// -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2; -*-
//
// Futaba485.hpp
//

#ifdef _WIN32
#pragma warning(disable:4251)
#endif

#ifndef _FUTABA485_HPP_
#define _FUTABA485_HPP_

#include <deque>
#ifdef __QNX__
#include <stdint.h>
#endif

#include "SerialIF.hpp"
#include "Logger.hpp"

#ifdef _WIN32
#include "stdint_vc.h"
#endif

#ifdef HIROHANDSDLL_EXPORTS
#define DLE __declspec(dllexport)
#else
#define DLE
#endif

#define PKT_BUFSIZE (128)

class DLE FutabaModuleChain ;

class DLE FutabaModule {
  friend class FutabaModuleChain;
public:
  typedef enum {TRQ_OFF=0x00, TRQ_ON=0x01, TRQ_BRAKE=0x02} TrqMode;
  typedef enum {NODUMP=0, STDERR=1} ErrDumpMode;
  typedef struct {
    uint8_t marginCW, marginCCW; // 0-255 (0.1 deg)
    uint8_t slopeCW,  slopeCCW;  // 0-150 (0.1 deg)
    uint16_t punch;              // 0-100 (0.01 %)
  } CompParam;
    
private:
  int mid; // module ID
  int16_t offset, lowerLimit, upperLimit;
  uint8_t status;
  typedef struct { 
    uint8_t address, length, count, status; 
    uint8_t data[PKT_BUFSIZE];
  } PktData;
  FutabaModuleChain *bus;
  inline void setBus(FutabaModuleChain *bus) { this->bus = bus; }
  Logger *logger;
  void log(const char *hdr, const char *format, ...) {
    if (this->logger) {
      VA_LIST ap; va_start(ap, format);
      this->logger->addMessage(hdr, "FutabaModule::", format, ap);
    }
  }

public:
  FutabaModule(int mid);
  virtual ~FutabaModule();
  int setDir(int8_t dir);
  int setRange(int16_t min, int16_t max);
  int setOffset(int16_t offset);
  int getCompParam(CompParam &param);
  int setCompParam(CompParam &param);
  int setTarget(int16_t goal, uint16_t time);
  int16_t getAngle(void);
  int setMaxTorque(uint8_t percent);
  int trqEnable(TrqMode trq_mode);
  int ping(void);
  inline void setLogger(Logger *logger) { 
    this->logger = logger; 
  }
};


class DLE FutabaModuleChain {
  friend class FutabaModule;
private:
  int num;
  SerialIF *serif;
  bool echobackDeviceFlag;
  Logger *logger;
  void log(const char *hdr, const char *format, ...) {
    if (this->logger) {
      VA_LIST ap; va_start(ap, format);
      this->logger->addMessage(hdr, "FutabaModuleChain::", format, ap);
    }
  }
  
public:
  std::deque<FutabaModule *>modules;

public:
  FutabaModuleChain();
  virtual ~FutabaModuleChain();
  
  int openDevice(const char *devname, int baudrate, 
                 bool echobackDeviceFlag);
  void closeDevice(void);

public:
  int createModules(int num, int mid[]);
  inline int getNum(void) { return num; }
  // int attachModule(FutabaModule *module);
  // int FutabaModule *getModule(int mid);
  
  int trqEnableAll(FutabaModule::TrqMode trq_mode);
  int setAllTargets(int16_t goal[], uint16_t time);

  inline void setLogger(Logger *logger) { 
    this->logger = logger; 
    this->serif->setLogger(logger);
  }

private:
  static const int HDR_SIZE;
  enum { RET_NONE=0, REG_ACK=1, RET_3059=5, RET_2029=7,
         RET_4259=9, RET_3041=11, RET_ADDR=15} ;
  int sendRequest(uint8_t id, uint8_t flag, FutabaModule::PktData &pkt);
  int sendShort(uint8_t id, uint8_t flag, FutabaModule::PktData &pkt);
  int sendLong(FutabaModule::PktData &pkt);
  int sendPacket(uint8_t hdr[], FutabaModule::PktData &pkt);
  int recvSpecifiedAddr(uint8_t id, FutabaModule::PktData &pkt);
  int recv(uint8_t id, FutabaModule::PktData &pkt);
};





#endif // _FUTABA485_HPP_

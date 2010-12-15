// -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2; -*-
//
// HiroHands.hpp
//

#ifndef _HIROHANDS_HPP_
#define _HIROHANDS_HPP_

#include <vector>

#include "Futaba485.hpp"


#ifdef HIROHANDSDLL_EXPORTS
#define DLE __declspec(dllexport)
#else
#define DLE
#endif

class DLE HiroHands;

class DLE HiroHand
{
  friend class HiroHands;
private:
  const int DOFS;
  std::vector<FutabaModule *> modules;
  int OPEN0, OPEN1, CLOSE0, CLOSE1;
  
  HiroHand(std::vector<FutabaModule *> &mods);
  ~HiroHand();
public:
  void setRange(int min0, int max0, int min1, int max1);
  int  servoON(void);
  int  servoBRAKE(void);
  int  servoOFF(void);
  int  close(int percent, float time);
  int  setPose(float j00deg, float j01deg,
               float j10deg, float j11deg, float time);
  int  setPose(float degs[4], float time);
  int  getCompParam(unsigned int jidx, FutabaModule::CompParam &param);
  int  setCompParam(unsigned int jidx, FutabaModule::CompParam &param);

  int readAngle(int idx);
};


class DLE HiroHands
{
public:
  typedef enum { 
    RH00=0, RH01, RH10, RH11, LH00, LH01, LH10, LH11, DOFS} jointTypes;
private:
  FutabaModuleChain fmods;
public:
  HiroHand *rightHand, *leftHand;
  HiroHands(Logger *logger);
  ~HiroHands();
  int init(const char *devname, int baudrate, bool echobackDeviceFlag);
  void release(void);
};


#endif // _HIROHANDS_HPP_

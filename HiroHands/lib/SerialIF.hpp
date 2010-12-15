// -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2; -*-
//
// SerialIF.hpp
//

#ifndef _SERIALIF_HPP_
#define _SERIALIF_HPP_

#include "Logger.hpp"

#ifdef POSIX_DEVIO
#include <pthread.h>
#endif

class SerialIF {
protected:
  Logger *logger;
  int     timeout;
protected:
  SerialIF() : logger(NULL), timeout(0) { }
  virtual ~SerialIF() { };

public:
  virtual void log(const char *hdr, const char *format, ...)=0;
  void setLogger(Logger *logger) { this->logger = logger; }
  virtual void setTimeout(int timeout_ms) { this->timeout=timeout_ms; };
  virtual int open(const char *devname) = 0;
  virtual int setBaudrate(int baudrate) = 0;
  virtual int read(void *buf, int size) = 0;
  virtual int read_one(void *buf) = 0;
  virtual int write(const void *buf, int size) = 0;
  virtual void close(void) = 0;

  virtual void lock(void) = 0;
  virtual void unlock(void) = 0;
};


#ifdef POSIX_DEVIO
class SerialIF_POSIX : public SerialIF {
private:
  int devfd;
  pthread_mutex_t devLock;
public:
  SerialIF_POSIX();
  ~SerialIF_POSIX() {}
  void log(const char *hdr, const char *format, ...) {
    if (this->logger) {
      VA_LIST ap; va_start(ap, format);
      this->logger->addMessage(hdr, "SerialIF_POSIX::", format, ap);
    }
  }
  int open(const char *devname);
  int setBaudrate(int baudrate);
  int read(void *buf, int size);
  int read_one(void *buf);
  int write(const void *buf, int size);
  void close(void);

  void lock(void)   { pthread_mutex_lock(&(this->devLock));   }
  void unlock(void) { pthread_mutex_unlock(&(this->devLock)); }
};
#endif


#ifdef _WIN32
#include <windows.h>

class SerialIF_Win32 : public SerialIF {
private:
  HANDLE devfd;
  CRITICAL_SECTION devLock;
public:
  SerialIF_Win32();
  ~SerialIF_Win32();
  void log(const char *hdr, const char *format, ...) {
    if (this->logger) {
      VA_LIST ap; va_start(ap, format);
      this->logger->addMessage(hdr, "SerialIF_Win32::", format, ap);
    }
  }
  int open(const char *devname);
  int setBaudrate(int baudrate);
  int read(void *buf, int size);
  int read_one(void *buf);
  int write(const void *buf, int size);
  void close(void);

  void lock(void)   { EnterCriticalSection(&(this->devLock)); }
  void unlock(void) { LeaveCriticalSection(&(this->devLock)); }
};
#endif


#endif // _SERIALIF_HPP_

// -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2; -*-
//
// SerialIF.cpp
//

#include <cstdarg>
#include <errno.h>

#ifndef __QNX__
#include <cstring>
#else
#include <string.h>
#define cfsetspeed(term, baudrate) \
cfsetispeed(term, baudrate);\
cfsetospeed(term, baudrate);
#endif

#ifdef _WIN32
#include "stdint_vc.h"
#else
#include <stdint.h>
#endif

#include "SerialIF.hpp"


//#define DUMP_COMM
#undef DUMP_COMM

#ifdef DUMP_COMM
static void dump_open(void);
static void dump_close(void);
static void dump_txdata(const void *buf, int size);
static void dump_rxdata(const void *buf, int size);
#endif


#ifdef POSIX_DEVIO
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>


SerialIF_POSIX::SerialIF_POSIX()
  : devfd(-1)
{
  pthread_mutex_init(&(this->devLock), NULL);
}


void SerialIF::log(const char *hdr, const char *format, ...)
{
  if (this->logger) {
    VA_LIST ap;
    va_start(ap, format);
    this->logger->addMessage(hdr, format, ap);
  }
}


int SerialIF_POSIX::open(const char *devname)
{
#ifdef DUMP_COMM  
  dump_open();
#endif

  if (this->devfd>=0) {
    this->log("++", "open(): device is already opened ?");
    this->close();
  }
  int fd = ::open(devname, O_RDWR);
  if (fd<0) {
    char *pmesg=std::strerror(errno);
    this->log("**", "open(): failed: %s", pmesg);
    return -1;
  }
  this->devfd=fd;
  return 0;
}

int SerialIF_POSIX::setBaudrate(int baudrate)
{
  if (this->devfd<0) {
    this->log("**", "setBaudrate(): device not opened.");
    return -1;
  }
  
  struct termios term;
  int res = tcgetattr(this->devfd, &term);
  if (res<0) {
    char *pmesg = std::strerror(errno);
    this->log("**", "setBaudrate(): failed to tcgetattr(): %s", pmesg);
    return -1;
  }
  
  cfmakeraw(&term);
  res = cfsetspeed(&term, baudrate);
  if (res<0) {
    char *pmesg = std::strerror(errno);
    this->log("**", "setBaudrate(): failed to cfsetspeed(%d): %s", 
              baudrate, pmesg);
    return -1;
  }
  
  res = tcsetattr(this->devfd, TCSANOW, &term);
  if (res<0) {
    char *pmesg = std::strerror(errno);
    this->log("**", "setBaudrate(): failed to tcsetattr(): %s", pmesg);
    return -1;
  }
  
  return 0;
}


int SerialIF_POSIX::read(void *buf, int size)
{
  if (this->devfd<0) {
    this->log("**", "read(): device not opened.");
    return -1;
  }
  
  uint8_t *bufp = static_cast<uint8_t *>(buf);
  
  int res;
  while(size>0) {
    if (this->timeout>0) {
      struct timeval tmout;
      tmout.tv_sec=  this->timeout/1000;
      tmout.tv_usec=(this->timeout%1000)*1000;
      
      fd_set sfds;
      FD_ZERO(&sfds);
      FD_SET(this->devfd, &sfds);
    
      res = ::select(devfd+1, &sfds, NULL, NULL, &tmout);
      if (res==0) {
        this->log("**", "read(): timeout.");
        return -2;
      }
    }
    
    res = ::read(this->devfd, bufp, size);
    if (res<=0) {
      char *pmesg = strerror(errno);
      this->log("**", "read(): failed to read(), got %d: %s", res, pmesg);
      return -3;
    }
    
    size -= res;
    bufp += res;
  }
  
  return 0;
}


int SerialIF_POSIX::read_one(void *buf)
{
  int res = read(buf, 1);
#ifdef DUMP_COMM
  if (res>=0) dump_rxdata(buf, 1);
#endif
  return res;
}


int SerialIF_POSIX::write(const void *buf, int size)
{
  if (this->devfd<0) {
    this->log("**", "write(): device not opened.");
    return -1;
  }
  
  const uint8_t *bufp = static_cast<const uint8_t *>(buf);
  
  while(size>0) {
    int res = ::write(this->devfd, bufp, size);
    if (res<=0) {
      char *pmesg = std::strerror(errno);
      this->log("**", "write(): failed to write, got %d: %s", res, pmesg);
      return -1;
    }
#ifdef DUMP_COMM
    dump_txdata(bufp, res);
#endif
    size-=res;
    bufp +=res;
  }
  
  return 0;
}

void SerialIF_POSIX::close(void)
{
  if(this->devfd > 0) {
    ::close(this->devfd);
    this->devfd=-1;
  }
#ifdef DUMP_COMM
  dump_close();
#endif
}

static int dumpfd_tx=-1;
static int dumpfd_rx=-1;

void dump_open(void)
{
  int mode = S_IRUSR|S_IWUSR;
  if (dumpfd_tx<0) dumpfd_tx = open("send.dat", O_WRONLY|O_CREAT, mode);
  if (dumpfd_rx<0) dumpfd_rx = open("recv.dat", O_WRONLY|O_CREAT, mode);
}

void dump_close(void)
{
  close(dumpfd_tx);
  close(dumpfd_rx);
}

void dump_txdata(const void *buf, int size)
{
  if (dumpfd_tx!=-1) {
    ssize_t res;
    res=write(dumpfd_tx, buf, size);
  }
}

void dump_rxdata(const void *buf, int size)
{
  if (dumpfd_rx!=-1) {
    ssize_t res;
    res=write(dumpfd_rx, buf, size);
  }
}


#endif // POSIX_DEVIO


#ifdef _WIN32
SerialIF_Win32::SerialIF_Win32()
  : devfd(INVALID_HANDLE_VALUE)
{
  InitializeCriticalSection(&(this->devLock));
}


SerialIF_Win32::~SerialIF_Win32()
{
  DeleteCriticalSection(&(this->devLock));
}


int SerialIF_Win32::open(const char *devname)
{
#ifdef DUMP_COMM  
  dump_open();
#endif

  if (this->devfd!=INVALID_HANDLE_VALUE) {
    this->log("++", "open(): device is already opened ?");
    this->close();
  }

  HANDLE fd = CreateFile(devname,
                         GENERIC_READ | GENERIC_WRITE,
                         0,   // shared mode ?
                         NULL, // security ?
                         OPEN_EXISTING,
                         FILE_ATTRIBUTE_NORMAL,
                         NULL); // template
  
  if (fd==INVALID_HANDLE_VALUE) {
    int err=GetLastError();
    char pmesg[128];
    strerror_s(pmesg, 128, err);
    this->log("**", "open('%s') failed: %s", devname, pmesg);
    return -1;
  }
  
  
#if 0
  COMMTIMEOUTS tmo;
  tmo.ReadTotalTimeoutMultiplier  = this->timeout; // per byte, ms/unit
  tmo.ReadTotalTimeoutConstant    = this->timeout; // pre call
  tmo.WriteTotalTimeoutMultiplier = 60000;    // pre byte
  tmo.WriteTotalTimeoutConstant   = 60000;    // pre call
  SetCommTimeouts(fd, &tmo);
#endif

  this->devfd=fd;

  return 0;
}

int SerialIF_Win32::setBaudrate(int baudrate)
{
  DCB dcb;
  int res = GetCommState(this->devfd, &dcb);
  if (FAILED(res)) {
    int err=GetLastError();
    char pmesg[128];
    strerror_s(pmesg, 128, err);
    this->log("**", "setBaudrate(%d): failed to GetCommState(): %s",
              baudrate, pmesg);
    return -1;
  }
  dcb.BaudRate = baudrate;
  dcb.ByteSize = 8;             // data size, xmit, and rcv
  dcb.Parity = NOPARITY;        // no parity bit
  dcb.StopBits = ONESTOPBIT;    // one stop bit
  
  res = SetCommState(this->devfd, &dcb);
  if (FAILED(res)) {
    int err=GetLastError();
    char pmesg[128];
    strerror_s(pmesg, 128, err);
    this->log("**", "setBaudrate(%d): failed to SetCommSate(): %s",
              baudrate, pmesg);
    return -1;
  }
  
  return 0;
}

int SerialIF_Win32::read(void *buf, int size)
{
  // [TODO] test me (error handling ?) 
  if (this->devfd==INVALID_HANDLE_VALUE) {
    this->log("**", "read(): device not opened.");
    return -1;
  }
  
  COMMTIMEOUTS tmo;
  tmo.ReadTotalTimeoutMultiplier  = this->timeout; // per byte, ms/unit
  tmo.ReadTotalTimeoutConstant    = this->timeout; // pre call
  tmo.WriteTotalTimeoutMultiplier = 60000;    // pre byte
  tmo.WriteTotalTimeoutConstant   = 60000;    // pre call
  SetCommTimeouts(this->devfd, &tmo);
  
  uint8_t *bufp = static_cast<uint8_t *>(buf);
  
  while(size>0) {
    unsigned long read_size;
    ReadFile(this->devfd, bufp, size, &read_size, NULL);
    if (read_size==0) {
      this->logger->addMessage("**", "ReadFile() error, timeout ?");
      return -2;
    }
    size -= read_size;
    bufp += read_size;
  }
  
  return 0;
}

int SerialIF_Win32::read_one(void *buf)
{
  int res = read(buf, 1);
#ifdef DUMP_COMM
  if (res>=0) dump_rxdata(buf, 1);
#endif
  return res;
}

int SerialIF_Win32::write(const void *buf, int size)
{
  unsigned long written_size;
  
  const uint8_t *bufp = static_cast<const uint8_t *>(buf);
  
  while(size>0) {
    WriteFile(devfd, bufp, size, &written_size, NULL);
    if (written_size<=0) return -1;
#ifdef DUMP_COMM
    dump_txdata(bufp, written_size);
#endif
    size-=written_size;
    bufp+=written_size;
  }
  
  return 0;
}


void SerialIF_Win32::close(void)
{
  if (this->devfd != INVALID_HANDLE_VALUE) {
    CloseHandle(this->devfd);
    this->devfd = INVALID_HANDLE_VALUE;
  }
#ifdef DUMP_COMM
  dump_close();
#endif
}

#ifdef DUMP_COMM
static HANDLE dumpfd_tx=INVALID_HANDLE_VALUE;
static HANDLE dumpfd_rx=INVALID_HANDLE_VALUE;

void dump_open(void)
{
  // [TODO] fixme ...
  dumpfd_tx=CreateFile("send.dat",
                       GENERIC_READ | GENERIC_WRITE,
                       0,   // shared mode ?
                       NULL, // security ?
                       OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL,
                       NULL); // template
  dumpfd_rx=CreateFile("recv.dat",
                       GENERIC_READ | GENERIC_WRITE,
                       0,   // shared mode ?
                       NULL, // security ?
                       OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL,
                       NULL); // template
}


void dump_txdata(const void *buf, int size)
{
  if (dumpfd_tx!=INVALID_HANDLE_VALUE) {
    unsigned long written_size;
    WriteFile(dumpfd_tx, buf, size, &written_size, NULL);
  }
}


void dump_rxdata(const void *buf, int size)
{
  if (dumpfd_rx!=INVALID_HANDLE_VALUE) {
    unsigned long written_size;
    WriteFile(dumpfd_rx, buf, size, &written_size, NULL);
  }
}


void dump_close(void)
{
  CloseHandle(dumpfd_tx);
  CloseHandle(dumpfd_rx);
}

#endif // DUMP_COMM
#endif // _WIN32


#if 0 // template
int open(const char *devname);
int setBaudrate(int baudrate);
int read(char *buf, int size);
int read_one(char *buf);
int write(char *buf, int size);
void close(void);
#endif

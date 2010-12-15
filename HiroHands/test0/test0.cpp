// -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2; -*-
//
// test0.cpp
//

#ifndef _WIN32
#define POSIX_SYSTEM
#endif

#include <iostream>
#include <iomanip>
#include <deque>
#include <cstdio>
#include "Futaba485.hpp"
#include "Logger.hpp"

#ifdef POSIX_SYSTEM
#include <unistd.h> // sleep(), usleep()
#define SNPRINTF std::snprintf
#else // _WIN32
#define sleep(sec)   Sleep((sec)*1000)
#define usleep(usec) Sleep((usec)/1000)
#define SNPRINTF sprintf_s
#endif


#define NUM (4)

#define TRQ_OFF   (FutabaModule::TRQ_OFF)
#define TRQ_ON    (FutabaModule::TRQ_ON)
#define TRQ_BRAKE (FutabaModule::TRQ_BRAKE)

enum {J00=0, J01, J10, J11};
int mid[NUM+1]={2,3,4,5,6};  // '+1' for timeout test

const int16_t min[NUM]={-900, -1500, -900, -1500};
const int16_t max[NUM]={ 450,   900,  450,   900}; 
const int16_t offset[NUM]= {450,0,450,0};
const int8_t  dir[NUM]={-1,-1,-1,-1};

#ifdef DEVICE
const char *devname=DEVICE;
#else
//const char *devname="/dev/ttyUSB0";
const char *devname="COM5";
#endif

#ifndef BAUDRATE
#define BAUDRATE (115200)
#endif

#ifdef _WIN32
int main_loop(void)
#else
int main(void)
#endif
{
  LoggerStderr logger;
  
  FutabaModuleChain fmods;
  fmods.setLogger(&logger);
  fmods.createModules(NUM+1, mid);
  std::deque<FutabaModule *> &modules = fmods.modules;
  int res;
  
#ifdef USING_ECHOBACK_IF
  bool echoback=true;
#else
  bool echoback=false;
#endif

  if (fmods.openDevice(devname, BAUDRATE, echoback) <0) {
    std::cerr << "** failed to open(" << devname << ")" << std::endl;
    return -1;
  }
  
  /* ping test */
  int err=0;
  for(int i=0;i<NUM;i++) {
    //std::cout << "ping to " << mid[i] << std::endl;
    res=modules[i]->ping();
    if (res<0) {
      std::cerr << "* failed to ping to " << mid[i] << std::endl;
      err = -1;
    }
    //std::cout << "- ping got from " << mid[i] << ", res: " << res 
    //          << std::endl;
  }
  
  /* ping timeout test */
  if (modules[NUM]->ping()<0) {
    std::cerr << "* failed to ping to " << mid[NUM] << std::endl;
  }
  
  
  if (err<0) {
    fmods.closeDevice();
    return -1;
  }

  //return 0;

  /* torque disble (servo off ) */
  res=fmods.trqEnableAll(TRQ_OFF);
  if (res<0) {
    std::cerr << "** failed to set TRQ_OFF(" << std::endl;
  } else {
    std::cout << "-- TRQ_OFF" << std::endl;
    //sleep(5);
  }
  
  /* setDir()/setMinMax()/setOffset() */
  for(int idx=0; idx<NUM; idx++) {
    modules[idx]->setDir(dir[idx]);
    modules[idx]->setRange(min[idx], max[idx]);
    modules[idx]->setOffset(offset[idx]);
  }
  
  /* getAngle */
  for(int count=0; count<20; count++) {
    for(int i=0; i<NUM; i++) {
      int angle = modules[i]->getAngle();
      std::cout << i << ": " << std::setw(7) << angle << ",   ";
    }
    std::cout << std::endl;
    
    usleep(500000);
  }
  
  
  /* get/set Compliance Paramters */
  for(int idx=0; idx<NUM; idx++) {
    FutabaModule::CompParam cp;
    modules[idx]->getCompParam(cp);
    char mesg[128];
    SNPRINTF(mesg, 128, "- %d: got margin %3d/%3d, slope %3d/%3d, punch %4d",
             mid[idx], cp.marginCW, cp.marginCCW, cp.slopeCW, cp.slopeCCW,
             cp.punch);
    std::cout << mesg << std::endl;
    cp.marginCW  = 2;
    cp.marginCCW = 2;
    cp.slopeCW   = 40;
    cp.slopeCCW  = 5;
    cp.punch = 2;
    SNPRINTF(mesg, 128, "- %d: set margin %3d/%3d, slope %3d/%3d, punch %4d",
             mid[idx], cp.marginCW, cp.marginCCW, cp.slopeCW, cp.slopeCCW,
             cp.punch);
    std::cout << mesg << std::endl;
    modules[idx]->setCompParam(cp);
  }
  
  
  /* brake */
  for(int i=0; i<NUM; i++) {
    res=modules[i]->trqEnable(TRQ_BRAKE);
    if (res <0) {
      std::cerr << "** failed to set TRQ_BRAKE(" << std::endl;
      err=-1;
    } else {
      std::cout << "-- TRQ_BRAKE " << mid[i] << std::endl;
    }
  }
  
  if (err<0) {
    fmods.closeDevice();
    return -1;
  } else {
    sleep(5);
  }
  
  
  /* torque enable (servo on ) */
  res=fmods.trqEnableAll(TRQ_ON);
  if (res<0) {
    std::cerr << "** failed to set TRQ_ON(" << std::endl;
    fmods.closeDevice();
    return -1;
  } else {
    std::cout << "-- TRQ_ON" << std::endl;
    sleep(10);
  }
  
  /* setTarget/setAlltargets */
  std::cout << "-- setTarget " << std::endl;
  for(int count=0; count<12; count++) {
    for(int idx=0; idx<NUM; idx++) {
      int j;
      if (idx==0 || idx==3) {
        j = (count%3+1)*min[idx]/3;
      } else {
        j = (count%3+1)*max[idx]/3;
      }        
      FutabaModule *mod = modules[idx];
      mod->setTarget(j, 150);
    }
    sleep(2);
    
    int16_t j[NUM];
    for(int idx=0; idx<NUM; idx++) {
      if (idx==0 || idx==3) j[idx] = (count%3+1)*max[idx]/3;
      else                  j[idx] = (count%3+1)*min[idx]/3;
    }
    
    fmods.setAllTargets(j, 150);
    sleep(2);
  }

  int16_t zero[NUM];
  for(int idx=0; idx<NUM; idx++) zero[idx]=0;
  fmods.setAllTargets(zero, 300);
  sleep(4);
  
  /* torque disable (servo off) */
  for(int i=0; i<NUM; i++) {
    res=modules[i]->trqEnable(TRQ_OFF);
    if (res <0) {
      std::cerr << "** failed to set TRQ_OFF(" << std::endl;
      err=-1;
    } else {
      std::cout << "-- TRQ_OFF " << mid[i] << std::endl;
    }
  }
  
  if (err<0) {
    fmods.closeDevice();
    return -1;
  }
  
  /* finished */
  fmods.closeDevice();
  
  return 0;
}

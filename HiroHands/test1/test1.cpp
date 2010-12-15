// -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2; -*-
//
// test1.cpp
//

#ifndef _WIN32
#define POSIX_SYSTEM
#endif

#include <iostream>

#ifdef POSIX_SYSTEM
#include <unistd.h> // usleep(), sleep()
#else // _WIN32
#define sleep(sec)   Sleep((sec)*1000)
#define usleep(usec) Sleep((usec)/1000)
#endif

#include "HiroHands.hpp"

#ifndef DEVICE
#ifdef _WIN32
#define DEVICE "COM5"
#else
#define DEVICE "/dev/ttyUSB0"
#endif
#endif

//#define USING_ECHOBACK_IF

#ifndef BAUDRATE
#define BAUDRATE (115200)
#endif

const char *devname=DEVICE;

#ifdef USING_ECHOBACK_IF
const bool echobackFlag=true;
#else
const bool echobackFlag=false;
#endif

#ifndef _WIN32
int main(void)
#else
int main_loop(void)
#endif
{
  LoggerStderr logger;
  HiroHands hands(&logger);
  if (hands.init(devname, BAUDRATE, echobackFlag)<0) return -1;
  
  HiroHand *rh = hands.rightHand;
  //HiroHand *lh = hands.leftHand;
  
  std::cerr << "Servo ON" << std::endl;
  rh->servoON();
  //lh->servoON();
  
  
  std::cerr << "OPEN hand" << std::endl;
  rh->setRange(-90, 0, 18, -16);
  rh->close(0,2);
  sleep(2);

  std::cerr << "close hand" << std::endl;
  for(int i=0; i<=100; i+=5) {
    rh->close(i, 0.5);
    usleep(500000);
  }
  
  
  std::cerr << "OPEN hand" << std::endl;
  rh->setRange(-90, 90, 18, -16);
  rh->close(0,2);
  sleep(2);
    
  std::cerr << "close hand" << std::endl;
  for(int i=0; i<=100; i+=5) {
    rh->close(i, 0.5);
    usleep(500000);
  }
  
  std::cerr << "wait for 5 sec" << std::endl;
  sleep(5);
  
  
  std::cerr << "release" << std::endl;
  hands.release();

  std::cerr << "Done" << std::endl;

  return 0;
}

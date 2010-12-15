// -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2; -*-
//
// HiroHands.cpp
//

#include <iostream>

#include<vector>

#include "HiroHands.hpp"

#define cast_int(var)    static_cast<int>(var)
#define cast_uint16(var) static_cast<uint16_t>(var)

HiroHand::HiroHand(std::vector<FutabaModule *> &mods)
  : DOFS(HiroHands::DOFS/2), modules(mods), 
    OPEN0(-90), OPEN1(90), CLOSE0(18), CLOSE1(-16)
{
}

HiroHand::~HiroHand()
{
}

void HiroHand::setRange(int open0, int open1, int close0, int close1)
{
  // [TODO] range check ?
  this->OPEN0  = open0;
  this->OPEN1  = open1;
  this->CLOSE0 = close0;
  this->CLOSE1 = close1;
}

int HiroHand::servoON(void)
{
  for(int idx=0; idx<DOFS; idx++) {
    this->modules[idx]->trqEnable(FutabaModule::TRQ_ON);
  }
  return 0;
}


int HiroHand::servoBRAKE(void)
{
  for(int idx=0; idx<DOFS; idx++) {
    this->modules[idx]->trqEnable(FutabaModule::TRQ_BRAKE);
  }
  return 0;
}


int HiroHand::servoOFF(void)
{
  for(int idx=0; idx<DOFS; idx++) {
    this->modules[idx]->trqEnable(FutabaModule::TRQ_OFF);
  }
  return 0;
}


int HiroHand::close(int percent, float time)
{
  float max = percent/100.0f;
  float min = 1-max;
  
  float deg0 = this->OPEN0*min + this->CLOSE0*max;
  float deg1 = this->OPEN1*min + this->CLOSE1*max;
  int d0 = cast_int(deg0*10);
  int d1 = cast_int(-deg1*10);
  
  for(int idx=0; idx<DOFS; idx++) {
    if (idx%2==0) this->modules[idx]->setTarget(d0, cast_uint16(time*100));
    else          this->modules[idx]->setTarget(d1, cast_uint16(time*100));
  }

  return 0;
}

int HiroHand::setPose(float j00deg, float j01deg,
                      float j10deg, float j11deg, float time)
{
  float degs[4];
  degs[0]=j00deg;
  degs[1]=j01deg;
  degs[2]=j10deg;
  degs[3]=j11deg;
  return this->setPose(degs, time);
}


int HiroHand::setPose(float degs[], float time)
{
  int time_10ms = cast_int(time*100);
  for(int idx=0; idx<this->DOFS; idx++) {
    int ddeg = cast_int(degs[idx]*10);
    this->modules[idx]->setTarget(ddeg, time_10ms);
  }
  return 0;
}

int HiroHand::getCompParam(unsigned int jidx, FutabaModule::CompParam &param)
{
  if ( jidx<modules.size() ) {
    this->modules[jidx]->getCompParam(param);
    return 0;
  }
  return -1;
}

int HiroHand::setCompParam(unsigned int jidx, FutabaModule::CompParam &param)
{
  if ( jidx<modules.size() ) {
    this->modules[jidx]->setCompParam(param);
    return 0;
  }
  return -1;
}

int HiroHand::readAngle(int idx)
{
  int ang;

  ang = cast_int(this->modules[idx]->getAngle());
  if(ang == 0xF000)
    std::cerr << "Angle Read Error" << std::endl;

  return ang;
}

//
//
//

HiroHands::HiroHands(Logger *logger)
  : fmods(), rightHand(NULL), leftHand(NULL)
{
  int mid[DOFS]={2,3,4,5,6,7,8,9};
  this->fmods.setLogger(logger);
  this->fmods.createModules(DOFS, mid);

  const int hdofs=this->DOFS/2;
  std::vector<FutabaModule *> modvec(hdofs);
  for(int idx=0; idx<hdofs; idx++) {
    modvec[idx] = this->fmods.modules[idx];
  }
  this->rightHand = new HiroHand(modvec);

  for(int idx=0; idx<hdofs; idx++) {
    modvec[idx] = this->fmods.modules[idx+hdofs];
  }
  this->leftHand = new HiroHand(modvec);
}


HiroHands::~HiroHands()
{
  this->fmods.setLogger(NULL);
  delete this->leftHand;
  delete this->rightHand;
  this->release();
}


int HiroHands::init(const char *devname, int baudrate, bool echobackDeviceFlag)
{
  int res=this->fmods.openDevice(devname, baudrate, echobackDeviceFlag);
  
  if(res<0) return res;
  
  const int16_t min[2]={-900, -1500};
  const int16_t max[2]={ 450,   900};
  const int16_t offset[2]= {450,0};

  bool dead[DOFS];

  for(int idx=0; idx<DOFS; idx++) {
    //std::cerr << "init: " << idx << std::endl;
    int res=this->fmods.modules[idx]->ping();
    dead[idx]=(res < 0 ? true : false);
  }

  for (int idx=0; idx<DOFS; idx++) {
    if (dead[idx]) continue;
    
    if (idx%2==0) this->fmods.modules[idx]->setDir(-1);
    else          this->fmods.modules[idx]->setDir(1);
    this->fmods.modules[idx]->setRange(min[idx%2], max[idx%2]);
    this->fmods.modules[idx]->setOffset(offset[idx%2]);

    FutabaModule::CompParam cp;
    this->fmods.modules[idx]->getCompParam(cp);
    cp.marginCW  = 2;
    cp.marginCCW = 2;
    //cp.slopeCW   = 40;
    cp.slopeCW   = 5;
    cp.slopeCCW  = 5;
    cp.punch = 2;
    this->fmods.modules[idx]->setCompParam(cp);
  }

  return res;
}


void HiroHands::release(void)
{
  this->fmods.trqEnableAll(FutabaModule::TRQ_OFF);
  this->fmods.closeDevice();
}

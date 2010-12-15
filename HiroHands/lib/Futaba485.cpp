// -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2; -*-
//
// Futaba485.cpp
//

#ifdef __QNX__
#include <string.h>
#else
#include <cstring> // memset()
#endif
#include <cerrno>  // errno
#include "Futaba485.hpp"

//#define DEFAULT_BPS (115200)
#define TIMEOUT     (200)  // ms

#define RET_NONE (FutabaModuleChain::RET_NONE)
#define RET_ADDR (FutabaModuleChain::RET_ADDR)


//
// FutabaModule
//

FutabaModule::FutabaModule(int mid)
  : mid(mid), offset(0), lowerLimit(-900), upperLimit(900), 
    bus(NULL), logger(NULL)
{
  return ;
}


FutabaModule::~FutabaModule()
{
  return ;
}


int FutabaModule::setDir(int8_t dir)
{
  // [TODO] check error handling...
  uint8_t rev;
  if      (dir== 1) rev=0;
  else if (dir==-1) rev=1;
  else {
    this->log("**", "setDir() to %d: unexpected argument %d must be 1 or -1",
              this->mid, dir);
    return -1;
  }
  
  PktData pkt;
  pkt.address= 0x05; // Reverse
  pkt.length =    1;
  pkt.data[0]=  rev;
  
  int res=this->bus->sendShort(this->mid, RET_ADDR, pkt);
  if (res<0) {
    this->log("**", "setDir() to %d: failed to sendShort(), got %d",
              this->mid, res);
    return -2;
  }
  
  pkt.data[0]=0xFF;
  res=this->bus->recvSpecifiedAddr(this->mid, pkt);
  if (res<0) {
    this->log("**", "setDir() to %d: failed to recv(), %d", this->mid, res);
    return -2;
  }
  
  if (pkt.data[0]!=rev) {
    this->log("**", "setDir() to %d: readback error, set/got:  0x%02X/0x%02X",
              this->mid, rev, pkt.data[0]);
    return -3;
  }
  
  // [TODO] remove me
  if (0) {
    this->log("--","setDir() to %d: set as 0x%02X", this->mid, pkt.data[0]);
  }

  return 0;
}


int FutabaModule::setRange(int16_t min, int16_t max)
{
  // [TODO] range check ?
  // [TODO] check error handling...
  int16_t regmin = min + this->offset;
  int16_t regmax = max + this->offset;
  
  if (regmin < -1500) {
    this->log("**", "setRange() to %d: min:%d < -1500, offset is %d",
              this->mid, regmin, this->offset);
    return -1;
  }
  
  if (regmin > 0) {
    this->log("**", "setRange() to %d: min:%d > 0, offset is %d",
              this->mid, regmin,this->offset);
    return -1;
  }
  
  
  if (regmax > 1500) {
    this->log("**", "setRange() to %d: max:%d > 1500, offset is %d",
              this->mid, regmax, this->offset);
    return -1;
  }
  
  if (regmax < 0) {
    this->log("**", "setRange() to %d: max:%d < 0, offset is %d",
              this->mid, regmax, this->offset);
    return -1;
  }
  
  FutabaModule::PktData pkt;
  pkt.address = 0x08; // CW_AngleLimitL
  pkt.length  = 4;
  pkt.data[0]=  regmax       & 0xFF;
  pkt.data[1]= (regmax >> 8) & 0xFF;
  pkt.data[2]=  regmin       & 0xFF;
  pkt.data[3]= (regmin >> 8) & 0xFF;
  int res=this->bus->sendShort(this->mid, RET_ADDR, pkt);
  if (res <0) {
    this->log("**", "setRange() to %d: failed to sendShort(), got %d",
              this->mid, res);
    return -1;
  }
  
  std::memset(pkt.data, 0, pkt.length);
  res=this->bus->recvSpecifiedAddr(this->mid, pkt);
  if(res<0) {
    this->log("**", "setRange() to %d: failed to recv(), %d", this->mid, res);
    return -1;
  }
  
  int16_t newmax = pkt.data[0] | (pkt.data[1]<<8);
  int16_t newmin = pkt.data[2] | (pkt.data[3]<<8);
  // [TODO] remove me
  if (0) {
    this->log("--", "setRange() to %d: read min:%d, max:%d",
              this->mid, newmin, newmax);
  }

  if (newmin != regmin || newmax != regmax) {
    regmin -= this->offset;
    newmin -= this->offset;
    this->log("**", "setRange() to %d: readback error, set/got: min %d/%d, "
              "max %d/%d", this->mid, regmin, newmin, regmax, newmax);
    return -1;

  } else {
    this->lowerLimit = min;
    this->upperLimit = max;
    // [TODO] remove me
    if (0) {
      this->log("--", "setRange() to %d: min %d, max %d", 
                this->mid, this->lowerLimit,  this->upperLimit);
    }        
  }
  
  return res;
}



int FutabaModule::setOffset(int16_t offset)
{
  // [TODO] range check ?
  // [TODO] check error handling...
  int16_t prev_offset=this->offset;
  this->offset=offset;
  int res = this->setRange(this->lowerLimit, this->upperLimit);
  if (res <0) {
    this->offset=prev_offset;
    this->log("**", "setOffset(%d) to %d: failed, result is %d", 
              this->mid, offset, res);
  }
  
  return res;
}


int FutabaModule::getCompParam(CompParam &param)
{
  // [TODO] check error handling...
  PktData pkt;
  pkt.address= 0x18; // CW_CompMargin
  pkt.length =    6;
  int res=this->bus->sendRequest(this->mid, RET_ADDR, pkt);
  if (res<0) {
    this->log("**", "getCompParam() to %d: failed to sendRequest().",
              this->mid);
    return -1;
  }
  
  res=this->bus->recvSpecifiedAddr(this->mid, pkt);
  if (res<0) {
    this->log("**", "getCompParam() to %d: failed to recv(), %d",
              this->mid, res);
    return -1;
  }
  
  param.marginCW  = pkt.data[0];
  param.marginCCW = pkt.data[1];
  param.slopeCW   = pkt.data[2];
  param.slopeCCW  = pkt.data[3];
  param.punch     = pkt.data[4] | (pkt.data[5]<<8);
  
  return 0;
}


int FutabaModule::setCompParam(CompParam &param)
{
  // [TODO] range check ?
  // [TODO] check error handling...
  PktData pkt;
  pkt.address= 0x18; // CW_CompMargin
  pkt.length =    6;
  pkt.data[0] = param.marginCW;
  pkt.data[1] = param.marginCCW;
  pkt.data[2] = param.slopeCW;
  pkt.data[3] = param.slopeCCW;
  pkt.data[4] = param.punch     &0xFF;
  pkt.data[5] =(param.punch>>8) &0xFF;

  int res=this->bus->sendShort(this->mid, RET_ADDR, pkt);
  if (res<0) {
    this->log("**", "setCompParam() to %d: failed to sendShort().", this->mid);
    return -1;
  }
  
  std::memset(pkt.data, 0, pkt.length);
  res=this->bus->recvSpecifiedAddr(this->mid, pkt);
  if (res<0) {
    this->log("**", "getCompParam() to %d: failed to recv(), %d", 
              this->mid, res);
    return -1;
  }
  
  uint16_t punch = pkt.data[4] | (pkt.data[5]<<8);
  if (param.marginCW != pkt.data[0] || param.marginCCW != pkt.data[1]
      || param.slopeCW != pkt.data[2] || param.slopeCCW != pkt.data[3]
      || param.punch != punch) {
    this->log("**", "setCompParam() to %d: readback error, set/got: "
              "marginCW %d/%d,  marginCCW %d/%d,  slopeCW %d/%d, "
              "slopeCCW %d/%d, punch %d/%d", this->mid,
              param.marginCW, pkt.data[0], param.marginCCW, pkt.data[1],
              param.slopeCW,   pkt.data[2], param.slopeCCW,   pkt.data[3], 
              param.punch, punch);
    return -1;
  }
  
  return 0;
}


int FutabaModule::setTarget(/// 0.1degree/unit
                            int16_t goal, 
                            /// 10ms/unit
                            uint16_t time)
{
  // [TODO] range check ?
  // [TODO] check error handling...
  goal += this->offset;
  PktData pkt;
  pkt.address = 0x1e; // GoalPositionL
  pkt.length   = 4;
  pkt.data[0]=  goal     &0xFF;
  pkt.data[1]= (goal>>8) &0xFF;
  pkt.data[2]=  time     &0xFF;
  pkt.data[3]= (time >>8)&0xFF;
  
  return bus->sendShort(this->mid, RET_NONE, pkt);
}


int16_t FutabaModule::getAngle(void)
{
  // [TODO] check error handling...
  PktData pkt;
  pkt.address= 0x2a; // PresentPositionL
  pkt.length=     2;
  int res = this->bus->sendRequest(this->mid, RET_ADDR, pkt);
  if (res<0) {
    this->log("**", "getAngle() to %d: failed to sendRequest().", this->mid);
    return (int16_t)(0xF000);
  }

  res = this->bus->recvSpecifiedAddr(this->mid, pkt);
  if(res<0) {
    this->log("**", "getAngle() to %d: failed to recv(), %d", this->mid, res);
    return (int16_t)(0xF000);
  }
  
  int16_t angle;
  angle = pkt.data[0] | (pkt.data[1] << 8);
  angle -= this->offset;
  // [TODO] remove me
  if (0) {
    this->log("--", "getAngle() to %d: got 0x%02X%02X, %d",
              this->mid, pkt.data[1], pkt.data[0], angle);
  }
  
  return angle;
}


int FutabaModule::setMaxTorque(uint8_t percent)
{
  // [TODO] range check ?
  // [TODO] check error handling...
  PktData pkt;
  pkt.address = 0x23; // MaxTorque
  pkt.length   = 1;
  pkt.data[0]=  percent;
  
  int res=this->bus->sendShort(this->mid, RET_ADDR, pkt);
  if (res<0) {
    this->log("**", "setMaxTorque() to %d: failed to sendShort().", this->mid);
    return -1;
  }
  
  //std::memset(pkt.data, 0, pkt.length);
  pkt.data[0]=0;
  res = this->bus->recvSpecifiedAddr(this->mid, pkt);
  if (res<0) {
    this->log("**", "setMaxTorque() to %d: failed to recv().", this->mid);
    return -1;
  }
  
  if (pkt.data[0]!=percent) {
    this->log("**", "setMaxTorque() to %d: readback error, set/got  %d/%d.",
              this->mid, percent, pkt.data[0]);
    return -1;
  }    
  
  return 0;
}


int FutabaModule::trqEnable(TrqMode trqMode)
{
  // [TODO] check error handling...
  PktData pkt;
  pkt.address = 0x24; // TorqueEnable
  pkt.length   = 1;
  pkt.data[0]=  trqMode &0xFF;
  
  int res = bus->sendShort(this->mid, RET_ADDR, pkt);
  if (res<0) {
    this->log("**", "trqEnable() to %d: failed to sendShort.", this->mid);
    return -1;
  }
  do {
    res = bus->recvSpecifiedAddr(this->mid, pkt);
    if (res<-1) break;
  } while(res==-1);

  if(res<0) {
    this->log("**", "trqEnable() to %d: failed to in recv(), %d", 
              this->mid, res);
    return -1;
  }

  return 0;
}


int FutabaModule::ping(void)
{
  PktData pkt;
  pkt.address = 0x00;
  pkt.length  = 5;

  int res=this->bus->sendRequest(this->mid, RET_ADDR, pkt);
  if (res<0) {
    this->log("**", "ping() to %d: failed to sendRequest().", this->mid);
    return -1;
  }
  do {
    res = bus->recvSpecifiedAddr(this->mid, pkt);
    if (res<-1) break;
  } while(res==-4); // packet is good, but not expected.

  if(res<0) {
    this->log("**", "ping() to %d: failed to recv(), %d", this->mid, res);
    return -1;
  } else {
    this->log("--", "ping(): got Model:0x%02X%02X, Firm:0x%02X, ID:0x%02X",
              pkt.data[1], pkt.data[0], pkt.data[2], pkt.data[4]);
  }
  
  return 0;
}


//
// FutabaModuleChain
//
FutabaModuleChain::FutabaModuleChain() 
  : num(0), echobackDeviceFlag(false)
{
#ifdef POSIX_DEVIO
  this->serif = new SerialIF_POSIX();
#else // _WIN32
  this->serif = new SerialIF_Win32();
#endif
}

FutabaModuleChain::~FutabaModuleChain()
{
  this->closeDevice();
  
  int num = this->modules.size();
  if (num>0) {
    for(int idx=0; idx<num; idx++) {
      delete this->modules[idx];
    }
  }
  this->modules.resize(0);
}

int FutabaModuleChain::openDevice(const char *devname, int baudrate,
                                      bool echobackDeviceFlag)
{
  this->serif->setLogger(this->logger);
  this->serif->lock();
  if (this->serif->open(devname)<0) {
    this->log("**", "openDeivce(): failed to open(%s).", devname);
    this->serif->unlock();
    return -1;
  }
  this->serif->setTimeout(TIMEOUT);
  
  if (serif->setBaudrate(baudrate)<0) {
    this->log("**", "openDeivce(): failed to setBaudrate(%d).", baudrate);
    this->serif->unlock();
    return -1;
  }
  
  this->echobackDeviceFlag = echobackDeviceFlag;
  
  if (1) {
    this->log("--", "openDevice(): succeeded in open(%s) and setting %d bps.",
              devname, baudrate);
  }
  this->serif->unlock();
  return 0;
}


void FutabaModuleChain::closeDevice(void)
{
  this->serif->lock();
  this->serif->close();
  this->serif->unlock();
}

// not checking duplicated mid ... How do I handle this ?
int FutabaModuleChain::createModules(int num, int mid[])
{
  // [TODO] test me
  if (this->modules.size()!=0) {
    // [TODO] test me
    this->log("**", "createModules(): modules are not empty.");
    return -1;
  }
  
  for(int idx=0; idx<num; idx++) {
    FutabaModule *mod = new FutabaModule(mid[idx]);
    mod->setBus(this);
    mod->setLogger(this->logger);
    this->modules.push_back(mod);
  }
  this->num = num;
  
  return 0;
}


int FutabaModuleChain::trqEnableAll(FutabaModule::TrqMode trq_mode)
{
  // [TODO] need check of overflow of pkt.data[]
  FutabaModule::PktData pkt;
  uint8_t *ptr = pkt.data;
  
  pkt.address = 0x24; // TorqueEnable
  pkt.length  = 2;
  
  for(int idx=0; idx<this->num; idx++) {
    FutabaModule *mod = this->modules[idx];
    *ptr++ = mod->mid;
    *ptr++ = static_cast<uint8_t>(trq_mode);
  }
  pkt.count=this->num;
  
  this->sendLong(pkt);
  
  return 0;
}

 
int FutabaModuleChain::setAllTargets(/// joint angles (0.1degree/unit)
                                     int16_t goal[], 
                                     /// time (10ms/unit)
                                     uint16_t time)
{
  // [TODO] range check ?
  // [TODO] need check of overflow of pkt.data[]
  FutabaModule::PktData pkt;
  uint8_t *ptr = pkt.data;
  
  pkt.address = 0x1e; // GoalPositionL
  pkt.length  = 5;
  pkt.count = this->num;
  
  for(int idx=0; idx<this->num; idx++) {
    FutabaModule *mod = this->modules[idx];
    register int g = goal[idx] + mod->offset;
    *ptr++ = mod->mid;
    *ptr++ =  g     &0xFF;
    *ptr++ = (g>>8) &0xFF;
    *ptr++ =  time     &0xFF;
    *ptr++ = (time >>8)&0xFF;
  }
  
  this->sendLong(pkt);
  
  return 0;
}


const int FutabaModuleChain::HDR_SIZE=7;

int FutabaModuleChain::sendRequest(uint8_t mid, uint8_t flag, 
                                   FutabaModule::PktData &pkt)
{
  uint8_t hdr[HDR_SIZE];
  hdr[0]= 0xFA;
  hdr[1]= 0xAF;
  hdr[2]= mid;         // ID
  hdr[3]= flag;        // Flags
  hdr[4]= pkt.address; // Address
  hdr[5]= pkt.length;  // Length
  hdr[6]= 0;           // Count;
  
  return sendPacket(hdr, pkt);
}


int FutabaModuleChain::sendShort(uint8_t mid, uint8_t flag, 
                                 FutabaModule::PktData &pkt)
{
  uint8_t hdr[HDR_SIZE];
  hdr[0]= 0xFA;
  hdr[1]= 0xAF;
  hdr[2]= mid;         // ID
  hdr[3]= flag;        // Flags
  hdr[4]= pkt.address; // Address
  hdr[5]= pkt.length;  // Length
  hdr[6]= 1;           // Count;
  
  return sendPacket(hdr, pkt);
}


int FutabaModuleChain::sendLong(FutabaModule::PktData &pkt)
{
  uint8_t hdr[HDR_SIZE];
  hdr[0]= 0xFA;
  hdr[1]= 0xAF;
  hdr[2]= 0x00;        // ID
  hdr[3]= 0x00;        // Flags
  hdr[4]= pkt.address; // Address
  hdr[5]= pkt.length;  // Length
  hdr[6]= pkt.count;   // Count;

  return sendPacket(hdr, pkt);
}


int FutabaModuleChain::sendPacket(uint8_t hdr[], FutabaModule::PktData &pkt)
{
  // [TODO] error handling ?
  int data_size=pkt.length*hdr[6]; // hdr[6]: Count
  
  uint8_t sum=hdr[2]; // ID
  for (int idx=3; idx<HDR_SIZE;  idx++) sum ^= hdr[idx];
  for (int idx=0; idx<data_size; idx++) sum ^= pkt.data[idx];

  int sent=0;

  this->serif->lock();
  int res=this->serif->write(hdr, HDR_SIZE);
  sent += HDR_SIZE;
  if (res<0) {
    this->serif->unlock();
    this->log("**", "sendPacket(): failed to write header, %d", res);
    return -1;
  }
  
  if (data_size>0) {
    res=this->serif->write(&pkt.data, data_size);
    sent += data_size;
    if (res<0) {
      this->serif->unlock();
      this->log("**", "sendPacket(): failed to write data, size %d, res %d",
                data_size, res);
      return -1;
    }
  }
  res=this->serif->write(&sum, 1);
  sent += 1;
  if (res<0) {
    this->serif->unlock();
    this->log("**", "sendPacket(): failed to write checksum.");
    return -1;
  }
  
  if (this->echobackDeviceFlag) {
    const int BUFSIZE=1024;
    char buf[BUFSIZE];
    while(sent>0) {
      int num = (sent > BUFSIZE ? BUFSIZE : sent);
      res=this->serif->read(buf, num);
      if (res<0) {
        this->serif->unlock();
        this->log("**", "sendPacket(): unexpected error in read echobacks.");
        return -1;
      }
      sent-=num;
    }
  }
  
  this->serif->unlock();
  
  return 0;
}


int FutabaModuleChain::recvSpecifiedAddr(uint8_t mid, 
                                         FutabaModule::PktData &pkt)
{
  // [TODO] error handling ?
  uint8_t address = pkt.address; // specified address
  uint8_t length  = pkt.length;   // specified length
  
  int res = recv(mid, pkt);
  
  if (res<0) return res;
  
  if (pkt.address!=address || pkt.length!=length ||pkt.count!=1) {
    this->log("**", "recvSpecifiedAddr(): got unexpected packet, "
              "got address:0x%02X, length:%d, couont:%d, "
              " must be address:0x%02X, length:%d, count:1",
              pkt.address, pkt.length, pkt.count, address, length);
    return -4;
  }
  
  return 0;
}


int FutabaModuleChain::recv(uint8_t mid, FutabaModule::PktData &pkt)
{
  // [TODO] error handling ?
  enum {HDR0=0, HDR1, MID, FLAGS, ADDR, LEN, COUNT, DATA, SUM, DONE} state;
  
  state = HDR0;
  unsigned char ch;
  uint8_t recv_mid=0;
  uint8_t sum=0;
  uint8_t *ptr = pkt.data;
  int size=0;
  
  while(state!=DONE) {
    int res = this->serif->read_one(&ch);
    if (res<0) {
      //this->log("**", "recv(): failed to read()");
      return res;
    }
    
    //this->log("--", "recv(): state: %d, ch: 0x%02X", state, ch);
    switch(state) {
    case HDR0:
      if (ch==0xFD) state=HDR1;
      break;
      
    case HDR1:
      if (ch==0xDF) state=MID;
      else state=HDR0;
      break;
      
    case MID:
      recv_mid=ch;
      sum=ch;
      state=FLAGS;
      break;
      
    case FLAGS:
      pkt.status=ch;
      sum^=ch;
      state=ADDR;
      break;
      
    case ADDR:
      pkt.address=ch;
      sum^=ch;
      state=LEN;
      break;
      
    case LEN:
      pkt.length=ch;
      sum^=ch;
      state=COUNT;
      break;
      
    case COUNT:
      pkt.count=ch;
      sum^=ch;
      state=DATA;
      size = pkt.count*pkt.length;
      break;
      
    case DATA:
      *ptr++ = ch; // [TODO] buffer size check ?
      sum ^= ch;
      if (--size==0) state=SUM;
      break;
      
    case SUM:
      if (sum != ch) {
        this->log("**", "recv(): unexpected packet, id:0x%02X, "
                  "Flags:0x%02X, Address:0x%02X, Length:%d, "
                  "Count:%d, ..., Sum:0x%02X (must be 0x%2X)",
                  recv_mid, pkt.status, pkt.address, pkt.length,
                  pkt.count, ch, sum);
        return -1;
      } else {
        state=DONE;
      }
      break;
      
    default:
      this->log("++", "unexpected state, start from header...");
      state=HDR0;
      break;
    }
  }
  
  if (recv_mid!= mid) return -4; // when id mismatch
  
  return 0;
}

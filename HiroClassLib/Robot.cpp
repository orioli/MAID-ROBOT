// -*- coding: utf-8  -*-
/*!
 *  @file   Robot.cpp
 *  @brief  ロボット制御クラスライブラリ
 */

#ifdef _WIN32
#pragma warning(disable: 4996)  // unsafe sprintf(), strcpy()
#endif

#include <cstdio>
#include <cstring>
#include "Robot.hpp"

using namespace KSP;


////////////////////////////////////////////////////////////////////
// class Arm
//

Arm::Arm(int block)
  : block(block), arm(NULL), speed(-1)
{
}

Arm::~Arm()
{
}

void Arm::connect(armServer_var arm)
{
  this->arm = arm;
}

void Arm::setDefaultSpeed(int speed)
{
  this->speed=speed;
}


void Arm::getAngles(double angles[DOFS_ARM], bool realFlag)
{
  ::CORBA::Double j[DOFS_ARM];  
  switch(this->block) {
  case DRARM:
    if (realFlag)
      this->arm->getJointAnglesRightArmReal(j[0],j[1],j[2],j[3],j[4],j[5]);
    else
      this->arm->getJointAnglesRightArm(j[0],j[1],j[2],j[3],j[4],j[5]);
    break;

  case DLARM:
    if (realFlag)
      this->arm->getJointAnglesLeftArmReal(j[0], j[1], j[2], j[3], j[4], j[5]);
    else
      this->arm->getJointAnglesLeftArm(j[0], j[1], j[2], j[3], j[4], j[5]);
    break;

  default:
    break;
  }

  for(int i=0; i<6; i++) angles[i]=j[i];

  return ;
}


unsigned long Arm::makePose(const double angles[], int speed)
{
  unsigned long status;

  if (speed<0) speed=this->speed;
  status = this->makePose(angles[0], angles[1], angles[2],
			  angles[3], angles[4], angles[5], speed);
  return status;
}


unsigned long Arm::makePose(double j0, double j1, double j2,
		   double j3, double j4, double j5, int speed)
{
  if (speed<0) speed=this->speed;
  this->wait();
  ::CORBA::ULong status;
  switch(this->block) {
  case DRARM:
    this->arm->setJointAnglesRightArmP(static_cast<double>(j0), 
				       static_cast<double>(j1),
				       static_cast<double>(j2),
				       static_cast<double>(j3),
				       static_cast<double>(j4),
				       static_cast<double>(j5),
				       static_cast<double>(speed), status);
    break;

  case DLARM:
    this->arm->setJointAnglesLeftArmP(static_cast<double>(j0),
				      static_cast<double>(j1),
				      static_cast<double>(j2),
				      static_cast<double>(j3),
				      static_cast<double>(j4),
				      static_cast<double>(j5),
				      static_cast<double>(speed), status);
    break;

  default:
    break;
  }

  return static_cast<unsigned long>(status);
}


unsigned long Arm::moveUpper(double j0, double j1, double j2, int speed)
{
  if (speed<0) speed=this->speed;
  this->wait();
  ::CORBA::Double j[DOFS_ARM];  
  switch (this->block) {
  case DRARM:
    this->arm->getJointAnglesRightArm(j[0],j[1],j[2],j[3],j[4],j[5]);
    break;
  case DLARM:
    this->arm->getJointAnglesLeftArm(j[0], j[1], j[2], j[3], j[4], j[5]);
    break;
  default:
    break;
  }

  j[0] += static_cast<double>(j0);
  j[1] += static_cast<double>(j1);
  j[2] += static_cast<double>(j2);

  ::CORBA::ULong status;
  switch(this->block) {
  case DRARM:
    this->arm->setJointAnglesRightArmP(static_cast<double>(j[0]),
				       static_cast<double>(j[1]),
				       static_cast<double>(j[2]),
				       static_cast<double>(j[3]),
				       static_cast<double>(j[4]),
				       static_cast<double>(j[5]),
				       static_cast<double>(speed), status);
    break;
  case DLARM:
    this->arm->setJointAnglesLeftArmP(static_cast<double>(j[0]),
				      static_cast<double>(j[1]),
				      static_cast<double>(j[2]),
				      static_cast<double>(j[3]),
				      static_cast<double>(j[4]),
				      static_cast<double>(j[5]),
				      static_cast<double>(speed), status);
    break;
  default:
    break;
  }

  return static_cast<unsigned long>(status);
}


unsigned long Arm::moveUpperTo(double j0, double j1, double j2, int speed)
{
  if (speed<0) speed=this->speed;
  this->wait();
  ::CORBA::Double j[DOFS_ARM];  
  switch (this->block) {
  case DRARM:
    this->arm->getJointAnglesRightArm(j[0],j[1],j[2],j[3],j[4],j[5]);
    break;
  case DLARM:
    this->arm->getJointAnglesLeftArm(j[0], j[1], j[2], j[3], j[4], j[5]);
    break;
  default:
    break;
  }

  j[0] = static_cast<double>(j0);
  j[1] = static_cast<double>(j1);
  j[2] = static_cast<double>(j2);

  ::CORBA::ULong status;
  switch(this->block) {
  case DRARM:
    this->arm->setJointAnglesRightArmP(static_cast<double>(j[0]),
				       static_cast<double>(j[1]),
				       static_cast<double>(j[2]),
				       static_cast<double>(j[3]),
				       static_cast<double>(j[4]),
				       static_cast<double>(j[5]),
				       static_cast<double>(speed), status);
    break;
  case DLARM:
    this->arm->setJointAnglesLeftArmP(static_cast<double>(j[0]),
				      static_cast<double>(j[1]),
				      static_cast<double>(j[2]),
				      static_cast<double>(j[3]),
				      static_cast<double>(j[4]),
				      static_cast<double>(j[5]),
				      static_cast<double>(speed), status);
    break;
  default:
    break;
  }

  return static_cast<unsigned long>(status);
}


unsigned long Arm::moveFore(double j3, double j4, double j5, int speed)
{
  if (speed<0) speed=this->speed;
  this->wait();
  ::CORBA::Double j[DOFS_ARM];  
  switch (this->block) {
  case DRARM:
    this->arm->getJointAnglesRightArm(j[0],j[1],j[2],j[3],j[4],j[5]);
    break;
  case DLARM:
    this->arm->getJointAnglesLeftArm(j[0], j[1], j[2], j[3], j[4], j[5]);
    break;
  default:
    break;
  }

  j[3] += static_cast<double>(j3);
  j[4] += static_cast<double>(j4);
  j[5] += static_cast<double>(j5);

  ::CORBA::ULong status;
  switch(this->block) {
  case DRARM:
    this->arm->setJointAnglesRightArmP(static_cast<double>(j[0]),
				       static_cast<double>(j[1]),
				       static_cast<double>(j[2]),
				       static_cast<double>(j[3]),
				       static_cast<double>(j[4]),
				       static_cast<double>(j[5]),
				       static_cast<double>(speed), status);
    break;
  case DLARM:
    this->arm->setJointAnglesLeftArmP(static_cast<double>(j[0]),
				      static_cast<double>(j[1]),
				      static_cast<double>(j[2]),
				      static_cast<double>(j[3]),
				      static_cast<double>(j[4]),
				      static_cast<double>(j[5]),
				      static_cast<double>(speed), status);
    break;
  default:
    break;
  }

  return static_cast<unsigned long>(status);
}


unsigned long Arm::moveForeTo(double j3, double j4, double j5, int speed)
{
  if (speed<0) speed=this->speed;
  this->wait();
  ::CORBA::Double j[DOFS_ARM];  
  switch (this->block) {
  case DRARM:
    this->arm->getJointAnglesRightArm(j[0],j[1],j[2],j[3],j[4],j[5]);
    break;
  case DLARM:
    this->arm->getJointAnglesLeftArm(j[0], j[1], j[2], j[3], j[4], j[5]);
    break;
  default:
    break;
  }
  
  j[3] = static_cast<double>(j3);
  j[4] = static_cast<double>(j4);
  j[5] = static_cast<double>(j5);
  
  ::CORBA::ULong status;
  switch(this->block) {
  case DRARM:
    this->arm->setJointAnglesRightArmP(j[0], j[1], j[2], j[3], j[4], j[5],
				       static_cast<double>(speed), status);
    break;
  case DLARM:
    this->arm->setJointAnglesLeftArmP(j[0], j[1], j[2], j[3], j[4], j[5],
				      static_cast<double>(speed), status);
    break;
  default:
    break;
  }

  return static_cast<unsigned long>(status);
}


void Arm::wait(void)
{
  ::CORBA::Octet block = this->block & 0xFF;
  this->arm->inMotion(block, true);
}


////////////////////////////////////////////////////////////////////
// class Hand
//

Hand::Hand(int block)
  : block(block), speed(-1), complementType(COMPLEMENTBY_ANGLE)
{
}

Hand::~Hand()
{
}

void Hand::connect(armServer_var arm, coordServer_var coord)
{
  this->arm = arm;
  this->coord = coord;
}


void Hand::setDefaultSpeed(int speed)
{
  this->speed=speed;
}


void Hand::setDefaultComplementType(int cType)
{
  this->complementType = cType;
}

void Hand::getCoord(double coord[6])
{
  double offset[6];
  for(int idx=0; idx<6; idx++) offset[idx] = 0.0;
  
  getCoord(offset,coord);
}

void Hand::getCoord(double offset[6], double coord[6])
{

  coordServer::Position Offset, Pos;
  ::CORBA::Octet baseCS = coordServer::FrontCS;
  ::CORBA::Octet targetCS=coordServer::RWristCS;
  if (this->block == KSP::LARM) targetCS = coordServer::LWristCS;

  ::CORBA::Octet typeTarget=0;

  for(int idx=0; idx<6; idx++)
    Offset[idx] = offset[idx];

  this->coord->getTarget(targetCS, Offset, baseCS, typeTarget, Pos);

  for(int idx=0; idx<6; idx++)
    coord[idx] = static_cast<double>(Pos[idx]);
}


unsigned long Hand::move(double xyz[3], int speed, int cType)
{
  if (speed<0) speed=this->speed;
  if (cType<0) cType = this->complementType;
  
  ::CORBA::Octet targetCS=coordServer::RWristCS;
  if (this->block == KSP::LARM) targetCS = coordServer::LWristCS;
  
  this->wait();

  ::CORBA::Octet baseCS = coordServer::FrontCS;
  coordServer::Position offsetZero, pos;
  for(int idx=0; idx<6; idx++) offsetZero[idx]=0.0;
  ::CORBA::Octet typeTarget=0;
  this->coord->getTarget(targetCS, offsetZero, baseCS, typeTarget, pos);
  for(int idx=0; idx<3; idx++) pos[idx]+=static_cast<double>(xyz[idx]);
  ::CORBA::ULong status;
  this->coord->moveTarget(cType, baseCS, pos, targetCS, 
			  static_cast<double>(speed), status);

  return static_cast<unsigned long>(status);
}


unsigned long Hand::move(double x, double y, double z, int speed, int cType)
{
  unsigned long status;
  double xyz[3];
  xyz[0]=x;  xyz[1]=y;  xyz[2]=z;
  status=this->move(xyz, speed, cType);
  return status;
}


unsigned long Hand::moveTo(double xyz[3], int speed, int cType)
{
  if (speed<0) speed=this->speed;
  if (cType<0) cType = this->complementType;
  
  ::CORBA::Octet targetCS=coordServer::RWristCS;
  if (this->block == KSP::LARM) targetCS = coordServer::LWristCS;
  
  this->wait();

  ::CORBA::Octet baseCS = coordServer::FrontCS;
  coordServer::Position offsetZero, pos;
  for(int idx=0; idx<6; idx++) offsetZero[idx]=0.0;
  ::CORBA::Octet typeTarget=0;
  this->coord->getTarget(targetCS, offsetZero, baseCS, typeTarget, pos);
  for(int idx=0; idx<3; idx++) pos[idx]=static_cast<double>(xyz[idx]);
  ::CORBA::ULong status;
  this->coord->moveTarget(cType, baseCS, pos, targetCS, 
			  static_cast<double>(speed), status);

  return static_cast<unsigned long>(status);
}


unsigned long Hand::moveTo(double x, double y, double z, int speed, int cType)
{
  unsigned long status;
  double xyz[3];
  xyz[0]=x;  xyz[1]=y;  xyz[2]=z;
  status=this->moveTo(xyz, speed, cType);

  return status;
}


unsigned long Hand::resetPose(int speed, int cType)
{
  if (speed<0) speed=this->speed;
  if (cType<0) cType = this->complementType;
  
  ::CORBA::Octet targetCS=coordServer::RWristCS;
  if (this->block == KSP::LARM) targetCS = coordServer::LWristCS;

  this->wait();

  ::CORBA::Octet baseCS = coordServer::FrontCS;
  coordServer::Position offsetZero, pos;
  for(int idx=0; idx<6; idx++) offsetZero[idx]=0.0;
  ::CORBA::Octet typeTarget=0;
  this->coord->getTarget(targetCS, offsetZero, baseCS, typeTarget, pos);
  pos[3]=180.0;
  pos[4]=-90.0;
  pos[5]=180.0;
  ::CORBA::ULong status;
  this->coord->moveTarget(cType, baseCS, pos, targetCS, 
			  static_cast<double>(speed), status);

  return static_cast<unsigned long>(status);
}


unsigned long Hand::turn(double rpy[3], int speed, int cType)
{
  if (speed<0) speed=this->speed;
  if (cType<0) cType = this->complementType;
  
  ::CORBA::Octet targetCS=coordServer::RWristCS;
  if (this->block == KSP::LARM) targetCS = coordServer::LWristCS;
  
  this->wait();
  
  ::CORBA::Octet baseCS = coordServer::FrontCS;
  coordServer::Position offsetZero, pos;
  for(int idx=0; idx<6; idx++) offsetZero[idx]=0.0;
  ::CORBA::Octet typeTarget=0;
  this->coord->getTarget(targetCS, offsetZero, baseCS, typeTarget, pos);
  for(int idx=0; idx<3; idx++) pos[idx+3]+=static_cast<double>(rpy[idx]);
  ::CORBA::ULong status;
  this->coord->moveTarget(cType, baseCS, pos, targetCS, 
			  static_cast<double>(speed), status);

  return static_cast<unsigned long>(status);
}


unsigned long Hand::turn(double r, double p, double y, int speed, int cType)
{
  unsigned long status;
  double rpy[3];
  rpy[0]=r;  rpy[1]=p;  rpy[2]=y;
  status=this->turn(rpy, speed, cType);

  return status;
}


unsigned long Hand::turnTo(double rpy[3], int speed, int cType)
{
  if (speed<0) speed=this->speed;
  if (cType<0) cType = this->complementType;
  
  ::CORBA::Octet targetCS=coordServer::RWristCS;
  if (this->block == KSP::LARM) targetCS = coordServer::LWristCS;
  
  this->wait();
  
  ::CORBA::Octet baseCS = coordServer::FrontCS;
  coordServer::Position offsetZero, pos;
  for(int idx=0; idx<6; idx++) offsetZero[idx]=0.0;
  ::CORBA::Octet typeTarget=0;
  this->coord->getTarget(targetCS, offsetZero, baseCS, typeTarget, pos);
  for(int idx=0; idx<3; idx++) pos[idx+3]=static_cast<double>(rpy[idx]);
  ::CORBA::ULong status;
  this->coord->moveTarget(cType, baseCS, pos, targetCS, 
			  static_cast<double>(speed), status);

  return static_cast<unsigned long>(status);
}


unsigned long Hand::turnTo(double r, double p, double y, int speed, int cType)
{
  unsigned long status;
  double rpy[3];
  rpy[0]=r;  rpy[1]=p;  rpy[2]=y;
  status=this->turnTo(rpy, speed, cType);

  return status;
}


void Hand::wait()
{
  ::CORBA::Octet block = this->block & 0xFF;
  this->arm->inMotion(block, true);
}


////////////////////////////////////////////////////////////////////
// class Robot
//

Robot::Robot(const std::string ipaddr)
  : ipaddr(ipaddr), msgstrm(std::cerr), rarm(KSP::RARM), larm(KSP::LARM),
    rhand(KSP::RARM), lhand(KSP::LARM), speed(20)
{
  this->setDefaultSpeed(this->speed);
  this->connect();
}


Robot::~Robot(void)
{
}


void Robot::emesg(const char *mesg, const char *hdr)
{
  std::ostream &strm=this->msgstrm;
  strm << hdr << " Robot::" << mesg << std::endl;
}


#define ARGNUM (4)
const char *ARGV[ARGNUM] = { "-ORBInitRef", NULL, 
			     "-ORBgiopMaxMsgSize", "104857600" };

void Robot::connect(void)
{
  char buf[ARGNUM][128], *argv[ARGNUM];
  for(int i=0; i<ARGNUM; i++) argv[i]=buf[i];
  std::strcpy(argv[0], ARGV[0]);
  std::sprintf(argv[1], "NameService=corbaloc:iiop:%s:2809/NameService", 
	       this->ipaddr.c_str());
  std::strcpy(argv[2], ARGV[2]);
  std::strcpy(argv[3], ARGV[3]);
  
  int argc=ARGNUM;
  try {
    ::CORBA::ORB_var orb = ::CORBA::ORB_init(argc, argv);
    ::CORBA::Object_var obj = orb->resolve_initial_references("NameService");
    CosNaming::NamingContext_var nsref =CosNaming::NamingContext::_narrow(obj);
  
    CORBA::Object_ptr ref;
  
    CosNaming::Name ncName;
    ncName.length(1);
    ncName[0].kind = "";

    ncName[0].id = "sysCom";
    ref = nsref->resolve(ncName);
    this->sysCom = systemCommand::_narrow(ref);

    ncName[0].id = "armServer";
    ref = nsref->resolve(ncName);
    this->arm = armServer::_narrow(ref);

    ncName[0].id = "coordServer";
    ref = nsref->resolve(ncName);
    this->coord = coordServer::_narrow(ref);

    ncName[0].id = "dio";
    ref = nsref->resolve(ncName);
    this->dio = dioPlugin::_narrow(ref);

  } catch(CORBA::SystemException& e) {
    // [TODO] change message properly
    char mesg[128];
    this->emesg("connect(): Caught CORBA::SystemException.");
    std::sprintf(mesg, "connect():   Exception name = %s", e._name());
    this->emesg(mesg);
    throw;

  } catch(CORBA::Exception&) {
    // [TODO] check message properly
    this->emesg("connect(): Caught CORBA::Exception.");
    throw;

  } catch(omniORB::fatalException& fe) {
    // [TODO] check message properly
    char mesg[128];
    this->emesg("connect(): Caught omniORB::fatalException:" );
    std::sprintf(mesg, "connect():   file: %s", fe.file());
    this->emesg(mesg);
    std::sprintf(mesg, "connect():   line: %d", fe.line());
    this->emesg(mesg);
    std::sprintf(mesg, "connect():   mesg: %s", fe.errmsg());
    this->emesg(mesg);
    throw;

  } catch(...) {
    this->emesg("connect(): Caught unknown exception.");
    throw;
  }
  
  this->rarm.connect(this->arm);
  this->larm.connect(this->arm);
  this->rhand.connect(this->arm, this->coord);
  this->lhand.connect(this->arm, this->coord);
}

void Robot::poweroff(void)
{
  ::CORBA::String_var cout;
  this->wait(WHOLE);
  this->sysCom->function("shutdown","", cout);
  return ;
}


//static armPlugin::LngLngSeq seq = {0x0824, 0x077DB};
static float angles[] = {0, 0, 0, 
			 0, 0, -130,  15, 0, 0,
			 0, 0, -130, -15, 0, 0};
static bool dir[] = { false, true, false, 
		      false, true, false, false, false, false,
		      true,  true, false, true,  false, true };

// [TODO] need to check servo ON/OFF state
// [TODO] need to accept anoter calibration pattern...
unsigned long Robot::jointCalib(void)
{
  armServer::LngLngSeq seq(2);
  seq.length(2);
  seq[0] = 0x00824;
  seq[1] = 0x077DB;
  
  ::CORBA::ULong status;
  this->arm->jointCalibration(seq, angles, dir, status);

  return static_cast<unsigned long>(status);
}



void Robot::servoON(void)
{
  this->arm->switchServo(true);
}


void Robot::servoOFF(void)
{
  this->wait(WHOLE);
  this->arm->switchServo(false);
}


void Robot::setDefaultSpeed(int speed)
{
  this->speed=speed;
  this->rarm.setDefaultSpeed(speed);
  this->larm.setDefaultSpeed(speed);
  this->rhand.setDefaultSpeed(speed);
  this->lhand.setDefaultSpeed(speed);
}


static double escapePose[] = {
  0.0, 0.0, 0.0,
// ↓SP用
   9.0, -154.8, -149.9,  116.1, -21.8,  10.0,
  -9.0, -154.8, -149.9, -116.1, -21.8, -10.0
// ↓AP用
//   9.0, -154.8, -149.9,   46.1, -21.8,  10.0,
//  -9.0, -154.8, -149.9,  -46.1, -21.8, -10.0
};

unsigned long Robot::makeEscapePose(int speed)
{
  unsigned long status;
  status=this->makePose(escapePose, speed);

  return status;
}


void Robot::getAngles(double angles[DOFS_WHOLE], bool realFlag)
{
  ::CORBA::Double j[DOFS_WHOLE];
  if (realFlag) {
    this->arm->getJointAnglesNeckReal(j[0], j[1]);
    this->arm->getJointAngleChestReal(j[2]);
    this->arm->getJointAnglesRightArmReal(j[3], j[4], j[5], j[6], j[7], j[8]);
    this->arm->getJointAnglesLeftArmReal(j[9], j[10], j[11], 
					 j[12], j[13], j[14]);
  } else {
    this->arm->getJointAnglesNeck(j[0], j[1]);
    this->arm->getJointAngleChest(j[2]);
    this->arm->getJointAnglesRightArm(j[3], j[4], j[5], j[6], j[7], j[8]);
    this->arm->getJointAnglesLeftArm(j[9], j[10], j[11], j[12], j[13], j[14]);
  }
  
  for (int dof=0; dof<DOFS_WHOLE; dof++) angles[dof]=j[dof];
  
  return ;
}


void Robot::getNeckAngles(double &pan, double &tilt, bool realFlag)
{
  ::CORBA::Double j[DOFS_NECK];
  if (realFlag) {
    this->arm->getJointAnglesNeckReal(j[0], j[1]);
  } else {
    this->arm->getJointAnglesNeck(j[0], j[1]);
  }
  
  pan  = j[0];
  tilt = j[1];

  return ;
}


void Robot::getNeckAngles(double angles[DOFS_NECK], bool realFlag)
{
  ::CORBA::Double j[DOFS_NECK];
  if (realFlag) {
    this->arm->getJointAnglesNeckReal(j[0], j[1]);
  } else {
    this->arm->getJointAnglesNeck(j[0], j[1]);
  }

  for (int dof=0; dof<DOFS_NECK; dof++) angles[dof]=j[dof];
  return ;
}


unsigned long Robot::faceTo(double pan, double tilt, int speed)
{
  if (speed<0) speed=this->speed;
  this->wait(KSP::NECK);
  ::CORBA::ULong status;
  this->arm->setAnglesNeckP(static_cast<double>(pan), static_cast<double>(tilt),
			    static_cast<double>(speed), status);

  return static_cast<unsigned long>(status);
}


unsigned long Robot::faceTo(double angles[2], int speed)
{
  unsigned long status;
  if (speed<0) speed=this->speed;
  status=this->faceTo(angles[0], angles[1],speed);

  return status;
}


unsigned long Robot::turnNeck(double angles[2], int speed)
{
  unsigned long status;
  if (speed<0) speed=this->speed;
  status=this->turnNeck(angles[0], angles[1], speed);

  return status;
}


unsigned long Robot::turnNeck(double pan, double tilt, int speed)
{
  if (speed<0) speed=this->speed;
  this->wait(KSP::NECK);
  ::CORBA::Double j0,j1;
  this->arm->getJointAnglesNeck(j0, j1);
  j0+=static_cast<double>(pan);
  j1+=static_cast<double>(tilt);
  ::CORBA::ULong status;
  this->arm->setAnglesNeckP(static_cast<double>(j0), static_cast<double>(j1),
			    static_cast<double>(speed), status);

  return static_cast<unsigned long>(status);
}


void Robot::getChestAngle(double &angle, bool realFlag)
{
  ::CORBA::Double j;
  if (realFlag) {
    this->arm->getJointAngleChestReal(j);
  } else {
    this->arm->getJointAngleChest(j);
  }
  
  angle = j;
  return ;
}


unsigned long Robot::directTo(double angle, int speed)
{
  if (speed<0) speed=this->speed;
  this->wait(KSP::CHEST);
  ::CORBA::ULong status;
  status=this->arm->setAngleChestP(static_cast<double>(angle),
				   static_cast<double>(speed), status);

  return static_cast<unsigned long>(status);
}


unsigned long Robot::turnChest(double angle, int speed)
{
  if (speed<0) speed=this->speed;
  this->wait(KSP::CHEST);
  ::CORBA::Double j0;
  this->arm->getJointAngleChest(j0);
  j0+=static_cast<double>(angle);
  ::CORBA::ULong status;
  this->arm->setAngleChestP(static_cast<double>(j0), 
			    static_cast<double>(speed), status);

  return static_cast<unsigned long>(status);
}


unsigned long Robot::makePose(const double angles[], int speed)
{
  unsigned long status;
  if (speed<0) speed=this->speed;
  status=this->makePose(angles[0],angles[1],angles[2],
			angles[3],angles[4],angles[5],
			angles[6],angles[7],angles[8],
			angles[9],angles[10],angles[11],
			angles[12],angles[13],angles[14], speed);
  return status;
}

unsigned long Robot::makePose(double jw,  double jn0, double jn1,
			      double jr0, double jr1, double jr2,
			      double jr3, double jr4, double jr5,
			      double jl0, double jl1, double jl2,
			      double jl3, double jl4, double jl5, int speed)
{
  if (speed<0) speed=this->speed;
  this->wait(WHOLE);
  ::CORBA::ULong status;
  this->arm->setAngleChestP(static_cast<double>(jw), 
			    static_cast<double>(speed), status);
  this->arm->setAnglesNeckP(static_cast<double>(jn0), 
			    static_cast<double>(jn1), 
			    static_cast<double>(speed), status);
  this->arm->setJointAnglesRightArmP(static_cast<double>(jr0),
				     static_cast<double>(jr1),
				     static_cast<double>(jr2),
				     static_cast<double>(jr3),
				     static_cast<double>(jr4),
				     static_cast<double>(jr5),
				     static_cast<double>(speed), status);
  this->arm->setJointAnglesLeftArmP(static_cast<double>(jl0),
				    static_cast<double>(jl1),
				    static_cast<double>(jl2),
				    static_cast<double>(jl3),
				    static_cast<double>(jl4),
				    static_cast<double>(jl5),
				    static_cast<double>(speed), status);

  return static_cast<unsigned long>(status);
}

void Robot::wait(int block)
{
  ::CORBA::Octet blk = (block&0xFF);
  this->arm->inMotion(blk, true);
  return ;
}

unsigned short Robot::getDin()
{
  return this->dio->getDin(); 
}


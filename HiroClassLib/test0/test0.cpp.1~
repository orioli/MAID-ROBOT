//
// test0.cpp
//

#include <iostream>
#ifndef _WIN32
#include <unistd.h> // sleep()
#endif

#include "Robot.hpp"

#ifndef IPADDR
#define IPADDR "192.168.128.11"
#endif

#define HIGH_SPEED (90)

int main(int argc, const char *argv[])
{
  const char *ipaddr;
  if (argc<2) ipaddr=IPADDR;
  else ipaddr=argv[1];
  
  KSP::Robot robot(ipaddr);
  
  robot.jointCalib();
  
  //
  // Neck
  //
  robot.faceTo(10,10); // starts to move and returns immediately.
  
  double pt[2];
  pt[0]=30;
  pt[1]=-30;
  robot.faceTo(pt); // waits for finish of previous neck motion, 
                    // then start to move to new position and returns.
  
  robot.wait(KSP::NECK); // or robot.wait()
  double pan, tilt;
  robot.getNeckAngles(pan, tilt);
  std::cout << "neck:       " << pan << ", " << tilt << std::endl;
  robot.getNeckAngles(pan, tilt, true);
  std::cout << "neck(real): " << pan << ", " << tilt << std::endl;
  
  robot.faceTo(10,10,HIGH_SPEED); // speed 100%
  robot.faceTo(pt, HIGH_SPEED);   // speed 100%
  
  robot.turnNeck(-10,10);
  robot.turnNeck(-10,10,HIGH_SPEED); // speed 100%
  pt[0]=-10;
  pt[1]=10;
  robot.turnNeck(pt);
  robot.turnNeck(pt,HIGH_SPEED); // speed 100%
  
  robot.wait(); // or robot.wait(KSP::NECK)
  pt[0]=pt[1]=99.9;       // dummy values
  robot.getNeckAngles(pt);
  std::cout << "neck:       " << pt[0] << ", " << pt[1] << std::endl;
  robot.getNeckAngles(pt, true);
  std::cout << "neck(real): " << pt[0] << ", " << pt[1] << std::endl;
  
  robot.faceTo(0.0, 0.0); // faceTo(0,0) fails. 0 seems null array of int ??
  
  robot.wait(); // or robot.wait(KSP::NECK);
  
  //
  // chest
  //
  robot.directTo(10);
  robot.wait(KSP::CHEST); // or robot.wait()
  robot.getChestAngle(pan);
  std::cout << "chest:       " << pan << std::endl;
  robot.getChestAngle(pan, true);
  std::cout << "chest(real): " << pan << std::endl;
  
  robot.turnChest(-10);
  robot.turnChest(-10, HIGH_SPEED); // speed 100%
  robot.directTo(0.0, HIGH_SPEED);  // speed 100%
  
  robot.wait(); // or robot.wait(KSP::CHEST)
  
  //
  // rarm
  //
  double arm[6];
  arm[0]=0.0;
  arm[1]=-60.0;
  arm[2]=-30.0;
  arm[3]=0.0;
  arm[4]=0.0;
  arm[5]=0.0;
  
  robot.rarm.makePose(arm);
  robot.rarm.moveUpper(10,20,-10);
  robot.rarm.moveFore(10,-10,10);
  robot.rarm.moveUpperTo(0, -60, -30);
  robot.rarm.moveForeTo(0, 0, 0);
  
  robot.rarm.moveUpper(10,20,-10, HIGH_SPEED);
  robot.rarm.moveFore(10,-10,10, HIGH_SPEED);
  robot.rarm.moveUpperTo(0, -60, -30, HIGH_SPEED);
  robot.rarm.moveForeTo(0,0,0, HIGH_SPEED);
  
  arm[0]+=10.0;
  arm[1]+=20.0;
  arm[2]-=10.0;
  arm[3]+=10.0;
  arm[4]-=10.0;
  arm[5]+=10.0;
  robot.rarm.makePose(arm, HIGH_SPEED);
  robot.rarm.makePose(0,-60,-30,0,0,0, HIGH_SPEED);
  robot.rarm.makePose(10,-10, -130, 15, 0, 0);
  
  robot.rarm.wait(); // or robot.wait(KSP::RARM) or robot.wait()
  
  //
  // larm
  //
  arm[0]=0.0;
  arm[1]=-60.0;
  arm[2]=-30.0;
  arm[3]=0.0;
  arm[4]=0.0;
  arm[5]=0.0;
  
  robot.larm.makePose(arm);
  robot.larm.moveUpper(-10,20,-10);
  robot.larm.moveFore(-10,-10,-10);
  robot.larm.moveUpperTo(0, -60, -30);
  robot.larm.moveForeTo(0,0,0);
  
  robot.larm.moveUpper(-10,20,-10, HIGH_SPEED);
  robot.larm.moveFore(-10,-10,-10, HIGH_SPEED);
  robot.larm.moveUpperTo(0, -60, -30, HIGH_SPEED);
  robot.larm.moveForeTo(0,0,0, HIGH_SPEED);
  
  arm[0]-=10.0;
  arm[1]+=20.0;
  arm[2]-=10.0;
  arm[3]-=10.0;
  arm[4]-=10.0;
  arm[5]-=10.0;
  robot.larm.makePose(arm, HIGH_SPEED);
  robot.larm.makePose(0,-60,-30,0,0,0, HIGH_SPEED);
  robot.larm.makePose(-10,-10, -130, -15, 0, 0);
  
  robot.larm.wait(); // or robot.wait(KSP::LARM) or robot.wait()
  
  
  //
  // both arm
  //
  robot.rarm.setDefaultSpeed(HIGH_SPEED);
  robot.larm.setDefaultSpeed(HIGH_SPEED);
  robot.rarm.makePose( 10, -10, -100,  15, 0, 0);
  robot.larm.makePose(-10, -10, -100, -15, 0, 0);
  
  robot.wait(KSP::RARM);
  robot.wait(KSP::LARM);
  
  robot.rarm.makePose( 10, -10,  -80, -60, 0, 0);
  robot.larm.makePose(-10, -10, -130, -30, 0, 0);
  
  robot.wait(KSP::RARM | KSP::LARM); // or wait(KSP::LARM); wait(KSP::RARM);
                                     // or wait()
  
  robot.rarm.makePose( 10, -10, -130,  30, 0, 0);
  robot.larm.makePose(-10, -10,  -80,  60, 0, 0);
  
  robot.rarm.wait();
  robot.larm.wait();
  
  robot.rarm.makePose( 10, -10,  -80, -60, 0, 0);
  robot.larm.makePose(-10, -10, -130, -30, 0, 0);
  
  robot.wait();
  
  robot.rarm.makePose( 10, -10, -130,  30, 0, 0);
  robot.larm.makePose(-10, -10,  -80,  60, 0, 0);
  
  robot.wait();
  
  robot.rarm.makePose( 10, -10, -100,  15, 0, 0);
  robot.larm.makePose(-10, -10, -100, -15, 0, 0);

  robot.wait();
  //
  // hand
  //
  double rxyz[3], lxyz[3], rpy[3];
  rxyz[0]= 300;  lxyz[0]= 300;
  rxyz[1]=-200;  lxyz[1]= 200;
  rxyz[2]= 150;  lxyz[2]= 150;
  robot.rhand.moveTo(rxyz);
  robot.rhand.wait();
  robot.lhand.moveTo(lxyz);
  robot.lhand.wait();
  
  robot.rhand.resetPose();
  robot.lhand.resetPose();
  
  rxyz[0] = lxyz[0] = 50;
  rxyz[1] = lxyz[1] = 50;
  rxyz[2] = lxyz[2] =  0;
  robot.rhand.move(rxyz);
  robot.lhand.move(lxyz);
  
  rpy[0] = -10;
  rpy[1] =-130;
  rpy[2] = -10;
  robot.rhand.turnTo(rpy);
  robot.lhand.turnTo(rpy);
  
  rpy[0] =  10;
  rpy[1] = -40;
  rpy[2] =  10;
  robot.rhand.turn(rpy);
  robot.lhand.turn(rpy);
  
  rxyz[0]= 300;  lxyz[0]= 300;
  rxyz[1]=-200;  lxyz[1]= 200;
  rxyz[2]= 150;  lxyz[2]= 150;
  robot.rhand.moveTo(rxyz, HIGH_SPEED);
  robot.lhand.moveTo(lxyz, HIGH_SPEED);
  
  robot.rhand.resetPose(HIGH_SPEED);
  robot.lhand.resetPose(HIGH_SPEED);
  
  rxyz[0] = lxyz[0] = 50;
  rxyz[1] = lxyz[1] = 50;
  rxyz[2] = lxyz[2] =  0;
  robot.rhand.move(rxyz, HIGH_SPEED);
  robot.lhand.move(lxyz, HIGH_SPEED);
  
  rpy[0] = -10;
  rpy[1] =-130;
  rpy[2] = -10;
  robot.rhand.turnTo(rpy, HIGH_SPEED);
  robot.lhand.turnTo(rpy, HIGH_SPEED);
  
  rpy[0] = 10;
  rpy[1] =-40;
  rpy[2] = 10;
  robot.rhand.turn(rpy, HIGH_SPEED);
  robot.lhand.turn(rpy, HIGH_SPEED);

  robot.wait();
  
  
  //
  // hand (ComplementByLine)
  //
  
  robot.rhand.setDefaultComplementType(KSP::COMPLEMENTBY_LINE);
  robot.lhand.setDefaultComplementType(KSP::COMPLEMENTBY_LINE);
  
  rxyz[0]= 300;  lxyz[0]= 300;
  rxyz[1]=-200;  lxyz[1]= 200;
  rxyz[2]= 200;  lxyz[2]= 200;
  robot.rhand.moveTo(rxyz);
  robot.lhand.moveTo(lxyz);

  robot.wait();

  for(int i=0; i<3; i++) {
    rxyz[0] = lxyz[0] =   0;
    rxyz[1] = lxyz[1] =   0;
    rxyz[2] = lxyz[2] =-250;
    robot.rhand.move(rxyz, 20, KSP::COMPLEMENTBY_ANGLE);
    robot.lhand.move(lxyz, 20, KSP::COMPLEMENTBY_ANGLE);
    
    robot.wait();
    
    rxyz[0]= 300;  lxyz[0]= 300;
    rxyz[1]=-200;  lxyz[1]= 200;
    rxyz[2]= 200;  lxyz[2]= 200;
    robot.rhand.moveTo(rxyz);
    robot.lhand.moveTo(lxyz);
    
    robot.wait();
  }  
  
  robot.rhand.setDefaultComplementType(KSP::COMPLEMENTBY_ANGLE);
  robot.lhand.setDefaultComplementType(KSP::COMPLEMENTBY_ANGLE);
  
  robot.rarm.makePose( 10, -10, -130,  15, 0, 0);
  robot.larm.makePose(-10, -10, -130, -15, 0, 0);
  
  robot.wait();

  //
  // whole
  //
  double angles[KSP::DOFS_WHOLE];
  angles[ 0] =   5.0; // chest-pan
  angles[ 1] =  10.0; // neck-pan
  angles[ 2] =  10.0; // neck-tilt
  angles[ 3] =  30.0; // rarm0 (shoulder)
  angles[ 4] = -30.0; // rarm1 (shoulder)
  angles[ 5] =-120.0; // rarm2 (elbow)
  angles[ 6] =  30.0; // rarm3 (wrist)
  angles[ 7] = -20.0; // rarm4 (wrist)
  angles[ 8] =  20.0; // rarm5 (wrist)
  angles[ 9] = -30.0; // larm0 (shoulder)
  angles[10] = -30.0; // larm1 (shoulder)
  angles[11] =-120.0; // larm2 (elbow)
  angles[12] = -30.0; // larm3 (wrist)
  angles[13] = -20.0; // larm4 (wrist)
  angles[14] = -20.0; // larm5 (wrist)

  robot.makePose(angles);
  robot.makePose(0,0,0,           // chest, neck
		 0,0,-90,0,0,0,   // rarm
		 0,0,-90,0,0,0);  // larm
  robot.makePose(angles, HIGH_SPEED);
  robot.makePose(0,0,0,           // chest, neck
		 0,0,-90,0,0,0,   // rarm
		 0,0,-90,0,0,0, HIGH_SPEED); // larm

  //
  // default speed
  //
  robot.setDefaultSpeed(10);
  robot.faceTo(10,10);
  robot.directTo(5);

  rxyz[0]= 150;  lxyz[0]= 150;
  rxyz[1]=-200;  lxyz[1]= 200;
  rxyz[2]= 150;  lxyz[2]= 150;
  robot.rhand.moveTo(rxyz);
  robot.lhand.moveTo(lxyz);

  robot.setDefaultSpeed(50);
  robot.makePose(0,0,0,
		 0,0,-90,0,0,0,
		 0,0,-90,0,0,0);

  robot.setDefaultSpeed(20);

  robot.makeEscapePose();
  robot.wait();
  robot.servoOFF();

  //robot.poweroff();

  return 0;
}

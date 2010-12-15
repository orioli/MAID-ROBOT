#! /usr/bin/python -i

import demo;

real=1
speed=50

def setSpeed(spd=20):
    global speed
    speed=spd

def showCoord(hand=0):
    xyzrpy=demo.KSP.dblArray(6)
    if(hand==0):
        demo.robot.rhand.getCoord(xyzrpy)
    else:
        demo.robot.lhand.getCoord(xyzrpy)
    for i in range(6):
        print str(xyzrpy[i])+" ",
    print ""

def showAngles(part=0):
    if(part==0):
        angles=demo.KSP.dblArray(demo.KSP.DOFS_WHOLE)
        demo.robot.getAngles(angles,real)
        for i in range(demo.KSP.DOFS_WHOLE):
            print str(angles[i])+" ",
        print ""
    else:
        angles=demo.KSP.dblArray(demo.KSP.DOFS_ARM)
        if(part==1):
            demo.robot.rarm.getAngles(angles,real)
        else:
            demo.robot.larm.getAngles(angles,real)
        for i in range(demo.KSP.DOFS_ARM):
            print str(angles[i])+" ",
        print ""


def moveTo_xyz(hand=0,x=330,y=-170,z=130):
    xyz=demo.KSP.dblArray(3)
    xyz[0]=x
    xyz[1]=y
    xyz[2]=z
    if(hand==0):
        state=demo.robot.rhand.moveTo(xyz,speed,0)
    else:
        state=demo.robot.lhand.moveTo(xyz,speed,0)
    print state

def move_xyz(hand=0,x=0,y=0,z=0):
    xyz=demo.KSP.dblArray(3)
    xyz[0]=x
    xyz[1]=y
    xyz[2]=z
    if(hand==0):
        state=demo.robot.rhand.move(xyz,speed,0)
    else:
        state=demo.robot.lhand.move(xyz,speed,0)
    print state

def turnTo_rpy(hand=0,r=0,p=-90,y=0):
    rpy=demo.KSP.dblArray(3)
    rpy[0]=r
    rpy[1]=p
    rpy[2]=y
    if(hand==0):
        state=demo.robot.rhand.turnTo(rpy,speed,0)
    else:
        state=demo.robot.lhand.turnTo(rpy,speed,0)
    print state

def turn_rpy(hand=0,r=0,p=0,y=0):
    rpy=demo.KSP.dblArray(3)
    rpy[0]=r
    rpy[1]=p
    rpy[2]=y
    if(hand==0):
        state=demo.robot.rhand.turn(rpy,speed,0)
    else:
        state=demo.robot.lhand.turn(rpy,speed,0)
    print state


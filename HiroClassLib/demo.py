#! /usr/bin/python -i
# -*- coding: utf-8 -*-

"""@package demo
ロボット制御クラスライブラリをpythonから利用するサンプル
a sample python script using "class library to control hiro"
"""

import KSP;

robot = KSP.Robot("192.168.128.3");
rbt=robot;

arm   = KSP.dblArray(KSP.DOFS_ARM);   # for robot.[rl]arm.getAngles()
whole = KSP.dblArray(KSP.DOFS_WHOLE); # for robot.getAngles()

def jointCalib():
	robot.jointCalib()

def goInit():
    """ @brief ロボットを初期姿勢まで動かす """
    robot.makePose(0,0,0, 
                 -0.6, 0, -100,  15.2, 9.4,  3.2,
                  0.6, 0, -100, -15.2, 9.4, -3.2, 10);
    return ;

def goEscape():
    ## @ロボットをエスケープ姿勢まで動かす
    robot.makeEscapePose(10);
    return ;

def servoOFF():
    ## @全身のサーボを切る
    robot.servoOFF();
    return;

def servoON():
    robot.servoON();
    return;

def shutdown():
    robot.poweroff();
    return;

def test0():
    robot.rhand.setDefaultComplementType(KSP.COMPLEMENTBY_LINE);
    robot.lhand.setDefaultComplementType(KSP.COMPLEMENTBY_LINE);
    rxyz = KSP.dblArray(3);
    lxyz = KSP.dblArray(3);
    
    rxyz[0]= 300;  lxyz[0]= 300;
    rxyz[1]=-200;  lxyz[1]= 200;
    rxyz[2]= 200;  lxyz[2]= 200;

    robot.rhand.moveTo(rxyz);
    robot.lhand.moveTo(lxyz);
    
    robot.wait();
    for i in range(3):
        robot.rhand.move(0,0,50, 20, KSP.COMPLEMENTBY_ANGLE);
        robot.lhand.move(0,0,50, 20, KSP.COMPLEMENTBY_ANGLE);
        robot.wait();
        
        robot.rhand.moveTo(rxyz);
        robot.lhand.moveTo(lxyz);
        robot.wait();

def nod():
    tiltAngles = [ -20, 20, -20, 20, 0]
    for tilt in tiltAngles:
        robot.faceTo(0, tilt, 50)
        robot.wait()

def nodNo():
    panAngles = [ -20, 20, -20, 0]
    for pan in panAngles:
        robot.faceTo(pan, 0, 50)
        robot.wait()

def showDIN():
    ret = robot.getDin()
    for i in range(16):
       print str((ret>>i & 1)) + " ",
    print ""

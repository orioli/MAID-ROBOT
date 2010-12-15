#! /usr/bin/python
import os
import sys;
sys.path.append("lib")
import HiroHands;

BAUDRATE = 115200
COM_PORT = "COM2"
ANGLE_FINGER0_OPEN =  -90
ANGLE_FINGER1_OPEN =    0
ANGLE_FINGER0_CLOSE =  18
ANGLE_FINGER1_CLOSE = -16




classlibDir = "../HiroClassLib"
if classlibDir != "" and os.path.exists(classlibDir):
    sys.path.append(classlibDir)
    from demo import *

def Hand_init():
    global logger, hands, rh, lh
    logger = HiroHands.LoggerStderr();
    hands = HiroHands.HiroHands(logger);
    if hands.init(COM_PORT, BAUDRATE, False) < 0:
        sys.exit(-1);
    rh = hands.rightHand;
    lh = hands.leftHand;
    rh.setRange(ANGLE_FINGER0_OPEN, ANGLE_FINGER1_OPEN, ANGLE_FINGER0_CLOSE, ANGLE_FINGER1_CLOSE);
    lh.setRange(ANGLE_FINGER0_OPEN, ANGLE_FINGER1_OPEN, ANGLE_FINGER0_CLOSE, ANGLE_FINGER1_CLOSE);

def Hand_servoON():
    rh.servoON()
    lh.servoON()

def Hand_servoOFF():
    rh.servoOFF()
    lh.servoOFF()
    
def Hand_openRight():
    rh.close(50, 0.2); #( ratio against full range[%], time[s])

def Hand_openLeft():
    lh.close(50, 0.2); #( ratio against full range[%], time[s])
    
def Hand_closeRight():
    rh.close(100, 0.2); #( ratio against full range[%], time[s])

def Hand_closeLeft():
    lh.close(100, 0.2); #( ratio against full range[%], time[s])
        
def Hand_finalize():
    hands.release();

def Hand_showAngle():
    print "RH: ",
    for i in range(4):
        ang = rh.readAngle(i)/10.0;
        print str(ang) + " ",
    print ""

    print "LH: ",
    for i in range(4):
        ang = lh.readAngle(i)/10.0;
        print str(ang) + " ",
    print ""









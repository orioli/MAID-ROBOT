#! /usr/bin/python

import os;
import sys;
import time;

import HiroHands;


logger=HiroHands.LoggerStderr();
hands=HiroHands.HiroHands(logger);

if (os.name=='posix'):
    if (hands.init("/dev/ttyUSB0", 115200, True)<0):
        sys.exit(-1);
elif (os.name=='nt'):
    if (hands.init("COM5", 115200, True)<0):
        sys.exit(-1);
else:
    sys.stderr.write("** unknown system: "+os.anme+" **");
    sys.exit(-1);

rh=hands.rightHand;

sys.stderr.write("Servo ON\n");
rh.servoON();

sys.stderr.write("OPEN hand\n");
rh.setRange(-90, 0, 18, -16);
rh.close(0, 2);
time.sleep(2);

sys.stderr.write("close hand\n");
for i in range(0,101,5):
    rh.close(i, 0.5);
    time.sleep(0.5);

sys.stderr.write("OPEN hand\n");
rh.setRange(-90, 90, 18, -16);
rh.close(0, 2);
time.sleep(2);

sys.stderr.write("close hand\n");
for i in range(0,101,5):
    rh.close(i, 0.5);
    time.sleep(0.5);

sys.stderr.write("wait for 5 sec\n");
time.sleep(5);
  
  
sys.stderr.write("release\n");
hands.release();

sys.stderr.write("Done\n");

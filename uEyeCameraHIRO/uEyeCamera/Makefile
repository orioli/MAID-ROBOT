# macro
CC	= g++ 
CFLAGS	= -O3 -Wall -D__LINUX__ -fomit-frame-pointer
LDFLAGS	= -L. -L../uEyeCamera/bin
INCLUDES = -I. -I/usr/include/python2.5/ `pkg-config --cflags opencv` -I../classLib/
LIBS	= -lueye_api

LIB_DIR = ./
T_LIB	= libuEyeCamera.so
OBJ_LIB	= uEyeCamera.o

PYEXT_DIR = ../uEyeCamPy/
T_PYEXT = uEyeCam.so
OBJ_PYEXT = uEyeCamPy.o

SAMPLE1_DIR = ../stereoCaptureDemo/
T_SAMPLE1 = stereoCaptureDemo
OBJ_SAMPLE1 = stereoCaptureDemo.o

SAMPLE2_DIR = ../camShiftDemo/
T_SAMPLE2= camShiftDemo
OBJ_SAMPLE2 = camShiftDemo.o

TARGETS = $(T_LIB) $(T_PYEXT) $(T_SAMPLE1) $(T_SAMPLE2)
OBJS 	= $(OBJ_LIB) $(OBJ_PYEXT) $(OBJ_SAMPLE1) $(OBJ_SAMPLE2)

# rule
all:	$(T_LIB) $(T_PYEXT) $(T_SAMPLE1) $(T_SAMPLE2) post_pro

$(T_LIB): $(OBJ_LIB)
	cd $(LIB_DIR)
	$(CC) $(LDFLAGS) -o $@ $(OBJ_LIB) $(LIBS) -fPIC -shared 
	mv $(T_LIB) ./bin/
	cd -

$(T_PYEXT): $(PYEXT_DIR)$(OBJ_PYEXT)
	cd $(PYEXT_DIR)
	$(CC) $(LDFLAGS) -o $@ $(OBJ_PYEXT) $(LIBS) -fPIC -shared -luEyeCamera -ldl -lrt `pkg-config --libs opencv`
	mv $(T_PYEXT) ../uEyeCamera/bin/
	cd -

$(T_SAMPLE1): $(SAMPLE1_DIR)$(OBJ_SAMPLE1)
	cd $(SAMPLE1_DIR)
	$(CC) $(LDFLAGS) -o $@ $(OBJ_SAMPLE1) $(LIBS) -luEyeCamera `pkg-config --libs opencv`
	mv $(T_SAMPLE1) ../uEyeCamera/bin/
	cd - 

$(T_SAMPLE2): $(SAMPLE2_DIR)$(OBJ_SAMPLE2)
	cd $(SAMPLE2_DIR)
	$(CC) $(LDFLAGS) -o $@ $(OBJ_SAMPLE2) $(LIBS) -luEyeCamera `pkg-config --libs opencv` `pkg-config --libs omniORB4` -L../classLib/ -lksp
	mv $(T_SAMPLE2) ../uEyeCamera/bin/
	cd -

post_pro:
	ln --force -s ../../classLib/libksp.so ./bin/
	ln --force -s ../../classLib/KSP.py ./bin/
	ln --force -s ../../classLib/_KSP.so ./bin/
	yes n|cp -i Release/stereoCaptureDemo.py ./bin/
	yes n|cp -i Release/camShiftDemo.py ./bin/

clean:
	rm -rf ./bin/libksp.so ./bin/KSP.py ./bin/KSP.pyc ./bin/_KSP.so
	rm -rf ./bin/stereoCaptureDemo.py ./bin/camShiftDemo.py
	rm -rf ./bin/$(T_LIB) ./bin/$(T_PYEXT) ./bin/$(T_SAMPLE1) ./bin/$(T_SAMPLE2)
	rm -rf ./*.o ./*~ ./#* ./bin/*~ ./bin/#* 

.cpp.o: 
	$(CC) $(CFLAGS) $(INCLUDES) -c $<




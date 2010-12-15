
OS:=$(shell uname -s)

GXX=g++
GXXD=$(GXX)
CXXFLAGS=-Wall -O4 -D_REENTRANT

SERIDEV=/dev/ttyUSB0
BAUDRATE=115200

LIBBASE=HiroHands
LIBDIR=../lib
LIB=$(LIBDIR)/lib$(LIBBASE).so
INC=$(LIBDIR)

LOPT = -L$(LIBDIR) -Wl,-rpath $(LIBDIR) -l$(LIBBASE)

CXXFLAGS += -DBAUDRATE=$(BAUDRATE) -I$(INC)

PYCONFIG:=python-config
SWIG_CFLAGS := $(shell $(PYCONFIG) --includes) -D_REENTRANT
SWIG_LIBS :=

ifeq ($(OS),Linux)
  CXXFLAGS += -DDEVICE=\"$(SERIDEV)\" -DPOSIX_DEVIO
  CXXFLAGS += -DUSING_ECHOBACK_IF       # for UTS-485
  SWIG_CFLAGS += -DUNIX  -DLINUX
endif


all: test0

-include test0.d

test0: test0.o $(LIB)
	$(GXX) -o $@ $^	

$(LIB):
	(cd $(dir $@); make $(notdir $@))

%.d:%.cpp
	$(GXXD) -MM -I$(INC) -o $@ $<

clean::
	/bin/rm -rf *~ *.o *.d

cleanall:: clean
	/bin/rm -rf test0 test1
	/bin/rm -rf *.suo *.ncb *.sln *.vcproj.* Debug Release


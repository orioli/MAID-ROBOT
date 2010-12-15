
OS:=$(shell uname -s)

ifeq ($(OS),Linux)
GXX=g++
GXXD=$(GXX)
else
CXX=QCC -V3.3.5,gcc_ntox86_cpp
GXX=$(CXX)
GXXD=i386-pc-nto-qnx6.3.0-g++
endif
CXXFLAGS=-Wall -O4 -D_REENTRANT

TARGET:=HiroHands

SERIDEV=/dev/ttyUSB0
BAUDRATE=115200

SUBS:= Futaba485 SerialIF Logger

CXXFLAGS += -DBAUDRATE=$(BAUDRATE)

SWIG_LIBS :=

ifeq ($(OS),Linux)
  PYCONFIG:=python-config
  SWIG_CFLAGS := $(shell $(PYCONFIG) --includes) -D_REENTRANT
  CXXFLAGS += -DDEVICE=\"$(SERIDEV)\" -DPOSIX_DEVIO
  CXXFLAGS += -DUSING_ECHOBACK_IF       # for UTS-485
  SWIG_CFLAGS += -DUNIX  -DLINUX
all: $(TARGET).py lib$(TARGET).so
else 
  CXXFLAGS += -DDEVICE=\"$(SERIDEV)\" -DPOSIX_DEVIO
  CXXFLAGS += -DUSING_ECHOBACK_IF       # for UTS-485
all: lib$(TARGET).so
endif

-include test0.d test1.d HiroHands.d $(addsuffix .d,$(SUBS))

%.d:%.cpp
	$(GXXD) -MM -o $@ $<

lib$(TARGET).so: $(TARGET).o $(addsuffix .o,$(SUBS))
	$(GXX) -o $@ -shared $^

%.py:_%.so

$(TARGET).py: _$(TARGET).so

_$(TARGET).so: $(TARGET)_wrap.o $(TARGET).o $(addsuffix .o,$(SUBS))
	$(GXX) -shared -o $@ $^ $(SWIG_LIBS)

%_wrap.o:%_wrap.cpp
	$(GXX) -c $(SWIG_CFLAGS) $<

%_wrap.cpp:%.i
	swig -c++ -python -o $@ $<

clean::
	/bin/rm -rf *~ *.o *.d
	/bin/rm -rf $(TARGET)_wrap.cpp

cleanall:: clean
	/bin/rm -rf test0 test1
	/bin/rm -rf *.suo *.ncb *.sln *.vcproj.* Debug Release
	/bin/rm -rf $(TARGET).py $(TARGET).pyc _$(TARGET).so
	/bin/rm -rf $(TARGET)_wrap.cxx Hirohands.exp Hirohands.dll
	/bin/rm -rf $(TARGET).lib $(TARGET).pdb _$(TARGET).pyd 
	/bin/rm -rf lib$(TARGET).so

TOOLS := jointCalib

IDLDIR=idls
IDLS= hiroCommonStatus statusPlugin servoPlugin protectPlugin safetyPlugin jointAnglePlugin linearPlugin coordServer armServer dioPlugin systemCommand OpenHRPCommon HRPcontroller 
IDLHPP=$(addsuffix .hpp,$(IDLS))

CLASS:=Robot
CLASS_OBJS:=$(addsuffix .o,$(CLASS) $(IDLS))

CXX:=g++
CXXFLAGS:= -Wall -O4 -I. -fPIC -D_REENTRANT
LIBS:=-lomniORB4 -L. -Wl,-rpath . -lksp

PYCONFIG=python-config
SWIG_CFLAGS = $(shell $(PYCONFIG) --includes) -DUNIX -DLINUX -D_REENTRANT

all: libksp.so  $(TOOLS) _KSP.so

jointCalib: jointCalib.o libksp.so
	$(CXX) -o $@ $^ $(LIBS)

libksp.so: $(CLASS_OBJS)
	$(CXX) -shared -o $@ $^

_%.so: %_wrap.o libksp.so
	$(CXX) -shared -o $@ $< $(LIBS)

%_wrap.cpp: %.ipy
	swig -python -c++ $(SWIG_CFLAGS) -o $@ $<

%_wrap.o: %_wrap.cpp
	$(CXX) -c $(CXXFLAGS) $(SWIG_CFLAGS) -o $@ $<

%.o:%.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

%.hpp:$(IDLDIR)/%.idl
	omniidl -bcxx -Wbh=.hpp -Wbs=.cpp -Wbtf $<

DEPS:=$(addsuffix .dep,$(CLASS) $(TOOLS))
-include $(DEPS)

%.dep:%.cpp $(IDLHPP)
	$(CXX) -MM $(CXXFLAGS) -o $@ $<

.PRECIOUS:%.hpp

man:
	doxygen doxygen.conf		

clean::
	/bin/rm -f $(CLASS_OBJS) $(addsuffix .o,$(TOOLS))
	/bin/rm -f *~

cleanall:: clean
	/bin/rm -f $(DEPS) libksp.so $(TOOLS)
	/bin/rm -f $(IDLHPP) $(addsuffix .cpp,$(IDLS)) 
	/bin/rm -f _KSP.so KSP.py KSP.pyc KSP_wrap.cpp
	/bin/rm -rf Release _KSP.pyd

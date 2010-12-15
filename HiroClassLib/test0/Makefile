TESTS := test0

LIBKSP_DIR=../

CXX:=g++
CXXFLAGS:= -Wall -O4 -I. -I$(LIBKSP_DIR) -fPIC -D_REENTRANT
LIBS:=-lomniORB4 -L$(LIBKSP_DIR) -Wl,-rpath .. -lksp

all: $(TESTS)

test0: test0.o
	$(CXX) -o $@ $^ $(LIBS)

%.o:%.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

DEPS:=$(addsuffix .dep,$(TESTS))
-include $(DEPS)

%.dep:%.cpp
	$(CXX) -MM $(CXXFLAGS) -o $@ $<

clean::
	/bin/rm -f $(addsuffix .o,$(TESTS))
	/bin/rm -f *~

cleanall:: clean
	/bin/rm -f $(TESTS) $(DEPS)


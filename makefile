PROG = flippity
PROGS := $(basename $(wildcard *.cpp))
LIBS = -lX11 -pthread $(shell pkg-config --libs allegro)
# CXX = /opt/gcc-4.9.0/bin/g++

all: $(PROGS)

%: %.cpp
	$(CXX) -std=c++11 -Wall -o $@ $< $(LIBS)

run: $(PROG)
	LD_LIBRARY_PATH=/opt/gcc-4.9.0/lib64 ./$(PROG)

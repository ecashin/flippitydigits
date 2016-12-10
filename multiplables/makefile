BOOST = $$HOME/opt/boost_1_62_0

CPPFLAGS = -I$(BOOST)
CFLAGS = -Wall -g -O2 -std=c++11
LDFLAGS = -L$(BOOST)/stage/lib
LIBS = -lboost_program_options

.PHONY: run

multiplables: main.cc
	g++ $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

run: multiplables
	./$<
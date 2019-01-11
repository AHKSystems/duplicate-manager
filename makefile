CXX=g++
RM=rm -f
CPPFLAGS=-std=c++17
LDFLAGS=
LDLIBS=


all: dupman

dupman: dupman.o
	$(CXX) $(LDFLAGS) date.o fs.o output.o dupman.o -o dupman.exe

dupman.o: dupman.cpp output.o
	$(CXX) $(CPPFLAGS) -c dupman.cpp

output.o: output.cpp output.h fs.o
	$(CXX) $(CPPFLAGS) -c output.cpp

fs.o: fs.cpp fs.h date.o
	$(CXX) $(CPPFLAGS) -c fs.cpp

date.o: date.cpp date.h
	$(CXX) $(CPPFLAGS) -c date.cpp

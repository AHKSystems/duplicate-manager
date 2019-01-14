CXX=g++
RM=rm -f
CPPFLAGS=-std=c++17 -Wall -Iinclude
LDFLAGS=

OBJS=date.o fs.o output.o main.o
EXE=dupman.exe

all: dupman

dupman: main.o
	$(CXX) $(LDFLAGS) -o $(EXE) $(OBJS)

main.o: main.cpp output.o
	$(CXX) -c $(CPPFLAGS) main.cpp

output.o: source/output.cpp include/output.h fs.o
	$(CXX) -c $(CPPFLAGS) source/output.cpp

fs.o: source/fs.cpp include/fs.h date.o
	$(CXX) -c $(CPPFLAGS) source/fs.cpp

date.o: source/date.cpp include/date.h
	$(CXX) -c $(CPPFLAGS) source/date.cpp

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) $(EXE)

CXX=g++
RM=rm -f
CPPFLAGS=-std=c++17 -Iinclude
LDFLAGS=

OBJS=date.o fs.o output.o dupman.o
SRC=source
INC=include
EXE=dupman.exe

all: dupman

dupman: dupman.o
	$(CXX) $(LDFLAGS) -o $(EXE) $(OBJS)

dupman.o: $(SRC)/dupman.cpp output.o
	$(CXX) -c $(CPPFLAGS) $(SRC)/dupman.cpp

output.o: $(SRC)/output.cpp $(INC)/output.h fs.o
	$(CXX) -c $(CPPFLAGS) $(SRC)/output.cpp

fs.o: $(SRC)/fs.cpp $(INC)/fs.h date.o
	$(CXX) -c $(CPPFLAGS) $(SRC)/fs.cpp

date.o: $(SRC)/date.cpp $(INC)/date.h
	$(CXX) -c $(CPPFLAGS) $(SRC)/date.cpp

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) $(EXE)

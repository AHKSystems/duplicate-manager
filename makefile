all: simple

simple: date.o fs.o output.o
	g++ -std=c++17 date.o fs.o output.o dupman.o -o dupman.exe

date.o: date.cpp date.h
	g++ -std=c++17 -c date.cpp

fs.o: fs.cpp fs.h date.h
	g++ -std=c++17 -c fs.cpp

output.o: output.cpp output.h fs.h
	g++ -std=c++17 -c output.cpp

dupman.o: output.cpp output.h
	g++ -std=c++17 -c dupman.cpp

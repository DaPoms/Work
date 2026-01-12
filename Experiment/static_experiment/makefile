# for windows, use "applicationName.exe" in terminal to run makefile
# On unix (School's server uses unix), use ./applicationName

test: main.o staticTest.o
	g++ -c main.o staticTest.o -o test

main: main.cpp staticTest.h
	g++ -c main.cpp 

staticTest: staticTest.cpp staticTest.h
	g++ -c staticTest.cpp

application: p1.o scoreboard.o worddata.o sortarr.o
	g++ -o application p1.o scoreboard.o worddata.o sortarr.o

p1.o: p1.cpp scoreboard.h 
	g++ -c p1.cpp

sortarr.o: sortarr.cpp sortarr.h worddata.h scoreboard.h
	g++ -c sortarr.cpp

worddata.o: worddata.cpp worddata.h
	g++ -c worddata.cpp

scoreboard.o: scoreboard.cpp scoreboard.h
	g++ -c scoreboard.cpp

taxtracker: p2.o stock.o stockhist.o
	g++ p2.o stock.o stockhist.o -o taxtracker

p2.o: p2.cpp stock.h stockhist.h
	g++ -c p2.cpp

stockhist.o: stockhist.cpp stockhist.h
	g++ -c stockhist.cpp

stock.o: stock.cpp stock.h
	g++ -c stock.cpp



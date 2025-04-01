listTest: project4.o OrderedLinkedList.o Node.o 
	g++ project4.o OrderedLinkedList.o Node.o -o listTest

project4.o: project4.cpp OrderedLinkedList.h
	g++ -c project4.cpp

OrderedLinkedList.o: OrderedLinkedList.cpp OrderedLinkedList.h Node.h
	g++ -c OrderedLinkedList.cpp

Node.o: Node.cpp Node.h
	g++ -c Node.cpp

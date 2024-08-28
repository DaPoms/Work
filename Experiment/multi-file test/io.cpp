#include <iostream>
#include "io.h"

int readNumber()
{
	std::cout << "Enter a number to add: ";

	int x{};
	std::cin >> x;
	return x;
}

void writeAnswer(int x)
{
	std::cout << "The answer is: " << x << '\n';
}

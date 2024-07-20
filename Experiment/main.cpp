#include <iostream>
#include <iomanip>
// #include <cstdint> reminder! This is used for specific int sizes

#include <iostream>

void print(int x)
{
	std::cout << x << '\n';
}

int main()
{
	system("CLS");

	
	//print( static_cast<int>(5.5) ); //Static cast makes the compiler happy w/casting loss


	char x{97};
	std::cout << static_cast<int>(x); //You can use casting to print char code #, code is an int



	/*
	char x{};
	std::cout << "enter a 3 letter word: ";

	std::cin >> x;
	std::cout << x;
	std::cin >> x;
	std::cout << x;
	std::cin >> x;
	std::cout << x;
*/
	
}


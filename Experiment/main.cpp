
//#include <iomanip>
// #include <cstddouble> reminder! This is used for specific double sizes
//#include <bitset>
#include <iostream>


constexpr double mult(double x, double y)
{
	return x * y;
}

int main()
{

constexpr double num{ mult(3.2, 5.4) }; //to put a value from a function inside a constant, the function must be a constant
std::cout << num;	
	
}


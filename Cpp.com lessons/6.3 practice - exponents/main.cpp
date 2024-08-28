#include <iostream>
#include <cmath>
int main()
{
    std::cout << std::pow(5, 12); // Does 5 to the 12th power, leads to imprecision (a few thousand off)
    std::cout << '\n' << std::pow(3.5, 3.0); //pow function takes an returns a double, converting ints to double
}

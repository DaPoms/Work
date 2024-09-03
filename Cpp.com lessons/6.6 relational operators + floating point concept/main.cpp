#include <iostream>

int main()
{
    
    
//This shows all the true cases
    std::cout << (3 < 5) << '\n';
    std::cout << (5 <= 5) << '\n';
    std::cout << (5 > 3) << '\n';
    std::cout << (5 >= 5) << '\n';
    std::cout << (5 == 5) << '\n';
    std::cout << (5 != 3) << '\n';

    if (!(5 + 3 == 2))
        std::cout << "This expression evaluates to true!\n";

bool boo{false};
    if (!boo)
        std::cout << "This is a concise way to show: if boo != true OR if boo == false\n";



/////////////Floating point example
double x{100.0 - 99.99};
double y{10.0 - 9.99};

std::cout << (x == y); //values are actually different due to rounding errors
std::cout << '\n' << x << '\n' << y; //won't show in code but does show in debugger

std::cout << '\n' << std::boolalpha << (0.3 == (0.2 + 0.1) ); //don't use == or != with doubles (or floats),
//unless both values are only variables with literals (no operators applied) or just literals

x = 9.9;
y= 9.9;
std::cout << '\n' << (x == y); //only real case to use == or != with floats/doubles, otherwise, you need to make your own function to get this to work 
}

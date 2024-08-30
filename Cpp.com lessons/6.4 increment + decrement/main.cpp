#include <iostream>
int main()
{
    int a{1};
    int b{1};
    int c{1};
    int d{1};
    int e{1};
    int f{1};

    std::cout << "Pre increment test \nA before: " << a;
    b = a++; //post inc test subject, b will stay same, a will = 2
    std::cout << "\nA after: " << a << ". a made b = " << b << '\n';

    std::cout << "Pre decrement test \nC before: " << c  ;
    d = c--; //post dec test subject, c will = 0, d will = 2
    std::cout << "\nC after: " << a << ". a made b = " << b << '\n'; //doing post decrement causes the 
    ++e; //pre increment
    --f; //pre decrement
    std::cout << e << '\n' << f;

    
}

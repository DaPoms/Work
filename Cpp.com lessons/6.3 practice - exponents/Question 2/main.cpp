#include <iostream>

constexpr bool isEven(int x)
{
    return (x % 2) == 0;
}

int main()
{
    std::cout << "Give an integer: ";

    int x{};
    std::cin >> x ;

    

    if (isEven(x))
        std::cout << x << " is odd.";



    else
        std::cout << x << " is even.";
}

#include <iostream>

double circumference(double radius); // forward declaration

constexpr double pi() { return 3.14159; } //constexpr is natively inline, meaning it can be in multiple files

int main()
{
    std::cout << pi() << '\n';
    std::cout << circumference(2.0) << '\n';

    return 0;
}

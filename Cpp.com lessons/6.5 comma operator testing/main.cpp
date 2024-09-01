#include <iostream>
int main() //comma operator is not very useful...
{
    int x{0};
    int y{2};
    std::cout << (++x, y--); //prints right element, but still changes the left one
    std::cout << '\n' << x;
}

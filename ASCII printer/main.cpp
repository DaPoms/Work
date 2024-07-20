#include <iostream>

int ASCIIprint(int x) // A different way to implicitly cast (not that good to do)
{
    return x;
}

int main()
{
    system("CLS");

    std::cout << "Enter a single character: ";

    char x{};
    std::cin >> x;

    int cast = x; //One way to implicitly cast

    std::cout << "You entered '" << x << "', which has an ASCII code of: " << cast; 
}

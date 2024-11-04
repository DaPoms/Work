#include <iostream>

int main()
{
    int* myPtr{NULL};
    std::cout << myPtr;

    int num{5};

    myPtr = &num;
    std::cout << "\nValue of var: " << *myPtr;
    std::cout << "\nMemory location of var: " << myPtr;
}

#include <iostream>

int main()
{
    int* ptr = new int[10]{1,2,3,4,5};

    *ptr = 20;
    std::cout << *(ptr);
}

#include <iostream>
#include <ctime>
#include <string>
#include <algorithm>
int main()
{
    std::string test {"123456"};

    for (int i{0}; i < 50; i++)
    {
    std::cout << std::clock() << '\n';
    //std:random_shuffle(test.begin(), test.end());
    //std::cout << test;
    }
}

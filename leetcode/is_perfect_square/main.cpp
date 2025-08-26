#include <iostream>
bool isPerfectSquare(int num) 
{
    double val{1};
    while(val * val < num)
        val++;
    if(val * val == num)
        return true;
    return false;
}

int main()
{
    std::cout << isPerfectSquare(16) << '\n';
    std::cout << isPerfectSquare(17);
}

#include <iostream>
int fib(int n) 
{
    if(n == 0) return 0;
    if (n == 1) return 1;
    return fib(n - 1) + fib(n - 2);
}
int main()
{
    std::cout << fib(3); //Answer should be 2 (0 + 1 = 1, 1 + 1 = 2)
}

#include <iostream>

int exponent(int r, int n)
{
    if(n == 0)
        return 1;
    return r * exponent(r, n-1);
}

int fib(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return (fib(n-1) + fib(n-2));
}
int main()
{
    std::cout << exponent(2,3) << '\n' <<
                 fib(6);
}

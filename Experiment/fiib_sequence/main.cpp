#include <iostream>
// just a quick reminder of the fibonacci sequence implimentation so I can think through the assembly implimentation

int fib(int count)
{
    if (count == 0) return 0;
    if (count == 1) return 1;
    return fib(count - 1) + fib(count - 2);

}

int main()
{
    int ans = fib(8);
    std::cout << ans;
}

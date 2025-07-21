#include <iostream>

int bringTo10(int val)
{
    if(val == 10)
        return val;
    if(val > 10)
        return bringTo10(--val);
    else
        return bringTo10(++val);
}

int main()
{
    std::cout << bringTo10(15);
}

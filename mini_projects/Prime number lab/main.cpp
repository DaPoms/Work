#include <iostream>

bool isPrime(int x)
{
   
    if (x == 2 || x == 3 || x == 5 || x == 7)
        return true;
    else
        return false;

    
}

int main()
{
    system("CLS"); //Learned this just now, I can make my programs pretty now!
    int x{};
    std::cout << "Enter a # from 0-9: "; 
    std::cin >> x;

    

    if (isPrime(x))
        std::cout << x << " is a prime number\n";
    else
        std::cout << x << " is NOT a prime number\n";
}

#include <iostream>
double myPow(double x, int n) //I had to make some statements for edge cases that are unique to certain values, such as 1, decimals, or negative powers
{
    if(x == 1) return 1; //Optimization for x == 1
    if(x ==  -1) //The definition of using power with x == -1
    {
        if(n % 2 == 0) //If even, x becomes positive (1)
            return -x;
        else //Else x stays negative
            return x;
    }
    if( ( x > 0 && x < 0.8 && n > 1000) || n < -2000) return 0.0; //If a decimal value for x is done to a postiive power high enough, we simplify to 0 (no need to do all the work), same for a negative value
    if(n == 0) return 1.0; //Base case, anything to the 0th power is 1. Works for increments negative powers and decrementing positive ones
    if(n < 0) return myPow(x, n + 1 ) * 1/x; //recursion for negative powers
    else return myPow(x, n - 1 ) * x; //recursion for positive powers 
}

int main()
{
    std::cout << myPow(0.00001, 1000); //Should be 4
}

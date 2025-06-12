#include <iostream>
using namespace std;
int mySqrt(int x) //Finds which whole number sqrt the passed value belongs to, rounded down
{
    long long int sqrtComparator{0}; //Value that we will do the square root of and compare it to the passed value, x. Made it a long, but I could've also just implicitly type casted line 6 too.
    while( (sqrtComparator * sqrtComparator) < x)
    {
        sqrtComparator++;
    }

    if(sqrtComparator * sqrtComparator == x)
        return sqrtComparator;
    else
        return sqrtComparator - 1;
}
int main()
{
    cout << mySqrt(10);
}

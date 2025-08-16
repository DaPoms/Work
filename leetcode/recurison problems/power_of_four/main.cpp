#include <iostream>
#include <cmath>
using namespace std;

//recursive inefficient approach I already knew from the power of 2 leetcode problem
int helper(int n, int target)
{
    if(n >= target)
        return n;
    return helper(n * 4, target);
}
bool isPowerOfFour(int n)
{
    if(n <= 0) //edge case of negative and 0
        return false;

    int num = helper(4, n);
    if(num == n)
        return true;
    else    
        return false;
}

/* 
//Non recursive log approach (math approach, log base 4 means 4 to what power gives you n. log(n) / log(4) is how you impliment log base 4
bool isPowerOfFour(int n) 
{
    if(n <= 0) //log and powers cannot give negative numbers
        return false;
    double num = log(n) / log(4); //I learned this from looking it up (change of base formula), if logs have the same base and are divided, the number inside the bottom log will become the new base
    int numInt = num; //long long to fit the sample size of leetcode
    if( (num - numInt) == 0) //Case of having a decimal (because we are not doing any changes to our double num (perfect log will always have no decimal vals), the imprecision of the decimal for doubles is not an issue)
        return true;
    else
        return false;
}
 */
int main()
{
    cout << isPowerOfFour(64 );
}

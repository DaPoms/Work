#include <iostream>
using namespace std;
    void twoToPower(long long& val,  int n) //Had to convert to long long to fit leetcode's sample size, which went beyond the max value of type int
    {
        if(val >= n)
            return;
        val = val * 2;
        twoToPower(val, n);
    }

    bool isPowerOfTwo(int n) 
    {

        long long val{1};
        twoToPower(val, n);
        if(val > n)
            return false;
        return true;
                
    }

int main()
{
    cout << isPowerOfTwo(7);
}

#include <bitset>
#include <iostream>
using namespace std;
//This is just a bit comparison program, it returns the number of bits that are not equal
int hammingDistance(int x, int y) 
{
    bitset<32> xBits = x;
    bitset<32> yBits = y;
    int xI{0};
    int yI{0};
    int differenceCount{0};
    while(xI < xBits.size())
    {
        if(xBits[xI] != yBits[yI])
            differenceCount++;
        xI++;
        yI++;
    }
    return differenceCount;
}

int main()
{
    cout << hammingDistance(1,4);
}

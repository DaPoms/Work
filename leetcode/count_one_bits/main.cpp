#include <bitset>
#include <iostream>
using namespace std;
int hammingWeight(int n) 
{
    bitset<32> intToBitSet(n);
    int count{0};
    for(int i{0}; i < 32; i++)
    {
        if(intToBitSet[i] == 1)
            count++;
    }
    return count;
}

int main()
{
    cout << hammingWeight(11); //should output 3;
}

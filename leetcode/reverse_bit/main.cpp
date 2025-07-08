#include <iostream>
#include <bitset>
#include <cstdint>

using namespace std;
uint32_t reverseBits(uint32_t n) 
{
    bitset<32> intToBitSet(n);
    bitset<32> ans;
    int addingIndex{0};
    for(int i{intToBitSet.size() - 1}; i >= 0; i--)
    {
        if(intToBitSet[i] == 0)
            ans[addingIndex] = 0;
        else
            ans[addingIndex] = 1;
        addingIndex++;    
    }
    
    return static_cast<uint32_t>(ans.to_ulong());
}

int main()
{
    cout << dec << reverseBits(uint32_t(4294967293)); //ans should be 3221225471  
}

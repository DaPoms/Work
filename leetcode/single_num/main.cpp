#include <iostream>
#include <vector>
#include <map>
using namespace std;

//My approach
/*     int singleNumber(vector<int>& nums) //Given a passed vector of ints, where only 1 value has 1 instance of itself, returns the value that only has once instance.
    {
        map<int,int> ans;
        for(int num : nums)
            ans[num]++; 
        for(auto pair : ans)
        {
            if(pair.second == 1)
                return pair.first;
        }
        return -1;
    } */


//Approach I found online (did not make)
int singleNumber(vector<int>& nums) 
{
    int ans = 0;
    for(int val : nums)
        ans = ans ^ val; //XOR operator, from what I understand, 1. if val shows up more than once, it makes the ans = 0 as since all the bits are the same, it makes the bitstring 000...
                         //2. In the case of the answer being a different value, it will change the value temporarily based on the unique bits between the numbers: 
                         // I.E: 4 = 100
                         //      3 = 011 -> result --> 111 -> 7
                         // But because each number shows up twice except the 1 single value, the bits will always cancel out the value it changed, using the previous I.E, lets say another 3 showed up:
                         // I.E: 7 = 111
                         //      3 = 011 --> result --> 100 -> 4 (See! The 3 canceled out because XOR of the same values always cancels out)
    return ans;
}
int main()
{
    vector<int> test = {2,2,14};
    
    cout << singleNumber(test);
    cout << "\n" << (4 ^ 3);
}

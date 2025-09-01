#include <iostream>
#include <vector>
using namespace std;
int digitCount(int num)
{
    int digits{0};
    while(num > 9)
    {
        num/=10;
        digits++;
    }
    return digits;
}
int findNumbers(vector<int>& nums) 
{
    int count{0};
    for(int num : nums)
    {
        if(digitCount(num) % 2)
            count++;
    }
    return count;
}

int main()
{
    vector<int> nums = {12,345,2,6,7896};
    cout << findNumbers(nums);
}

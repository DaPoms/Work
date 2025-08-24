#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int arrayPairSum(vector<int>& nums) 
{
    sort(nums.begin(), nums.end());
    int sum{0};
    
    int rightI{static_cast<int>(nums.size()) - 1};
    int leftI{rightI - 1};
    while(leftI >= 0)
    {
        sum += nums[leftI];
        leftI-=2; //this only works as we assume we have an even nums.size(). Due to pairings requiring 2 vals, do we can traverse in pairs knowing we will not seg fault
        rightI-=2;
    }
    return sum;
}

int main()
{
    vector<int> nums = {6,2,6,5,1,2};
    cout << arrayPairSum(nums);
}

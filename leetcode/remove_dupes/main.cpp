#include <vector>
#include <iostream>
using namespace std;

int removeDuplicates(vector<int>& nums) 
{
    for(int i{static_cast<int>(nums.size()) - 1}; i > 0; i--)
    {
        if(nums[i] == nums[i - 1])
            nums.erase( (nums.begin() + i), nums.erase(nums.begin() + i, nums.begin() + (i + 1) ) );
    }
    return nums.size();
}

int main() //Note: vector is assumed to be sorted
{
    vector<int> nums = {1,1,2,2,3,3,3,3,3};
    removeDuplicates(nums);

    for(int num : nums)
        cout << num << " ";

}

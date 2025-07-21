#include <vector>
#include <iostream>
using namespace std;
int helper(vector<int>& nums, int low, int high, int target)
{
    if(low > high)
        return -1;
    else
    {
        int mid = { (low + high) / 2};
        if(target == nums[mid])
            return mid;
        else if(target > nums[mid])
            return helper(nums, mid + 1, high, target); // Finally a discovery! A good way to return your answer in recursion is by doing returns with the recursive call itself,
                                                        // as it will traverse recursion till it reaches the base case, and return that base case val;
        else
            return helper(nums, low, mid - 1, target);
        
    }
}
int search(vector<int>& nums, int target) 
{
    
    return helper(nums, 0, nums.size() - 1, target);         
}
int main()
{
    vector<int> test = {-1,0,3,5,9,12};
    cout << search(test, 9);
}

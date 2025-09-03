#include <iostream>
#include <vector>
using namespace std;
bool isIncreasing(vector<int>& nums, int size)
{
    for(int i{0}; i < size - 1; i++)
        if(nums[i] > nums[i + 1])
            return false;
        return true;
}
bool isDecreasing(vector<int>& nums, int size)
{
    for(int i{0}; i < size - 1; i++)
        if(nums[i] < nums[i + 1])
            return false;
        return true;
}

bool isMonotonic(vector<int>& nums) 
{
    int size = nums.size();
    if(nums.size() < 2) return true;

    else if(nums[0] < nums[1]) //Case that we can check for monotonic increasing
        return isIncreasing(nums, size);
    else if(nums[0] > nums[1]) //Case that we can check for monotonic decreasing
        for(int i{0}; i < size - 1; i++)
            return isDecreasing(nums, size);;
    return isIncreasing(nums, size) || isDecreasing(nums, size); //case of == requires testing both for decrease and increase    
}

int main()
{
    // vector<int> test = {6,6,5,4,3,2,2,1};
    //vector<int> test = {6,5,4,3,10};
    vector<int> test = {3,4,5,6,6,10};
    cout << isMonotonic(test);
}

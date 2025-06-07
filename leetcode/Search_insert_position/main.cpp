#include <vector>
#include <iostream>
using namespace std; 

int searchInsert(vector<int>& nums, int target) 
    {
        int greaterIndex{-1};
        bool firstTime{true}; //Did this to make sure we get the index of the value greater than target, but also the closest to target out of the pool of "greater" values. 
        //This value will be where the target should be added, as insertion pushes this "greater" value forward
        for(int i{0}; i < nums.size(); i++)
        {
            if(nums[i] == target) //If we find the target, we return it
                return i;
            else if (firstTime && nums[i] > target) //Parameter for finding the first value greater than the target
            {
                greaterIndex = i;
                firstTime = false;
            }
        }

        if(greaterIndex == -1) //Case of needing to be added to the end
            return nums.size();
        else //Case of being found of needing to be added inbetween a value
            return greaterIndex;
    }

    int main()
    {
        // vector<int> test = {1,2,3,4};
        vector<int> test = {1,3, 5, 6};
        cout << searchInsert(test, 5); //Returns index where target is or where it should be inserted if it is not found
    }

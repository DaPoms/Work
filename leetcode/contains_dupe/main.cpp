#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;
/* bool containsDuplicate(vector<int>& nums) 
{
    unordered_map<int,int> occurences;
    for(int num : nums) 
    {
        occurences[num]++;
        if(occurences[num] > 1)
            return true;
    }
    return false;
}  */

//Alternate approach, not my first strategy (more efficient in memory and speed)
bool containsDuplicate(vector<int>& nums) 
{
    sort(nums.begin(),nums.end()); //By sorting, dupes will be consequtive to each other
    for(int i{0}; i < nums.size() - 1; i++) 
        if(nums[i] == nums[i + 1])
            return true;
    return false;
}

int main()
{
    vector<int> test = {1,2,3,1};
    cout << containsDuplicate(test);
}

#include <iostream>
#include <vector>
using namespace std;

//DIY approach (doesen't remove elements, just ignores them by moving all the other elements to the start of the vector and k defines the "new" size of the vector)
int removeElement(vector<int>& nums, int val) 
{
    int k{0}; //K is the count of elements that are != val
    for(int i{0}; i < nums.size(); i++)
    {
        if(nums[i] != val)
        {
            nums[k] = nums[i];
            k++;
        }
    
    }        
    return k;
}


//library approach (using vector functions)
/* int removeElement(vector<int>& nums, int val) 
{
    int k{0}; //K is the count of elements that are != val
    for(int i{0}; i < nums.size(); i++)
    {
        if(nums[i] == val)
        {
            nums.erase(nums.begin() + i, (nums.begin() + (i + 1) ) );
            i--;
        }
        else    
            k++;
    }        
    return k;
} */

int main()
{
    vector<int> test = {3,2,2,3};
    removeElement(test, 3);

    for(int num : test)
        cout << num << " ";
}

#include<vector>
#include<iostream>
#include <map>
using namespace std;
// This isn't the most efficient solution but I like using maps. Theres a way more efficient a mathematical way to 
// solve this as the sum of the pattern 1 + 2 + 3 + ... + n is (n*(n+1)) / 2, and whatever  the difference 
// is between the sum of the sequence with all values in the range vs the actual sum of our vector nums will give us the missing number
int missingNumber(vector<int>& nums) 
{
    int max = nums[0]; //very minorly inefficient
    map<int, int> numbers;
    for(int num : nums)
    {
        numbers[num]++;
        if(num > max)
            max = num;
    }
    
    int end{-1};
    for(int i{0}; i <= max; i++)
    {
        if(numbers[i] == 0)
            return i;
        end = i;
    }
    return end + 1;   
}

int main()
{
    vector<int> test = {3,0,1};
    cout << missingNumber(test);
}

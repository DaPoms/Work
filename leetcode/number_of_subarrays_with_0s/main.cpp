#include <vector>
#include <map>
#include <iostream>
using namespace std;

//This is an altered version of the below approach. Without recursion, this approach was way faster! 
//In no situation did we have to store ALL the previous values for zero streaks like I did in the first approach, 
//as you only need the one before the streak you are trying to calculate the sub arrays for. Due to this change, my approach now works efficiently for even large arrays (100,000 0 streaks and more!)
long long zeroFilledSubarray(vector<int>& nums) {
    int zeroStreak{0};
    map<int, int> count;
    for(int num : nums)
    {
        if(num == 0)
            zeroStreak++;
        else
        {
            if(zeroStreak > 0)
                count[zeroStreak]++;
            zeroStreak = 0;
        }
    }
    if(zeroStreak > 0) //makes sure to add the last streak in the case that 0's are at the end of the array
        count[zeroStreak]++;
    
    long long subarraysTotal{0}; 
    long long counter{1};
    long long val{0};

    auto it = count.begin();
    
    while(it != count.end())
    {
        val += counter;
        if( it -> first == counter) //it -> first is the key for the map
        {
            subarraysTotal += val * it->second; // it -> second is the occurences of that streak size
            it++;
        }
        counter++; 
    }
    //Here is where I noticed a pattern that each streak of zeros is the previous one but plus a counter that increases by 1 for each 0. EX:
    // A 1 zero streak has 1 subarray, 2 has 1 + 2 = 3, with 2 being the starting streak value. A 3 zero streak is just 3 + 3 = 6, as you can see the pattern continues
    
    return subarraysTotal;
}

/* 
//This first approach isn't the best, it works on all small sample sizes, but once you get to 0 streaks of size 100,000, it seg faults, and the recursion is why this is rather inefficient
void calculateSubarrays(long long num, long long counter, long ending, vector<long>& ans)
{
    if(counter > ending ) //base case! we only need to calculate up to the highest zero streak we found in our array, so we stop once we go 1 above our greatest streak
        return;
    ans.push_back(num + counter);
    calculateSubarrays(num + counter, counter + 1, ending, ans);
}
long long zeroFilledSubarray(vector<int>& nums) {
    //sliding window it the first idea that came to my mind!
    int maxStreak{-1};
    int zeroStreak{0};
    int zeroSubarrayCount{0};
    map<int, int> count;
    for(int num : nums)
    {
        if(num == 0)
            zeroStreak++;
        else
        {
            if(zeroStreak > 0)
                count[zeroStreak]++;
            if(zeroStreak > maxStreak)
                maxStreak = zeroStreak;
            zeroStreak = 0;
        }
    }
    if(zeroStreak > 0) //makes sure to add the last streak in the case that 0's are at the end of the array
    {
        if(zeroStreak > maxStreak)
                maxStreak = zeroStreak;
        count[zeroStreak]++;
    }
    
    //This is the longest variable name I've ever made, but its named as exactly what it is meant for
    vector<long> countOfSubArraysInZeroStreak = {1}; //stores the amount of subarrays that can be made from a given streak of zeros, index 0 is for 1 zero, 1 is for 2 zeroes, and so on.
    countOfSubArraysInZeroStreak.reserve(maxStreak + 1000);
    //Here is where I noticed a pattern that each streak of zeros is the previous one but plus a counter that increases by 1 for each 0. EX:
    // A 1 zero streak has 1 subarray, 2 has 1 + 2 = 3, with 2 being the starting streak value. A 3 zero streak is just 3 + 3 = 6, as you can see the pattern continues
    calculateSubarrays(1, 2, maxStreak, countOfSubArraysInZeroStreak);
    
    for(auto& [numZeros, occurences] : count) 
        zeroSubarrayCount += (countOfSubArraysInZeroStreak[numZeros - 1] * occurences);
    return zeroSubarrayCount; 
}
 */
int main()
{
    vector<int> nums = {0,0,0};
    cout << zeroFilledSubarray(nums);
}

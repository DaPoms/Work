#include <iostream>
#include <vector>
#include <map>
using namespace std;

//Assisted attempt (I got a hint)
class FindSumPairs 
{
private:
    vector<int> first;
    vector<int> second;
    map<int,int> n2Freq; //nums2 frequency map, tells us what val we need to get count for the count function

public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) : first{nums1}, second{nums2}
    {
        for(int x : second)
            n2Freq[x]++;
    }
    
    void add(int index, int val) //Adding is only done on the second vector according to the leetcode prompt
    {
        n2Freq[second[index]]--; //We remove the old mapping
        second[index] += val; //We add the new value
        n2Freq[second[index]]++; //We add the new value to the mapping
    }

    int count(int tot) //In this method all the work is already done ahead of time, so this is all we have to call this. making it more efficient
    {
        int count{0};
        for(int x : first)
        {
            count += n2Freq[tot - x]; //Adds the frequency of the amount of pairs which work with the first vector's value in adding to the total param
        }
        return count;
    }

};

/* My attempt of the problem (ended up too slow on the 24th testcase)
class FindSumPairs 
{
private:
    vector<int> first;
    vector<int> second;
    map<int,int> occurence;

public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) : first{nums1}, second{nums2}
    {
        for(int leftI{0}; leftI < first.size(); leftI++) //This was the issue for my take: You can avoid O(n^2) by storing the frequency of one of the lists, not all the sums between the two
        {
            for(int rightI{0}; rightI < second.size(); rightI++)
            {
                occurence[first[leftI] + second[rightI]]++;
            }
        }
    }
    
    void add(int index, int val) 
    {
        for(int leftI{0}; leftI < first.size(); leftI++) //Clears the map values affected by the old val
        {
            occurence[first[leftI] + second[index]]--;
        }
        second[index] += val;

        for(int leftI{0}; leftI < first.size(); leftI++) //Changes map to new value
        {
            occurence[first[leftI] + second[index]]++;
        }
    }

    int count(int tot) //In this method all the work is already done ahead of time, so this is all we have to call this. making it more efficient
    {
        return occurence[tot];
    }
     //Inefficient attempt
    int count(int tot) 
    {
        int count{0};
        for(int leftI{0}; leftI < first.size(); leftI++)
        {
            for(int rightI{0}; rightI < second.size(); rightI++)
            {
                if(first[leftI] + second[rightI] == tot)
                    count++;
            }
        }
        return count;
    }
    
};
*/
int main()
{
    vector<int> test1 = {1, 1, 2, 2, 2, 3};
    vector<int> test2 = {1, 4, 5, 2, 5, 4};
    FindSumPairs* obj = new FindSumPairs(test1, test2);
    cout << obj->count(7);
}

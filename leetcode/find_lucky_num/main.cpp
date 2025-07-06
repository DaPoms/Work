#include <vector>
#include <map>
#include <iostream>
using namespace std;
int findLucky(vector<int>& arr) 
    {
        map<int,int> occurence;
        for(int num : arr)
            occurence[num]++;

        int max{-1};
        for(auto& [key, count] : occurence) 
        {
            if(key == count) //Since the vector is sorted, we do not need a true max method (like adding to the if: "key == count && key > max")
                max = key;
        }
        return max;
    }

    int main() 
    {
        vector<int> test = {1,2,2,3,3,3}; //should return 3
        cout << findLucky(test);
    }

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
//This approach is closer to an actual hashSet, index is the number instead
class MyHashSet {
private:
    vector<bool> nums;
public:
    MyHashSet() {nums.resize(1000001);} //leetcode specified the key values go up to 10^6
    
    void add(int key) 
    {
        nums[key] = true; 
    }
    
    void remove(int key) 
    {
        nums[key] = false;
    }
    
    bool contains(int key) 
    {
        return nums[key];
    }
};
/* 
//This approach puts no limit on the size other than the limitations of the vector class, very inefficient speed wise though
class MyHashSet {
private:
    vector<int> nums;
public:
    MyHashSet() {}
    
    void add(int key) 
    {
        for(int num : nums) // acts like .contains()
        {
            if(num == key)
                return;
        }
            nums.push_back(key);
    }
    
    void remove(int key) 
    {
        vector<int>::iterator index = find(nums.begin(), nums.end(), key); //
        if(index != nums.end())
            nums.erase(index);        
    }
    
    bool contains(int key) 
    {
        return find(nums.begin(), nums.end(), key) != nums.end();
    }
};
 */
int main()
{
    MyHashSet test;
    test.add(1);
    test.add(2);
    test.add(3);
    cout << test.contains(0) << '\n';
    cout << test.contains(1) << '\n';
    cout << test.contains(2) << '\n';

}

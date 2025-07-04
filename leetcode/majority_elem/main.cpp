    #include <map>
    #include <vector>
    #include <iostream>
    using namespace std;
    int majorityElement(vector<int>& nums) 
    {
        map<int, int> occurence;
        for(int num : nums)
            occurence[num]++;
        for(auto& [key,count] : occurence) //I learned of this new [key, value] synax for "for each in.. for loops", this way you don't have to do .first and .second, and you can name them!
        {
            if(count > nums.size() / 2)
                return key;
        }
        return -1;
    }

    int main()
    {
        vector<int> test = {3,2,3}; //Answer should be 3
        cout << majorityElement(test);
    }

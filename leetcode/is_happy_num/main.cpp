#include <vector>
#include <iostream>
using namespace std;
    bool contains(vector<int> v, int val)
    {
        for(int i : v)
        {
            if(i == val)
                return true;
        }
        return false;
    }
    bool isHappy(int n) 
    {
        vector<int> seen = {n};
        int val{0};
        while(seen[seen.size() - 1] != 1)
        {
            while(n > 0)
            {
                val += (n % 10) * (n % 10); //Adding the square of all the digits to val
                n /= 10; //Removes digit we added
            }
            if(contains(seen, val)) //If val is already seen, we are in a cycle, and it is not a happy num
                return false;
            n = val;
            seen.push_back(val);
            val = 0;
        }
        return true;
    }

    int main()
    {
        cout << isHappy(19); //True!
        cout << '\n' <<  isHappy(2); //False!
    }

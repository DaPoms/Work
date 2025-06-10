#include <string>
#include <iostream>
using namespace std;
string addBinary(string& a, string b) //I admit this is easily one of the more sloppy leetcode solutions I've made
{
    int endIndexL{static_cast<int>( a.size() ) - 1}; //For adding, we only need to care about comparisons for the 
    int endIndexR{static_cast<int>( b.size() ) - 1}; //Right side end index
    int digitsToCompare{-1}; //The number of digits we need to compare, the rest are just returned from the bitstring with the longer size
    string ans{""};
    
    if(a.size() > b.size())
    {
        digitsToCompare = b.size();
        ans = a;
    }
    else
    {
        digitsToCompare = a.size();
        ans = b;
    }

    
   
    int count{0};

    if(ans == a)
    {
        while(count != digitsToCompare) //Adding digits that need to be added
        {
            if(b[endIndexR] == '1')
                ans[endIndexL]++;
            
            endIndexL--;
            endIndexR--;
            count++;
        }
    }
    else
    {
        while(count != digitsToCompare) //Adding digits that need to be added
        {
            if(a[endIndexL] == '1')
                ans[endIndexR]++;
            
            endIndexL--;
            endIndexR--;
            count++;
        }
    }

    count = ans.size() - 1;
    while(count >= 0)
    {
        if(ans[count] == '2' || ans[count] == '3') //Case of new digit
        {
            if(count != 0)
            {
                if(ans[count] == '2')
                {
                    ans[count] = '0';
                    ans[count - 1]++;
                }
                else //Case of having a val of 3
                {
                    ans[count] = '1';
                    ans[count - 1]++;
                }
            }

            else
            {
                if(ans[0] == '3')
                    ans[0] = '1';
                else
                    ans[0] = '0';
                ans.insert(ans.begin(), '1'); 
            }

        }
        count --;
    }

    return ans;
}

int main()
{
    string test{"1111"};
    string test2{"1111"};
    addBinary(test,test2);

    cout << test[0] << '\n';
    for(char bit : test)
        cout << bit << " ";
    
}

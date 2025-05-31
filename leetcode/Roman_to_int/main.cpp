#include <iostream>
#include <string>
#include <map>
using namespace std;
int romanToInt(string s) {
        int val{0};
        map<char, int> romanIntVals = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
        };

        for(int i{0}; i < s.size() - 1; i++)
        {
            if( (s[i] == 'I' && (s[i + 1] == 'V' || s[i + 1] == 'X' ) ) || (s[i] == 'X' && (s[i + 1] == 'L' || s[i + 1] == 'C' ) ) || (s[i] == 'C' && (s[i + 1] == 'D' || s[i + 1] == 'M') ) )
            {
                val -= romanIntVals[s[i]];
            }

            else
                val += romanIntVals[s[i]];
            
        }
        if(s.size() != 0)
            val += romanIntVals[s[s.size() - 1]];
            
        return val;
    }

int main()
{
    cout << romanToInt("");
}

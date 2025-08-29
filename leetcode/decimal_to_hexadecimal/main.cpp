#include <string>
#include <iostream>
using namespace std;   
void insertHex(string& hex, int val)
{
    string toAdd{""};
    if(val < 10)
        toAdd = to_string(val);
        // toAdd = char(val);
    else
    {
        switch(val)
        {
            case 10: toAdd = "a"; break;
            case 11: toAdd = "b"; break;
            case 12: toAdd = "c"; break;
            case 13: toAdd = "d"; break;
            case 14: toAdd = "e"; break;
            case 15: toAdd = "f"; break;
        }
    }

    hex = toAdd + hex;
}
string toHex(unsigned int num) //unsigned to avoid issues with negative numbers
{
    int digit;
    string ans;
    if(num == 0) return "0";
    while(num > 0)
    {
        
        digit = num % 16;
        num /= 16;
        insertHex(ans, digit);

    }
    return ans;   
}

int main()
{
    string ans = toHex(26);
    cout << ans;
}

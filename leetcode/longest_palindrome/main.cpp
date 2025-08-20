#include <map>
#include <iostream>
using namespace std;
int longestPalindrome(string s) 
{
    int ans{0};
    int hasOddCenter{false};
    int end{0};
    map<char, int> letters;
    for(char letter : s)
        letters[letter]++;
    for(auto& [key, value] : letters)
    {
        if(value % 2 != 0)
        {
            hasOddCenter = true;
            end = 1; //required to prevent 1 from running on the for loop, allows us to use 1 for loop for both cases of even and odd counts of letters
        }
        else
            end = 0;
        for(int i{value}; i > end; i -= 2)
            ans += 2;
    }   
    if(hasOddCenter)
        ans++;
    return ans;  
}

int main()
{
    cout << longestPalindrome("bbbaac");
}

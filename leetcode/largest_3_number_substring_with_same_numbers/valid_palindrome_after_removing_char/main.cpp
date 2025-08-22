#include <iostream>
#include <map>
#include <string>
using namespace std;
//This is once again a showcase of how you can make something extremely convoluted no matter how simple a problem is. I vow to come back to this problem more concisely later
//The bonus though is that it works! albeit very inefficiently
    bool validPalindrome(string s) 
    {
        map<int, int> letters;
        for(char letter : s)
            letters[letter]++;
        int removals{0};
        string partialPalin{""};
        for(int i{static_cast<int>(s.size()) - 1}; i >= 0; i--)
        {
            partialPalin += s[i];
        }
        for(int i{0}; i < s.size(); i++)
        {
            if(removals > 1)
                return false;
            if(partialPalin[i] != s[i])
            {
                if( (letters[partialPalin[i]] < letters[partialPalin[s.size() - 1 - i]] || (letters[partialPalin[s.size() - 1 - i]] % 2 == 0) ) && (letters[partialPalin[i]] % 2 != 0 && partialPalin[i] == s[s.size() - 1 - i]))
                {
                    s.erase(s.size() - 1 - i, 1);
                    partialPalin.erase(i, 1);
                    i--;
                }
                else
                {
                    partialPalin.erase(partialPalin.size() - 1 - i, 1);
                    s.erase(i, 1);
                    i--;
                }
                removals++;
            }
        }
        return true;
    }


/*     
bool validPalindrome(string s) 
{
    map<char,int> letters;
    int oddCount{0};
    for(char letter : s)
        letters[letter]++;
    for(auto& [key,value] : letters)
    {
        if(value % 2 != 0)
        {
            oddCount++;
        }
    }
    int mid = s.size() / 2;
    if(oddCount <= 1 || (oddCount == 2 && letters[s[mid]] % 2 != 0) )
        return true;
    return false;
     
}
 */
int main(){
    cout << validPalindrome("aaaz");
}

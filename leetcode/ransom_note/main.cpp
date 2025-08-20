#include <iostream>
#include <map>
#include <string>
using namespace std;

//array approach I found on leetcode (not made by me)
/* 
    bool canConstruct(string ransomNote, string magazine) 
    {
        int arr[26]; //there are 26 letters
       
        for(char letter : magazine)
            arr[letter - 'a']++; // subtracting by 'a' brings the char 'a' at the index 0 of the arr and 'z' at index 25.
        for(char letter : ransomNote)
        {
            if(arr[letter - 'a'] == 0)
                return false;
            arr[letter - 'a']--;
        }  
        return true;
    }
 */
//map approach (my attempt), almost exactly like the above one but with a map instead of an array
bool canConstruct(string ransomNote, string magazine) 
{
    map<char, int> lettersPool;
    
    for(char letter : magazine)
        lettersPool[letter]++;
    for(char letter : ransomNote)
    {
        if(lettersPool[letter] == 0)
            return false;
        lettersPool[letter]--;
    }  
    return true;
    
}

#include <string>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;
int findWord(string arr[], int size, string n)
{
    for(int i{0}; i < size; i++)
        if(arr[i] == n)
            return i;
    return -1;
}

bool wordPattern(string pattern, string s) 
{

    if(s.size() == 1)
        return true;
    
    string arr[26] = {""};

    int startI{0};
    bool hasStart{false};
    int length{1};
    int trPattern{0};
    int wordCount{0};
    int indexFound{-1};
    for(int i{0}; i < s.size(); i++)
    {
        if(s[i] == ' ' || i == s.size() - 1)
        {
            wordCount++;
            if(i == s.size() - 1 )
            {
                if(length == 1 && s[i - 1] == ' ')
                    startI = s.size() - 1;

                length++;
            }
            
            indexFound = findWord(arr, 26, s.substr(startI, length) );
            if( trPattern < pattern.size() &&  (indexFound == -1 || indexFound == pattern[trPattern] - 'a') && (arr[ (pattern[trPattern] - 'a') ] == "" ||  arr[ pattern[trPattern] - 'a']  ==  s.substr(startI, length) ) ) //if we have to map different vals
                arr[ (pattern[trPattern] - 'a') ] = s.substr(startI, length);
            else
                return false;
            trPattern++;
            //words[s.substr(startI, length)]++;
            hasStart = false;
            length = 1;
        }
        else if(!hasStart)
        {
            startI = i;
            hasStart = true;
        }
        else
            length++;
    }


    if(pattern.size() == s.size())
    {
        for(int i{0}; i < s.size(); i++)
            if(pattern[i] == s[i])
                return false;
    }
    else if(wordCount < pattern.size()) return false;

    return true;
}


int main()
{
    cout << wordPattern("he", "unit");
}

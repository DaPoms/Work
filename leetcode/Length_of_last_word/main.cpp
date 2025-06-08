#include <string>
#include <iostream>
using namespace std;

//Approach 1 (I like doing the first approach that comes to mind and then seeing the more proper approach later)
//This approach was inefficient because this activity is based off of finding the length of the LAST word, so there is no reason to traverse from the start, we should start at the end! Its much easier that way
/* int lengthOfLastWord(string s) 
{
    int lastSpace{-1};
    int fillerSpaceCount{0};
    for(int i{0}; i < s.size() - 1; i++)
    {
        if(s[i] == ' '  )
        {
            if(s[i + 1] != ' ')
            {
                lastSpace = i;
                fillerSpaceCount = 0;
            }
            else
                fillerSpaceCount++;
        }
        else
        {
            if(s[i + 1] == ' ')
                fillerSpaceCount++;
        }
    }

    if(lastSpace != -1 || s[s.size() - 1] == ' ')
    {
        int ans = s.substr(lastSpace + 1).size();
        if(s[s.size() - 1] == ' ')
            ans -= fillerSpaceCount;
        return ans;
    }
    else //Case of no spaces
    {
        return s.size();
    }
    
    return -1; //Error case
} */
    

//Approach 2

int lengthOfLastWord(string s) 
{
    int count{0};
    int traverseIndex{static_cast<int>(s.size()) - 1};
     bool passedSpaces{false};

     while(s[traverseIndex] == ' ' && traverseIndex >= 0) //Accounts for excess spaces at the end if there are any, by ignoring them
        traverseIndex--;

    while(s[traverseIndex] != ' ' && traverseIndex >= 0)
    {
        traverseIndex--;
        count++;
    }

    return count;


}

 
int main()
{
    cout << lengthOfLastWord("a");
}

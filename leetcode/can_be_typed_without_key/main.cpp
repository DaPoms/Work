#include <string>
#include <iostream>
#include <map>
using namespace std;
int canBeTypedWords(string text, string brokenLetters) 
{
    bool isBroken{false};
    int count{0};
    map<char, int> letters;
    for(int i{0}; i < text.size(); i++)
    {
        letters[text[i]]++;
        if(text[i] == ' ' || i == text.size() - 1)
        {
            for(char brokenChar : brokenLetters)
            {
                if(letters[brokenChar] != 0) //case that word cannot be typed as it uses a broken key
                {
                    isBroken = true;
                    break;
                }
                
            }
            if(!isBroken)
                count++;
            isBroken = false;
            letters.clear();
                    
        }
    }        
    
    return count;
}

int main()
{
    cout << canBeTypedWords("leet code", "lt"); //Returns the number of words that can be typed considering the keys which are broken (the right param)
}

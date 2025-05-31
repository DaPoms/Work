#include <string>
#include <iostream>
#include <vector>
using namespace std;
string longestCommonPrefix(vector<string>& strs) {
        string prefix{""};

        int smallest{static_cast<int>(strs[0].size())}; //This is a bandaid solution, but I wanted to use this for loop type for once
        for(string word : strs)// finds the smallest word
        {
            if(word.size() < smallest)
            {
                smallest = word.size();
            }
        }

        int letterIndex{0};
        char letter{'\0'};
        while(letterIndex < smallest) //I used the smallest variable because we know that the common prefix cannot be larger than the smallest word
        {
            letter = strs[0][letterIndex];
            for(string word : strs)
            {
                if(letter != word[letterIndex])
                    return prefix;
                letter = word[letterIndex];
                
            }
            prefix += letter;
            letterIndex++;
        }

        return prefix;
    }

int main()
{
    vector<string> words = {"flower","flow","flight"};
    cout << "Answer: "  << longestCommonPrefix(words);
}

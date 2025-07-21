#include <string>
#include <iostream>
using namespace std;
void helper(int k, string& word)
{
    if(word.size() >= k)
        return;
    string appendWord = "";
    for(char letter : word)
    {
        if(letter == 'z') //z's loop back to a
            appendWord += 'a';
        else 
            appendWord += (++letter); //Char shifts forward one letter
    }
    word += appendWord;
    helper(k, word);
}
char kthCharacter(int k) 
{
    string word{"a"};
    helper(k, word);
    cout << word << '\n';
    return(word[k-1]);
}

int main()
{
    cout << kthCharacter(5);
}

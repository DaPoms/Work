#include <iostream>
#include <cctype>
#include <string>
using namespace std;

bool isValid(string word) 
{
    bool hasVowel{false};
    bool hasConsonant{false};
    int charAsInt;
    if(word.size() >= 3)
    {
        for(char& character : word)
        {
            character = tolower(character); //To lower removes the need to account for upper case letters
            charAsInt = int(character);
            if( (charAsInt >= 48 && charAsInt <= 57) || (charAsInt >= 97 && charAsInt <= 122) )
            {
                if((charAsInt >= 97 && charAsInt <= 122)) //Case of letter not number
                {
                    if(character == 'a' || character == 'e' || character == 'i' || character == 'o' || character == 'u')
                        hasVowel = true;
                    else
                        hasConsonant = true;
                }
            } 
            else //Case of breaking rule by having a symbol in the word
                return false;
        }
    }
    if(hasConsonant && hasVowel) //Case of passing all tests for a valid word
        return true;
    else
        return false;

}

int main()
{
    
    string test1{"APPLE123@"}; //Should be false, has '@', which is a symbol
    string test2{"UuEe6"}; //Should be false, has no consonants
    string test3{"Aeioum321"}; //Should be true, has a vowel + consonant and no symbols
    
    std::cout << isValid(test1) << '\n' << isValid(test2) << '\n' << isValid(test3);
}

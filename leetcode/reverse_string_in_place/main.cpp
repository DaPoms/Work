#include <vector>
#include <iostream>
using namespace std;
void reverseString(vector<char>& s) 
{
    int leftI{0};
    int rightI{static_cast<int>(s.size()) - 1};
    char placeholder{'\0'};
    while(!(leftI >= rightI)) //Stops for two cases: 1. If the vector has an odd size, when the indexes are the same, it stops. 2. If the vector has an even size, the while will end when leftI is greater than rightI
    {
        placeholder = s[leftI]; //swaps left char with right char
        s[leftI] = s[rightI];
        s[rightI] = placeholder;
        leftI++;
        rightI--;
    }
}

int main()
{
    vector<char> test = {'a', 'p', 'p', 'l', 'e'};
    reverseString(test);
    for(char letter : test)
        cout << letter;
}

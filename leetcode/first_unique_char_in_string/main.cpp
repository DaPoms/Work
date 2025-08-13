#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;
//I am aware this is a rather inefficient approach, but I wanted to play around with queues even if it isn't the most efficient method (especially in terms of memory usage)
int firstUniqChar(string s) 
{
    int index{0};
    char previous{'\0'};
    unordered_map<char, int> occurence;
    queue<char> letters;
    for(char letter : s)
    {
        occurence[letter]++;
        letters.push(letter);
    }
    while(!letters.empty())
    {
        if(occurence[letters.front()] == 1)
            return index;
        else
            letters.pop();
        index++;
    }
    return -1;
}

int main()
{
    cout << firstUniqChar("blalb"); //should return "a" at index 2
}

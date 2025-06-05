#include <string>
#include <iostream>

using namespace std;
int strStr(string haystack, string needle)
{
    string substring{""};
    int startingI{0};
    while(startingI + (needle.size() - 1) < haystack.size())
    {
        substring = haystack.substr(startingI, needle.size() ); //New lesson to self: Substr has second param as length of substring, not the index of the end of the substring, unlike java (what I was used to)
        if(substring == needle)
            return startingI;
        startingI++;
    }
    return -1;
}

int main()
{
    cout << strStr("hello", "ll");
}

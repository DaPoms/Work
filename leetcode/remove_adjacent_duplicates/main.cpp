#include <iostream>
#include <string>
using namespace std;
//I didn't have much time for optimizing today so here is my approach.
string removeDuplicates(string s) 
{
    int i{0};
    int size = s.size();
    while(i < size) //requires checking size each while loop, rather unefficient
    {
        if(s[i] == s[i + 1])
        {
            s.erase(i, 2); //This is what makes my program rather inefficient, as erasing requires shifting ALL the elements 
                           //to the right of the target down 2. An approach that instead observes the elements of s rather than doing inplace manipulation might be more efficient
            if(i != 0)
                --i;
        }
        else
            i++;
    }
    return s;
}

int main()
{
    /* cout << removeDuplicates("abbaca"); */
    cout << removeDuplicates("aaaaaaaa");
}

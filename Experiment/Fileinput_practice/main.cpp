#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
    //Approach 1
    /* ifstream file{"test.txt"};
    string word;
    string p{""};
    
    while(getline(file, word))
    {
        stringstream s{word};
        while(s >> p)
        {
            cout << p;
        }
    }
 */

 ////Approach 2 (flat out doesn't work, str() only works for the first time)
    /* string p{""};
    stringstream s{};
    s.str("a b c d");

    while(s >> p)
    {
        cout << p;
    }

    s.str("e f g h"); //weird behavior of str, only works on first try

    while(s >> p)
    {
        cout << p;
    } */

    //approach 3 (the best one)

   /*  ifstream file{"test.txt"};
    string p;
    while(file >> p)
        cout << p << " ";
     */

     //testing behavior of operator>> on ifstreams, particularly what happens when you reach the end but still call operator>>
    ifstream file{"test.txt"};
    string word{""};

    for(int i{0}; i < 20; i++)
    {
        file >> word;
        cout << word << "\n";
    }

    if(!(file))
        cout << "I'm at the end of the file!";
    //Lesson learned: operator>> repeats the last value if you use it with an ifstream which is pointing out of bounds

}

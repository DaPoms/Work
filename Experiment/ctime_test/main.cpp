#include <iostream>
#include <ctime>
#include <string>

using namespace std;

string doThing()
{
    clock_t before = clock();
    string empty{""};
    for(int i{0}; i < 100000000; i++)
    {
        empty += "a";
    }
    
    cout << "In function: " << difftime(clock(), before) << '\n';
    return empty;
}


int main()
{
    
    
    clock_t before = clock();
    doThing();
    clock_t after = clock();
    cout << "In main: " << difftime(after,before) << '\n';
}

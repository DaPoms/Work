#include <iostream>
using namespace std;

void err()
{
    //exception test;
    //throw test;
    throw new exception;
}

int main()
{  
    try
    {
        err();
    }
    catch(const exception* e)
    {
        cout << "Uh oh!";
    }
}

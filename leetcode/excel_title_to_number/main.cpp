#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int titleToNumber(string columnTitle) 
{
    long val{0};
    int adding{0};
    for(int i{static_cast<int>(columnTitle.size() - 1)}; i >= 0; i--)
    {
        adding = (int(columnTitle[i]) - int('A') + 1) * pow(26, columnTitle.size() - i - 1 );
        val += adding;
    }
    return val;
}

int main()
{
    cout << titleToNumber("AB");
}

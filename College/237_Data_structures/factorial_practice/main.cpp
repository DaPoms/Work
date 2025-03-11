//4.1.1 fragment
#include <iostream>
using namespace std;
long factorial(int n)
{
    if (n < 0)
        cout << "n must be nonnegative";
    else if (n == 0)
        return 1;
    else 
        return n *= factorial(n-1);
}

int main()
{
    long input{-1};
    cout << "What do you want to do the factorial of?:";
    cin >> input;
    cout << factorial(input);
}

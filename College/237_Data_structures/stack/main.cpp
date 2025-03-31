#include <stack>
#include <iostream>
#include <string>
using namespace std;

//The goal of my teachers assignment for this task was to test the STL stack library's basic functions
template<typename T>
void dispStack(stack<T> passedStack) //Purposely not passing by reference so that the popping doesn't actually affect the real stack, 
                                    //though it is rather inefficient as it has to make a copy of the stack, but this is how my teacher wanted it to be done
{
    while(!passedStack.empty())
    {
        cout << passedStack.top() << " ";
        passedStack.pop();
    }   
    cout << "\n";
}

template<typename T = int>
void dispAction(string functName, stack<T> passedStack, T elem = -1) //Prints what we are doing to the stack based on the passed string. 
                                                                //NOTE: Does not run said function call, it must be called manually, and elem is only useful for push back
{
    if (functName == "PU")
        cout << "Pushing " << elem << " to the top of the stack.\n";
    else if (functName == "PO" )
        cout << "Popping " << passedStack.top() << " at the top of the stack.\n";
    else    
        cout << "ERROR - wrong string input to function call dispAction(), " << functName << " is not a valid string.\n";
}

int main()
{
    stack<int> myStack{};

    dispAction("PU", myStack, 5);
    myStack.push(5);
    dispStack(myStack);

    dispAction("PO", myStack);
    myStack.pop();
    dispStack(myStack);

    dispAction("PU", myStack, 10);
    myStack.push(10);
    dispStack(myStack);

    dispAction("PU", myStack, 63);
    myStack.push(63);
    dispStack(myStack);

    dispAction("PO", myStack);
    myStack.pop();
    dispStack(myStack);

    dispAction("PU", myStack, 15);
    myStack.push(15);
    dispStack(myStack);

    dispAction("PU", myStack, 20);
    myStack.push(20);
    dispStack(myStack);
}

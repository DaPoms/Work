#include <queue>
#include <stack>
#include <iostream>
using namespace std;


int main()
{
    stack<int> testStack;
    queue<int> testQueue;
    testStack.push(1); //items added are put to the top
    cout << testStack.top() << '\n';
    testStack.push(2);
    cout << testStack.top() << '\n';
    testStack.push(3);
    cout << testStack.top() << "\n\n";
    testStack.pop();
    cout << testStack.top() << "\n";
    testStack.pop();
    cout << testStack.top() << "\n\n";
    testStack.pop();
    
   
    testQueue.push(1); //items added are put to the bottom
    cout << testQueue.front() << '\n';
    testQueue.push(2);
    cout << testQueue.front() << '\n';
    testQueue.push(3);
    cout << testQueue.front() << "\n\n";
    testQueue.pop();
    cout << testQueue.front() << "\n";
    testQueue.pop();
    cout << testQueue.front() << "\n";
    testQueue.pop();

}

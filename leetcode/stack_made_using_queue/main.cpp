#include <queue>
#include <iostream>
using namespace std;
class MyStack {
    queue<int> q;

public:
    MyStack() {}

    void push(int x) 
    {
        q.push(x);
        int flipCount = q.size(); //the amount of numbers we have to flip from the top to the back of the queue to make the queue behave like a stack, as the back of a queue is the most recently added values, but a stack should instead have these at the top
        while(--flipCount) 
        {
            q.push(q.front());
            q.pop();
        }
   
    }

    int pop() {
        int val = q.front();
        q.pop();
        return val;
    }

    int top() {
        return q.front();
    }

    bool empty() {
        return q.empty();
    }
};

int main()
{
    MyStack test;
    test.push(1);
    test.push(2);
    test.push(3);

}

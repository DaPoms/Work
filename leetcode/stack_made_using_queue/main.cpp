#include <queue>
#include <iostream>
using namespace std;
class MyStack {
    queue<int> q;

public:
    MyStack() {}

    void push(int x) {
        q.push(x);
        int size = q.size();
        while (--size) {
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

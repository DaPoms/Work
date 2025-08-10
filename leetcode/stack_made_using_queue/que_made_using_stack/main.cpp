#include <stack>
#include <iostream>
using namespace std;
class MyQueue {
    private:
        stack<int> s1;
        stack<int> s2;
    public:
        MyQueue() {
            
        }
        
        void push(int x) 
        {
            s1.push(x);
        }
        
        int pop() 
        {
            int val = peek(); //only runs to check if theres a recent push
            s2.pop();
            return val;
        }
        
        int peek() {
            if(s2.empty()) //We really only need to remake the queue when all the elements of the queue from the last set of push's have been popped, 
            //as any push calls put the elements in the back, but pop() pops the oldest elements, so the newest have no impact till the oldest elements are gone
            {
                while(!s1.empty()) //puts vals from s1 in backwards, now we have the first/oldest elements added to the stack, just like a queue!
                {
                    s2.push(s1.top());
                    s1.pop();
                }
            }
            return s2.top();
        }
        
        bool empty() 
        {
            if(s1.empty() && s2.empty())
                return true; 
            else
                return false;
            
        }
};

int main()
{
    
}

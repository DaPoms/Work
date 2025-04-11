#include <string>
#include <iostream>
#include <memory>
using namespace std;
//Most of this was not made by me, provided by our textbook
// Implementation of a queue interface using an array with bounded capacity
template <typename T>
class ArrayQueue {

private:
    std::unique_ptr<T[]> data;                            // smart pointer to the underlying array
    int capacity;                                         // capacity of the underlying array
    int sz{0};                                            // current number of elements in the queue
    int f{0};                                             // index of the front of the queue

public:
    // Construct a new queue with given capacity (default 1000)
    ArrayQueue(int cap = 1000) : capacity(cap), data(std::make_unique<T[]>(cap)) { }

    
    int size() const { return sz; }                       // return number of elements in the queue
    bool empty() const { return sz == 0; }                // return whether the queue is currently empty
    const T& front() const { return data[f]; }            // return const reference to the first element
    T& front() { return data[f]; }                        // return live reference to the first element
    const T& back() const { return data[(f+sz-1)%capacity]; }  // return const reference to last element
    T& back() { return data[(f+sz-1)%capacity]; }         // return live reference to the last element
    
    void push(const T& elem) {                            // add element to the end of the queue
        if (size() == capacity)
           throw std::overflow_error("Queue overflow");
        int avail{(f + sz) % capacity};                   // compute next available index
        data[avail] = elem;
        sz++;
    }
    
    void pop() {                                         // remove the first element of the queue
        f = (f + 1) % capacity;                          // advance the front one step (circularly)
        sz--;
    }
};

template<typename T = int>
void dispAction(string action, ArrayQueue<T>& passedQ, T elem = -1)
{
    if(action == "PO" )
        cout << "Popping element " << passedQ.front() <<  " at top of the que\n";
    else if(action == "PU")
        cout << "Pushing " << elem << " to the top of the que\n";
}

template<typename T>
void dispStack(ArrayQueue<T>& passedQ) //Not passing by reference or else it will actually affect the que
{
    while(!passedQ.empty())
    {
       cout << passedQ.front() << " ";
       passedQ.pop();
    }
    cout << '\n';
   
}

int main()
{
    ArrayQueue<int> q;
    dispAction("PU", q, 1);
    q.push(1);
    dispAction("PU", q,  2);
    q.push(2);
    dispAction("PU", q, 3);
    q.push(3);
    dispAction("PU", q, 4);
    q.push(4);
    dispAction("PO", q);
    q.pop();
    dispAction("PU", q, 5);
    q.push(5);
    dispStack(q);
}

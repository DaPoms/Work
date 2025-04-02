/*	File:	stackV.cpp
	By:
	Last Modified:	2-Apr-2025
	Implement a stack class that adapts a Vector class as a container type, and
	demonstarte its working
*/

// include necessary header files here
#include <iostream>
#include <string>
// Copy here the Code Fragment 5.5.1 for Vector class (not made by me)
using namespace std;
template <typename T>
class Vector {
  private:
    int cap{0};                            // capacity of the array
    int sz{0};                             // number of actual entries
    T* data{nullptr};                      // pointer to array of elements

  public:
    // Constructs an empty vector
    Vector() {}

    // Returns the current capacity of the underlying array
    int capacity() const { return cap; }

    // Returns the number of elements stored
    int size() const { return sz; }

    // Tests whether the vector is empty.
    bool empty() const { return sz == 0; }


    // Returns a const reference to the last element. behavior is undefined if vector is empty
    const T& back() const { return data[sz - 1]; }

    // Returns a live reference to the last element; behavior is undefined if vector is empty
    T& back() { return data[sz - 1]; }

    // Requests that the vector capacity be at least as large as the indicated capacity
    void reserve(int minimum) {
        if (cap < minimum) {
            T* temp{new T[minimum]};
            for (int k = 0; k < sz; k++)
                temp[k] = move(data[k]);
            delete[] data;                             // delete old array (if any)
            data = move(temp);                         // begin using new array
            cap = minimum;                             // new capacity
        }
    }

    // Inserts an element at end of the vector
    void push_back(const T& elem) {
        if (sz == cap) reserve(max(1, 2 * cap));       // double array size
        data[sz++] = elem;
    }

    // Removes an element from the end of the vector
    void pop_back() { sz--; }


    
};
// You may omit the member functions that are not needed for stack implementation

// Copy here the Code Fragment 7.1.2 for stack class implementation that adapts a Vector class as a container type
template <typename T, typename Container = Vector<T>>
class stack {
  private:
    Container data;            // use a Container instance for storage
  public:
    void push(const T& elem) { data.push_back(elem); }
    void pop() { data.pop_back(); }
    T& top() { return data.back(); }
    const T& top() const { return data.back(); }
    int size() const { return data.size(); }
    bool empty() const { return data.empty(); }
};
// Write a dispStack function that displays total number of elements in the stack and the element at the top.
template < typename T >
void dispStack(stack<T> passedStack)
{
    cout << passedStack.size() << " elements on the stack."<< " The top value is: " << passedStack.top() << '\n';
}
// Write a dispAction function that displays the action being performed (1st parameter) and 
// the element (2nd parameter) pushed on stack (if the action is "Push") 
//PS: (The instructions I was given seem wrong, our stack must be the 1st param as
// this is instructed to be made outside the stack class, and is the one required thing for all cases, unlike elem, which is only input in "Push" cases
template < typename T >
void dispAction(stack<T> passedStack, string functName, T elem = -1)
{
    if(functName == "Push")
        cout << "Pushing " << elem << " on the stack ...\n";
    else if(functName == "Pop")
        cout << "Popping from the stack ...\n";
    else
        cout << "ERROR: functName of " << functName << " not an accepted function name.\n";
}

int main() {
    // Instantiate a stack S
    stack<int> S{};
    // Push the following elements one by one: 10, 16, 4, 12
    dispAction(S, "Push", 10);
    S.push(10);
    dispStack(S);

    dispAction(S, "Push", 16);
    S.push(16);
    dispStack(S);

    dispAction(S, "Push", 4);
    S.push(4);
    dispStack(S);

    dispAction(S, "Push", 12);
    S.push(12);
    dispStack(S);
    // Pop elemenets twice one by one
    dispAction(S, "Pop");
    S.pop();
    dispStack(S);

    dispAction(S, "Pop");
    S.pop();
    dispStack(S);
    // For each of the above actions, first display action, perform action, and then display the stack.
    /* The expected output is like:
        Pushing 10 on the stack ...
        1 elements on the stack. The one at the top is: 10
        Pushing 16 on the stack ...
        2 elements on the stack. The one at the top is: 16
        Pushing 4 on the stack ...
        3 elements on the stack. The one at the top is: 4
        Pushing 12 on the stack ...
        4 elements on the stack. The one at the top is: 12
        Popping from the stack ...
        3 elements on the stack. The one at the top is: 4
        Popping from the stack ...
        2 elements on the stack. The one at the top is: 16
    */
        return 0 ;
    }


    //Lesson learned - containers allow an object to utilize multiple data structures as long as the functions used are shared by both data structures. 
    //The more simplistic way to me that we basically just learned that you can template objects (like vectors or Deques), not just primitive types(int, doubles, etc..).

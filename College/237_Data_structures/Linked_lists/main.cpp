#include <iostream>
#include <string>
using namespace std;
//None of the below code was written by me unless stated otherwise, this was a class activity to play around with linked lists (even though I already know them, but our class is going over it again)

template <typename T>
class SinglyLinkedList {
  private:
    //---------------- nested Node class ----------------
    class Node {
      public:
        T elem;                                   // stored element
        Node* next;                               // pointer to next node

        Node(const T& element, Node* nxt = nullptr) : elem{element}, next{nxt} {}
    };  //------------ end of nested Node class ------------

    // SinglyLinkedList instance variables
    int sz{0};                                    // number of entries in the list
    Node* head{nullptr};                          // raw pointer to first node of list
    Node* tail{nullptr};                          // raw pointer to last node of list

  public:
    SinglyLinkedList() {}                         // Constructs an empty list

    // ---------- Accessor functions ----------
    int size() const { return sz; }               // Returns the number of elements stored
    bool empty() const { return sz == 0; }        // Tests whether the list is empty
    T& front() { return head->elem; }             // Live reference to first element
    const T& front() const { return head->elem; } // Const reference to first element
    T& back() { return tail->elem; }              // Live reference to last element
    const T& back() const { return tail->elem; }  // Const reference to last element

    // ---------- Update functions ----------

    // Inserts element at the beginning of the list
    void push_front(const T& elem) {
        head = new Node(elem, head);              // new head uses old head (possibly null) as next
        if (sz == 0)
            tail = head;                          // special case: newest node is also the tail
        sz++;
    }

    // Inserts element at the end of the list
    void push_back(const T& elem) {
        Node* newest{new Node(elem)};
        if (sz == 0)
            head = newest;                        // newest node becomes head
        else
            tail->next = newest;                  // new node follows old tail
        tail = newest;                            // in either case, newest node becomes the tail
        sz++;
    }

    // Removes the first element of the list; behavior is undefined if list is empty
    void pop_front() {
        Node* old{head};
        head = head->next;
        delete old;
        sz--;
        if (sz == 0)
            tail = nullptr;                       // special case as list is now empty
    }

    void dispList()// I made this function in its entirety, though it's a very simple function
    {
        Node* traverse = head;

        while(traverse)
        {
            cout << traverse->elem << " -> ";
            traverse = traverse -> next;
        }        
        cout << "EOL\n";
    }
};


template <typename T>
class CircularlyLinkedList {
  private:
    class Node {
        public:
          T elem;                                   // stored element
          Node* next;                               // pointer to next node
  
          Node(const T& element, Node* nxt = nullptr) : elem{element}, next{nxt} {}
      };  //------------ end of nested Node class ------------

    // instance variables of the CircularlyLinkedList
    int sz{0};                                           // number of entries in the list
    Node* tail{nullptr};                                 // the node storing last element of the list

  public:
    CircularlyLinkedList() {}                            // Constructs an empty list

    // ---------- access functions ----------
    int size() const { return sz; }                      // Returns the number of elements stored
    bool empty() const { return sz == 0; }               // Tests whether the list is empty.
    T& front() { return tail->next->elem; }              // Live reference to first element
    const T& front() const { return tail->next->elem; }  // Const reference to first element
    T& back() { return tail->elem; }                     // Live reference to last element
    const T& back() const { return tail->elem; }         // Const reference to last element

    // ---------- update functions ----------

    // Inserts element at the beginning of the list
    void push_front(const T& elem) {
        if (sz == 0) {
            tail = new Node(elem);
            tail->next = tail;                           // link to itself circularly
        } else {
            tail->next = new Node(elem, tail->next);     // splice new node after the tail
        }
        sz++;
    }

    // Inserts element at the end of the list
    void push_back(const T& elem) {
        push_front(elem);                                // start by inserting at front of list
        tail = tail->next;                               // then rotate newest node to be tail
    }

    // Removes the first element of the list
    void pop_front() {
        Node* head = tail->next;
        if (head == tail)
            tail = nullptr;                              // must be the only node left
        else
            tail->next = head->next;
        delete head;
        sz--;
    }

    // Rotates the first element to the back of the list
    void rotate() {
        if (tail != nullptr)                             // if empty, do nothing
            tail = tail->next;                           // otherwise, the old head becomes the new tail
    }

    void dispList()// I made this function in its entirety, though it's a very simple function
    {
        Node* traverse{};
        if(tail) //If tail exists
        {
            traverse = tail -> next; //starts at head
            cout << traverse->elem << " -> ";
            traverse = traverse -> next; //Decided to manuall do the 1st cout to work around the case where tail is = to head. Without this statement, it would print nothing
        }
        while(traverse != tail)
        {
            cout << traverse -> elem << " -> ";
            traverse = traverse -> next;
        }
        cout << "EOL\n"; //Printings the nullpointer, whic his always the ->next of the last node
    }
};

void dispAction(string action, int i = 0) // I wrote this function in its entirety
{
    if (action == "PF")
        cout << "Executing a push front of value: " << i << " on the linked list\n";
    else if (action == "PB")
        cout << "Executing a push back of value: " << i << " on the linked list\n";
    else if (action == "PP")
        cout << "Executing pop front on the linked list.\n";
    else
        cout << "ERROR! Wrong parameters in function call dispAction(), string '" << action << "' not accepted. (must be \"PF\" or \"PB\")\n";
}
int main()
{

    SinglyLinkedList<int> L{};
    CircularlyLinkedList<int> C{};
    cout << "==========Test of Singly Linked List ==========\n\n";
    dispAction("PF", 20) ; L.push_front(20); L.dispList() ;
    dispAction("PF", 10) ; L.push_front(10); L.dispList() ;
    dispAction("PB", 16) ; L.push_back(16); L.dispList() ;
    dispAction("PB", 40) ; L.push_back(40); L.dispList() ;
    dispAction("PB", 30) ; L.push_back(30); L.dispList() ;
    dispAction("PP") ; L.pop_front(); L.dispList() ;
    dispAction("PP") ; L.pop_front(); L.dispList() ;

    cout << "\n==========Test of Circularly Linked List ==========\n\n";
    dispAction("PF", 20) ; C.push_front(20); C.dispList() ;
    dispAction("PF", 10) ; C.push_front(10); C.dispList() ;
    dispAction("PB", 16) ; C.push_back(16); C.dispList() ;
    dispAction("PB", 40) ; C.push_back(40); C.dispList() ;
    dispAction("PB", 30) ; C.push_back(30); C.dispList() ;
    dispAction("PP") ; C.pop_front(); C.dispList() ;
    dispAction("PP") ; C.pop_front(); C.dispList() ;
}

#include <iostream>
//Struct taken from leetcode (not my work)
 struct ListNode 
 {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
    ListNode* reverseList(ListNode* head) 
    {
        if(!head || !head -> next)
            return head;
        ListNode* new_head = reverseList(head -> next);
        (head -> next) -> next = head; //Changes the direction of the current rightmost node
        head -> next = nullptr; // the node before the one being reversed must be pointing to null or else the list becomes circular at what was supposed to be the end (doesn't end)
        return new_head;
    }

int main()
{
    ListNode* test = new ListNode(1);
    test -> next = new ListNode(2);
    test -> next -> next = new ListNode(3);
    test -> next -> next -> next = new ListNode(4);
    test -> next -> next -> next -> next = new ListNode(5);
    ListNode* ans = reverseList(test);
    while(ans) //Not a good practice but I don't need a traversal pointer because I'm not using "ans" after this 
    {
        std::cout << ans -> val << " ";
        ans = ans -> next;
    }
}

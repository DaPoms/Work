#include <iostream>
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* deleteDuplicates(ListNode* head) 
    {
        ListNode* traverse{head}; //Traverses Nodes that are the duplicates of target, then is used as the next target node once a new value is reached
        ListNode* target{}; //The node we look for duplicates of
        while(traverse && traverse -> next)
        {
            target = traverse;
             while(traverse -> next && target -> val == traverse -> next -> val)
                traverse = traverse -> next;
             target -> next = traverse -> next;
             traverse = traverse -> next;
        }
        return head;    
    }

    int main()
    {
        ListNode* test = new ListNode(1);
        test -> next = new ListNode(1);
        test -> next -> next = new ListNode(1);
        //  test -> next -> next -> next = new ListNode(3);
        // test -> next -> next -> next -> next = new ListNode(3);
        

        deleteDuplicates(test);

        ListNode* traverse = test;
        while(traverse)
        {  
            std::cout << traverse -> val <<  " ";
            traverse = traverse -> next;
        }
    }

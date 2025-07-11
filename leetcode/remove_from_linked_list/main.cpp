//ListNode struct taken from leetcode
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
}; 
    
ListNode* removeElements(ListNode* head, int val) 
{
    ListNode* toBeDeleted;
    ListNode* traverse = head;

    while(traverse && traverse -> val == val) //Move up the head
    {
        toBeDeleted = traverse;
        traverse = traverse -> next;
        delete toBeDeleted;
        head = traverse;
    }
    traverse = head;
    while(traverse && traverse -> next)
    {
        if(traverse -> next -> val == val)
        {
            toBeDeleted = traverse -> next; 
            traverse -> next = traverse -> next -> next;
            delete toBeDeleted; //To prevent memory leaks
        }
        else
            traverse = traverse -> next;
    }
    return head;
}

int main()
{
    ListNode* test = new ListNode(7);
    test -> next = new ListNode(7);
    test -> next -> next = new ListNode(7);
    test -> next -> next -> next = new ListNode(7);
    removeElements(test, 7);
}

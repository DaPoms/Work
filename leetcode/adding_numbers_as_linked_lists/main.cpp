#include <iostream>
//struct taken from leetcode
 struct ListNode 
 {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
{
int adding{0};
ListNode* ans;
ListNode* traverseAns;
if(l1 && l2)
    ans = new ListNode(l1 -> val + l2 -> val);
else if(l1)
    ans = new ListNode(l1 -> val);
else if(l2)
    ans = new ListNode(l2 -> val);
else //Case of empty lists
    return ans;

traverseAns = ans;
if(traverseAns -> val > 9)
{
    traverseAns -> val -= 10;
    adding++;
}
l1 = l1 -> next; //Using l1 and l2 to traverse is not the best practice, but we aren't reusing the two linked lists being added so I didn't use a traversing pointer (this strategy makes l1 and l2 lose access to all nodes at the end)
l2 = l2 -> next;
while(l1 && l2) //Adding nodes at the same digit
{
    traverseAns -> next = new ListNode(l1 -> val + l2 -> val + adding);
    if(adding > 0) //resets adding after each case
        adding = 0;
    if(traverseAns -> next -> val > 9)
    {
        traverseAns -> next -> val -= 10;
        adding++;
    }
    traverseAns = traverseAns -> next;
    l1 = l1 -> next;
    l2 = l2 -> next;
}
while(l1) //Adding the nodes for the digits the other number does not
{
    traverseAns -> next = new ListNode(l1 -> val + adding);
    if(adding > 0) //resets adding after each case
        adding = 0;
    if(traverseAns -> next -> val > 9)
    {
        traverseAns -> next -> val -= 10;
        adding++;
    }
    traverseAns = traverseAns -> next;
    l1 = l1 -> next;
}
while(l2)
{
    traverseAns -> next = new ListNode(l2 -> val + adding);
    if(adding > 0) //resets adding after each case
        adding = 0;
    if(traverseAns -> next -> val > 9)
    {
        traverseAns -> next -> val -= 10;
        adding++;
    }
    traverseAns = traverseAns -> next;
    l2 = l2 -> next;
}
if(adding > 0) //Case of needing to add a digit at the end
    traverseAns -> next = new ListNode(1);
return ans;
}

int main()
{
    ListNode *test1 = new ListNode(2);
    test1 -> next = new ListNode(4);
    test1 -> next -> next = new ListNode(3);

    ListNode *test2 = new ListNode(5);
    test2 -> next = new ListNode(6);
    test2 -> next -> next = new ListNode(4);

    ListNode *ans = addTwoNumbers(test1, test2);

    while(ans)
    {
        std::cout << ans -> val << " ";
        ans = ans -> next;
    }
}

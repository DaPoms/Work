#include <vector>
#include <algorithm>
using namespace std;
//Node struct taken from leetcode 
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
//The more efficient solution I learned of (so not fully done by me)
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) 
{
    ListNode* left = headA;
    ListNode* right = headB;
    while (left != right)
    {
        if(left == nullptr) left = headB; //By swapping when null, we cancel out the diffence in size, 
        else left = left -> next;
        if(right == nullptr) right = headA;
        else right = right -> next;
    }
    return left;
}

//My inefficient method (has to check through every node of vector B for each elem of A)
/* 
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) 
{
    vector<ListNode*> a;
    vector<ListNode*> b;
    while(headA)
    {
        a.push_back(headA);
        headA = headA -> next;
    }

    while(headB)
    {
        b.push_back(headB);
        headB = headB -> next;
    }

    for(ListNode *node : a)
    {
        if(find(b.begin(), b.end(), node) != b.end() ) //If the iterator == b.end() then the elem was not found
            return node;
    }
    return nullptr;
} 
*/

int main()
{
    ListNode* intersect = new ListNode(2);

    ListNode *testL = new ListNode(1);
    testL -> next = new ListNode(9);
    testL -> next -> next = new ListNode(1);
    testL -> next -> next -> next = intersect;

    ListNode *testR = new ListNode(3);
    //testR -> next = intersect;

    getIntersectionNode(testL, testR);

}

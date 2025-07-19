#include <vector>
#include <iostream>
#include <deque>
using namespace std;
struct ListNode { //Struct taken from leetcode
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

 //Very lightly usage of recursion in this approach

void helper(ListNode *node, std::vector<ListNode*>& nodes)
{
    if(!node)
        return;
    nodes.push_back(node);
    helper(node -> next, nodes);

}
void reorderList(ListNode* head) 
{
    std::vector<ListNode*> nodes;
    ListNode* toBeAdded;
    helper(head, nodes);
    int left{0};
    int right{static_cast<int>(nodes.size() - 1)};
    while(left != right && (left < right))
    {
        nodes[left] -> next = nodes[right];
        left++;
        nodes[right] -> next = nodes[left];
        right--;
    }
    if(left == right)
        nodes[left] -> next = nullptr;
    else if(left > right)
    {
        right++;
        nodes[right] -> next = nullptr;
    }
}

int main()
{
    ListNode *test = new ListNode(1);
    test -> next = new ListNode(2);
    test -> next -> next = new ListNode(3);
    test -> next -> next -> next = new ListNode(4);
    reorderList(test);
    while(test)
    {
        std::cout << test -> val << " ";
        test = test -> next;
    }
}

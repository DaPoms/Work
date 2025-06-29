#include <vector>
#include <map>
#include <iostream>

//ListNode is taken from leetcode
 struct ListNode 
 {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };
 
using namespace std;
    bool hasCycle(ListNode *head) 
    {
        map<ListNode*,int> visited; //Key is the node, value is the count of that node value
        //PS: The key has to be node pointers for the case that there are multiple nodes with the same value, as if you do value it will detect these nodes as the same, when they aren't
        ListNode* traverse = head;
        while(traverse)
        {
            visited[traverse]++;
            if(visited[traverse] > 1)
                return true;
            traverse = traverse -> next;
            
        }
        return false;
    }

    int main()
    {
        ListNode* ans = new ListNode(3);
        ans -> next = new ListNode(2);
        ans -> next -> next = new ListNode(0);
        ListNode* cycle = new ListNode(-4);
        ans -> next -> next -> next = cycle;
        cycle -> next = ans -> next;

        cout << hasCycle(ans);
    }

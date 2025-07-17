 #include <deque>
 #include <iostream>
 using namespace std;
 struct ListNode { //struct listnode copied from leetcode (not made by me)
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
void helper(ListNode* node, deque<int>& ans, bool& isFalse)
{
    if(!node)
        return;
     ans.push_back(node -> val);
    helper(node -> next, ans, isFalse);
    if(!ans.empty())
    {
        if(ans.front() == node -> val)
        {        
            if(ans.size() >= 2)
            {
                ans.pop_back();
                ans.pop_front();
            }
            else if(ans.size() == 1)
                ans.pop_back();
        }
        else    
            isFalse = true;
    }

    
}
bool isPalindrome(ListNode* head) 
{
    deque<int> ans;
    bool isFalse{false};
    helper(head, ans, isFalse);
    if(isFalse)
        return false;
    return true;
}
/* bool isPalindrome(ListNode* head) 
{
    if(!head -> next)
        return true;
    stack<int> nextWord;
    ListNode* traverse = head;
    while (traverse)
    {
        if(!nextWord.empty() && nextWord.top() == traverse -> val)
            nextWord.pop();
        else
            nextWord.push(traverse -> val);
        traverse = traverse -> next;
    }
    if(nextWord.empty())
        return true;
    else
        return false;
} */
int main()
{
    ListNode* test = new ListNode(2);
    test -> next = new ListNode(2);
    test -> next -> next = new ListNode(1);
    //test -> next -> next -> next = new ListNode(1);

    cout << isPalindrome(test);
}

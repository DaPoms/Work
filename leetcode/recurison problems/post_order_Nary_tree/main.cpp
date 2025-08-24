#include <vector>
#include <iostream>
using namespace std;
// Definition for a Node. This class is made by Leetcode (not me)
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

    void helper(Node* root, vector<int>& ans)
    {
        for(Node* child : root -> children)
        {
            helper(child, ans);
            ans.push_back(child -> val);
        }
       
        
    }
    vector<int> postorder(Node* root) 
    {
        vector<int> ans;
        if(!root) //empty tree case
            return ans;
        helper(root, ans);
        ans.push_back(root -> val);
        return ans;
    }
int main()
{
    Node* val5 = new Node(5);
    Node* val6 = new Node(6);

    Node* val3 = new Node(3, vector<Node*>{val5, val6});
    Node* val2 = new Node(2);
    Node* val4 = new Node(4);

    Node* root = new Node(1, vector<Node*>{val3, val2, val4});
    

   //The way implimented test in main makes it so that the null Nodes are visited, I like this more as it shows the traversal of null nodes too.
    vector<int> ans = postorder(root);
    cout << "[ ";
    for(int num : ans)
    {
        cout << num << " ";
    }
    cout << ']';
}

#include <iostream>
#include <vector>
using namespace std;
//Node class taken from leetcode
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
 
    void helper(TreeNode* root, vector<int>& ans)
    {  
        if(!root)
            return;
        ans.push_back(root -> val);
        helper(root -> left, ans);
        helper(root -> right, ans);
    }
    vector<int> preorderTraversal(TreeNode* root) //Preorder traversal means that parent nodes must be visited before visiting children nodes
    {
        vector<int> ans;
        helper(root, ans);
        return ans;
    }

    int main()
    {
        TreeNode* test = new TreeNode(1, new TreeNode(2), new TreeNode(3));
        vector<int> ans = preorderTraversal(test);
        for(int num : ans)
            cout << num << " ";
    }

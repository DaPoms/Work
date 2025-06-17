 #include <vector>
 #include <iostream>
 using namespace std;
 //TreeNode was not made by me, it was copied from leetcode
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
//

//Altered approach (adding a vector passed by reference so you don't need a helper function + void instead of vector return type)
    void inorderTraversal(TreeNode* root, vector<int>& ans) 
    {
        if(!root) //Once nullptr is reached
            return;
        inorderTraversal(root -> left, ans);
        ans.push_back(root -> val); 
        inorderTraversal(root -> right, ans);
    }

int main()
{
    
    TreeNode node2{3, nullptr, nullptr};
    TreeNode node1{2, &node2, nullptr};
    TreeNode test{1,nullptr, &node1};
    
    vector<int> ans{};
    inorderTraversal(&test, ans);
    for(int num : ans)
        cout << num << " ";
}

//Helper function approach
/* 
    void helper(TreeNode* root, vector<int>& ans)
    {
        if(!root)
            return;
        helper(root -> left, ans);
        ans.push_back(root -> val); 
        helper(root -> right, ans);
    }
    vector<int> inorderTraversal(TreeNode* root) 
    {
        vector<int> ans;
        helper(root, ans);
        return ans;
    }
 */

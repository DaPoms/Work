#include <iostream>
#include <vector>
using namespace std;
//Node struct taken from leetcode 
 struct TreeNode 
 {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

/* void helperLeft(TreeNode* root, vector<int>& ans)
{
    if(!root)
        return;
    ans.push_back(root -> val);
    helperLeft(root -> left, ans);
    helperLeft(root -> right, ans);
}

void helperRight(TreeNode* root, vector<int>& ans)
{
    if(!root)
        return;
    ans.push_back(root -> val);
    helperRight(root -> right, ans);
    helperRight(root -> left, ans);
}

bool isSymmetric(TreeNode* root)
{
    vector<int> left;
    helperLeft(root -> left, left); //Traverse left side
    vector<int> right;
    helperRight(root -> right, right); //Traverse right side

    if(left == right)
        return true;
    return false;
} */

bool helper(TreeNode* left, TreeNode* right)
{
    if(!left && !right)
        return true;
    if(!left || !right)
        return false;
    if(left -> val != right -> val)
        return false;
        
    return helper(left -> left, right -> right) && helper(left -> right, right -> left);
}
bool isSymmetric(TreeNode* root)
{
    return helper(root -> left, root -> right);
}

 int main()
 {
    TreeNode test{1, new TreeNode(2, nullptr, new TreeNode(3)), new TreeNode(2, nullptr, new TreeNode(3))};
    cout << isSymmetric(&test);
 }

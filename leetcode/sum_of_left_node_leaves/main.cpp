#include <iostream>
//struct taken from leetcode (not made by me)
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

void helper(TreeNode* root, int& leftSum)
{
    if(!root)
        return;
    if(root -> left)
        if(!(root -> left -> left) && !(root -> left -> right))
            leftSum += root -> left -> val;
    helper(root -> left, leftSum);
    helper(root -> right, leftSum);
    
}
int sumOfLeftLeaves(TreeNode* root) 
{
    int leftSum{0};
    helper(root, leftSum);
    return leftSum;    
}

int main()
{
    TreeNode *test = new TreeNode(1, new TreeNode(3, new TreeNode(12), nullptr), new TreeNode(5, new TreeNode(3), new TreeNode(1)));
    std::cout << sumOfLeftLeaves(test); //should return 15
}

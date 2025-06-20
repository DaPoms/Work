#include <iostream>
//Struct provided from leetcode
struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };


int maxDepth(TreeNode* root) 
{
    if(!root)
        return 0;
    int depthL = maxDepth(root -> left);
    int depthR = maxDepth(root -> right);
    return std::max(depthL, depthR) + 1;
}
    
int main()
{
    TreeNode test = {3, new TreeNode(9, nullptr, nullptr), new TreeNode(20, new TreeNode(15, nullptr,nullptr), new TreeNode(7, nullptr, nullptr))};
    // TreeNode test = {1, nullptr, new TreeNode(2, nullptr, nullptr)};
    std::cout << maxDepth(&test);
}


/* void helper(TreeNode* root, int& depth, bool& goUp)
{
    

    if(!root)
    {
        goUp = true;
        return;
    }
    
    if(goUp)
        ++depth;

    helper(root -> left, depth, goUp);
    helper(root -> right, depth, goUp);
} */

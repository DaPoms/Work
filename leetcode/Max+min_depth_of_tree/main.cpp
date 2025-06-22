#include <iostream>
#include <vector>
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


int minDepth(TreeNode* root) //I had to get help for this one again
{
    if (!root) return 0; //If root is null, it is 0
    if (!(root -> left) && !(root -> right)) return 1; //If node is a leaf, it counts as the start of height counting
    if(!root -> left) return 1 + minDepth(root -> right); //If left node does not exist, we traverse the right one
    if(!root -> right) return 1 + minDepth(root -> left); //If right node does not exist, we traverse the left one
    return std::min(1 + minDepth(root -> left), 1 + minDepth(root -> right)); //We're looking for mins, so thus we return the min between the two
}


    
int main()
{
    TreeNode test = {3, new TreeNode(9, nullptr, nullptr), new TreeNode(20, new TreeNode(15, nullptr,nullptr), new TreeNode(7, nullptr, nullptr))};
    // TreeNode test = {1, nullptr, new TreeNode(2, nullptr, nullptr)};
    std::cout << maxDepth(&test) << '\n';
    std::cout << minDepth(&test);
}



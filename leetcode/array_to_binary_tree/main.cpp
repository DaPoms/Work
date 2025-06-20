#include <iostream>
#include <vector>

//TreeNode struct taken from leetcode
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//I got help for this approach (recursive approach)
TreeNode* helper(std::vector<int>& nums, int left, int right)
{
    //This algorithmn reminds me of a binary search algorithm
    if(left > right) //If value could not be found that belongs at this node position, then we just make the node null
        return nullptr;

    int mid = (left + right) / 2; //Wprks on the idea of making a bunch of subtrees based on a root and its left and right children
    TreeNode* root = new TreeNode(nums[mid]); //The middle vals are the nodes that are likely to have both left and right children, allowing for proper balancing by placing them as the higher up parent nodes 
    root->left = helper(nums, left, mid - 1);
    root->right = helper(nums, mid + 1, right); //Every left side node also forms the ride part of the left side with this, and likewise for the right
    return root;
}

TreeNode* sortedArrayToBST(std::vector<int>& nums)
{
    return helper(nums, 0, nums.size() - 1);
}

//My iterative attempt (works, but is not balanced)
/* TreeNode* sortedArrayToBST(std::vector<int>& nums)
{
    int midIndex{-1};
    int traverseArr{0};
    TreeNode* traverseNode;
    TreeNode* ans;
    if(true) //If odd
    {
        midIndex = {static_cast<int>(nums.size()) / 2};
        ans = new TreeNode(nums[midIndex]);
        traverseNode = ans;

        while(traverseArr < midIndex)
        {
            if(nums[traverseArr] < traverseNode -> val)
            {
                traverseNode -> left = new TreeNode(nums[traverseArr]);
                traverseNode = traverseNode -> left;
            }
            else
            {
                traverseNode -> right = new TreeNode(nums[traverseArr]);
                traverseNode = traverseNode -> right;
            }
            traverseArr++;
        }

        traverseArr = midIndex + 1;
        traverseNode = ans; //Sets back to root
        while (traverseArr < nums.size())
        {
           if(nums[traverseArr] < traverseNode -> val)
            {
                traverseNode -> left = new TreeNode(nums[traverseArr]);
                traverseNode = traverseNode -> left;
            }
            else
            {
                traverseNode -> right = new TreeNode(nums[traverseArr]);
                traverseNode = traverseNode -> right;
            }
            traverseArr++;
        }
    }
    return ans;

} */

int main()
{
    std::vector<int> test{0,1,2,3,4,5};
    sortedArrayToBST(test);
    
}

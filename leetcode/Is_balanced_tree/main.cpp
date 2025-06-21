 #include <iostream>
 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
 //This is the first recursion tree problem I was able to do mostly solo, so we're making progress!

int helper(TreeNode* root)
    {
        if(!root)
            return 0;
        
        int leftH = helper(root -> left);
        if(leftH == -1) return -1; //Ensures that if rule is broken once, it is brought up from the bottom to the top (so the return doesn't get ignored)
        int rightH = helper(root -> right);
        if(rightH == -1) return -1;
        if(std::abs(leftH - rightH) <= 1) //Absolute value is important as the difference must be less than or equal to one, and that could mean the left is less than the right leading to a negative
            return std::max(leftH, rightH) + 1; //The height of a node is based on which subtree has more height: The left or the right, then + 1 as the node is the parent of the left and right subtrees
 
        return -1;
    }
    bool isBalanced(TreeNode* root) 
    {
        int ans = helper(root);
        if(ans == -1)
            return false;
        else
            return true;
    }

    int main()
    {
        TreeNode* test = new TreeNode(1, new TreeNode(2, new TreeNode(3, new TreeNode(4), new TreeNode(4) ), new TreeNode(3) ), new TreeNode(2));
        std::cout << isBalanced(test);
    }

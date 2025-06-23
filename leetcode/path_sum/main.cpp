  #include <iostream>
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };
  
    
    bool hasPathSum(TreeNode* root, int targetSum) 
    {
        if(!root) //Case of null node (for empty tree)
            return false;
        if(!root -> left && !root -> right) //Case of leaf node
            return targetSum - root -> val == 0; //The target sum calculation ends on the leaf node, so if after subtracting the val of the leaf, it cancels out the target, we know it's the answer
        targetSum -= root -> val;

        return hasPathSum(root -> left, targetSum) || hasPathSum(root -> right, targetSum);
    }

    int main()
    {
        TreeNode* test = new TreeNode(5, new TreeNode(4, new TreeNode(11, new TreeNode(7), new TreeNode(2)), nullptr ), new TreeNode(8, new TreeNode(13), new TreeNode(4, nullptr, new TreeNode(1) ) ) );
        std::cout << hasPathSum(test, 22);
    }

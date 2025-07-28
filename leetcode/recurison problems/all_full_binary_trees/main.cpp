#include <vector>
using namespace std;
//Note: This is the best recursion problem for myself because this is almost exactly what I need to do for my wublin project
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
void helper(TreeNode* root)
{
//Need an algorithm for doing every combo of: Place two child nodes OR place 2 null pointers
}

vector<TreeNode*> allPossibleFBT(int n) 
{
    TreeNode* root = new TreeNode(0, nullptr, nullptr);
    helper(root);
}

int main()
{}

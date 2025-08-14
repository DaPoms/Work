#include <iostream>
#include <vector>
using namespace std;

struct TreeNode { //Struct taken from leetcode
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
/*  
void helper(TreeNode* node, string path, vector<string>& paths)
{

    if(!node)
        return;
    else if(!node -> left && !node-> right) //Case of reaching leaf node, indicates the end of a path
    {
        path += "->" + to_string(node -> val);
        paths.push_back(path);
        return;
    }
    
    path += "->" + to_string(node -> val);
    helper(node -> left, path, paths);
    helper(node -> right, path, paths);
    
    
}
vector<string> binaryTreePaths(TreeNode* root) 
{
    
    string path = to_string(root -> val);
    vector<string> paths;
    if(!root -> left && !root -> right)
    {
        paths.push_back(path);
        return paths;
    }
    helper(root -> left, path, paths);
    helper(root -> right, path , paths);

    return paths;
    
}
 */
//Second attempt made from looking at other people's code, makes my program slightly faster, but shows how close I was to the most optimal approach. 
//All I had to do was traverse from the root instead of left and right subtrees, and doing this simplifies (increases readability) the code significantly in terms of creating the path which is to be added to the paths vector
void helper(TreeNode* node, string path, vector<string>& paths)
{
    if(node -> left == nullptr && node-> right == nullptr) //Case of reaching leaf node, means we are at the end of a path
    {
        paths.push_back(path);
        return;
    }
    if(node -> left)
        helper(node -> left,  path + "->" + to_string(node -> left -> val), paths);
    if(node -> right)
        helper(node -> right,  path + "->" + to_string(node -> right -> val), paths); 
}
vector<string> binaryTreePaths(TreeNode* root) 
{
    
    string path = to_string(root -> val);
    vector<string> paths;
    helper(root, path, paths);
    return paths;
    
}

int main()
{
    TreeNode* test = new TreeNode(1, new TreeNode(2), new TreeNode(3));
    vector<string> ans = binaryTreePaths(test);  
    for(string paths : ans)
        cout << paths << '\n';
        
}

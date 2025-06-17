#include <iostream> 
#include <vector>
using namespace std;
struct TreeNode 
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode *right) : val(x), left(left), right(right) {}
 };


//This approach I had to get help (not my own code) to understand (I'm still working on recursion concepts)
bool isSameTree(TreeNode* p, TreeNode* q) 
{   
    //All 3 base cases
    if(!p && !q) //both null = true
        return true;
    if(!p || !q) //One null only
        return false;
    if(p -> val != q -> val) //Vals differ
        return false;
    
     return isSameTree(p -> left, q -> left) && isSameTree(p -> right, q -> right); //both the right and left side must have equal vals to be true (by recursion, every left nodes right nodes will also be visited)
}



//This is a very messy approach (but it works!). I realized that through the power of both inorder and preorder traversal, it addresses all the cases of testing equivalence


/*  void inorderTraversal(TreeNode* p, vector<int>& ans, int& left, int& right)
 {
    if(!p)
        return;
    else
    {
        inorderTraversal(p -> left, ans, left, right);
        ans.push_back(p -> val);
        if(p -> left) //To differentiate cases with the same vals but placed differently (EX: all 2's)
            left++;
        if(p -> right)
            right++;
        
        inorderTraversal(p -> right, ans, left , right);
    }
 }
 void preorderTraversal(TreeNode* p, vector<int>& ans, int& left, int& right)
 {
    if(!p)
        return;
    else
    {
       
        ans.push_back(p -> val);
        if(p -> left) //To differentiate cases with the same vals but placed differently (EX: all 2's)
            left++;
        if(p -> right)
            right++;
        preorderTraversal(p -> left, ans, left, right);
        preorderTraversal(p -> right, ans, left , right);
    }
 }
 
bool isSameTree(TreeNode* p, TreeNode* q) 
{
    vector<int> leftAns;
    vector<int> rightAns;
    int left1{0};
    int right1{0};
    int left2{0};
    int right2{0};
    preorderTraversal(p, leftAns, left1, right1);
    preorderTraversal(q, rightAns, left2, right2);

    vector<int> leftAns2;
    vector<int> rightAns2;
    inorderTraversal(p, leftAns2, left1, right1);
    inorderTraversal(q, rightAns2, left2, right2);

    if( (leftAns == rightAns || leftAns2 == rightAns2) && (left1 == left2) && (right1 == right2) )
        return true;
    else
        return false;
} */

int main()
{
    /* TreeNode leftNode1{2};
    TreeNode rightNode1{3};
    TreeNode test1{1, &leftNode1, &rightNode1};
    TreeNode leftNode2{2};
    TreeNode rightNode2{3};
    TreeNode test2{1, &leftNode2, &rightNode2}; */

   
 /*    TreeNode test1{2, new TreeNode(2, nullptr, new TreeNode(2, new TreeNode(2), nullptr) ) , new TreeNode(2)};
    TreeNode test2{2, (new TreeNode(2, new TreeNode(2), nullptr) ), (new TreeNode(2, new TreeNode(2), nullptr) )}; */

    /* TreeNode test1{10, new TreeNode(5), new TreeNode(15)};
    TreeNode test2{10, new TreeNode(5, nullptr, new TreeNode(15)), nullptr}; */

/*     TreeNode test1{5, ( new TreeNode(4, nullptr, new TreeNode(1, new TreeNode(2), nullptr) ) ), (new TreeNode(1, nullptr, new TreeNode(4, new TreeNode(2), nullptr)))};
    TreeNode test2{5, (new TreeNode(1, new TreeNode(4, nullptr, new TreeNode(2)), nullptr)), (new TreeNode(4, new TreeNode(1, nullptr, new TreeNode(2)), nullptr))}; */

    cout << isSameTree(&test1, &test2);
}

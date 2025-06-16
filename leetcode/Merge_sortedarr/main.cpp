#include <iostream>
#include <vector>

using namespace std;

//The approach leetcode accepted (you had to utilitze these spare "0's" that are forced on the left vector)
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) //n is the number of elements being added from the right element to the left one
{
    int addingIndex{n - 1};
    int leftEnd{m + n - 1};
    while(leftEnd >= m)
    {
        nums1[leftEnd] = nums2[addingIndex];
        addingIndex--;
        leftEnd--;
    }

    int placeholder{-1};
    //insertion sort for elements past m (not very efficient, but constraints were for a size of 200, which isn't sufficiently large to warrant a better approach to this problem)
    for(int i{m}; i <= m + n - 1; i++)
    {
        int traverse = i;
        while(traverse > 0 && nums1[traverse] < nums1[traverse - 1])
        {
            placeholder = nums1[traverse];
            nums1[traverse] = nums1[traverse - 1];
            nums1[traverse - 1] = placeholder;
            traverse--;
        }
    }
}


//My personal approach (that leetcode didn't like, and it also doesn't work for a lot of cases, but does work for the most general ones. This could be fixed easily)
/* void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) //n is the number of elements being added from the right element to the left one
{
    nums1.resize(m);
    int traverse = m - 1;
    int traverseAdding = n - 1;
    while(traverse >= 0)
    {
        if(nums2[traverseAdding] >= nums1[traverse] )
        {
            nums1.insert(nums1.begin() + traverse + 1, nums2[traverseAdding]);
            traverseAdding--;
        }
        else
            traverse--;
    }
} */

int main()
{
    vector<int> left = {4,5,6,0,0,0};
    vector<int> right = {1,2,3};

    merge(left, 3, right, 3);
    
    for(int num  : left)
        cout << num << " ";
}

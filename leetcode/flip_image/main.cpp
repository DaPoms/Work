#include <vector>
#include <iostream>
using namespace std;
vector<vector<int>> flipAndInvertImage(vector<vector<int>>& image) 
{
    vector<vector<int>> ans;
    
    for(vector<int> row : image)
    {
        vector<int> newRow;
        for(int i{static_cast<int>(row.size()) - 1}; i >= 0; i--) //reverse (add elems from back to the front)
        {
            newRow.push_back(row[i]);
        }
        ans.push_back(newRow);
    }
        
    for(vector<int>& row : ans)
    {
        for(int& num : row) //invert (flip all 0 -> 1, and 1 -> 0)
        {
            if(num == 0)
                num = 1;
            else
                num = 0;
        }
    }
    
    return ans;
}

int main()
{
    vector<vector<int>> test = {
    {1,1,0,0},
    {1,0,0,1},
    {0,1,1,1},
    {1,0,1,0}};
    test = flipAndInvertImage(test);
    for(vector<int> row : test)
    {
        for(int num : row)
        {
            cout << num << " ";
        }
        cout << '\n';
    }
}

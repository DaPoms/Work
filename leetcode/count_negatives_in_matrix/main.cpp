#include <iostream>
#include <vector>
using namespace std;
int countNegatives(vector<vector<int>>& grid) 
{
    int nCount{0};
    int size = grid[0].size();
    int i{size - 1};
    for(vector<int> row : grid)
    {
        i = size - 1;
        while(i >= 0 && row[i] < 0)
        {
            nCount++;
            i--;
        }
    }
    return nCount;
}

int main()
{
    vector<vector<int>> test = {
        {4,3,2,-1},
        {3,2,1,-1},
        {1,1,-1,-2},
        {-1,-1,-2,-3}
    };
    cout << countNegatives(test); //should return 8
}

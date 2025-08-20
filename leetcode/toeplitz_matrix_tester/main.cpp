#include <vector>
#include <iostream>
using namespace std;

bool isToeplitzMatrix(vector<vector<int>>& matrix) 
{
    int x{0};
    int y{static_cast<int>(matrix.size()) - 1};
    int xStart{x};
    int yStart{y};
    
    int rowVal;
    while( !(xStart == matrix[0].size() - 1 && yStart == 0) ) //upper right corner is always the end, but it also always follows the toeplitz rule, so we can skip it
    {
        rowVal = matrix[yStart][xStart];
        while(y < matrix.size() && x < matrix[0].size()) //There are two out of bounds cases for diagonal travel: the y axis and the x axis
        {
            if(matrix[y][x] != rowVal)
                return false;
            y++;
            x++;
        }
        
        if(yStart > 0)
            yStart--;
        else
            xStart++;
        x = xStart + 1;
        y = yStart + 1;
    }
    return true;
}

int main()
{
    vector<vector<int>> test = {
    {1,2,3,4},
    {5,1,2,3},
    {9,5,1,2}};
    /* 
    vector<vector<int>> test = {
        {1,2},
        {2,2} };
         */
    cout << isToeplitzMatrix(test);
}

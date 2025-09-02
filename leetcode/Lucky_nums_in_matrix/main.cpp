#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
vector<int> luckyNumbers(vector<vector<int>>& matrix) 
{
    int colI{0}; //Index of row that we want to traverse
    int rowI{0}; //Index of element in row 
    int minRow{INT_MAX};
    int maxCol{-1};
    vector<int> minRows;
    vector<int> maxCols;
    vector<int> ans;

    for(vector<int> row : matrix) //finding max vals for each row
    {
        for(int num : row)
        {
            if(num < minRow)
                minRow = num;
        }
        minRows.push_back(minRow);
        minRow = INT_MAX;
    }
    while(rowI < matrix[0].size()) //finding min vals for each column 
    {
        
        if(matrix[colI][rowI] > maxCol)
            maxCol = matrix[colI][rowI];
        
        colI++;
        if(colI == matrix.size())
        {
            maxCols.push_back(maxCol);
            colI = 0;
            maxCol = -1;
            rowI++;
        }
    }
    
    for(int num : minRows)
    {
        if(find(maxCols.begin(), maxCols.end(), num) != maxCols.end())
            ans.push_back(num);
    } 
    return ans;
}

int main()
{
    vector<vector<int>> test = {
        {1,10,4,2},
        {9,3,8,7},
        {15,16,17,12}};
    vector<int> ans = luckyNumbers(test);
    for(int num : ans)
        cout << num << " ";
}

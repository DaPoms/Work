#include <vector>
#include <iostream>
using namespace std;
int areaOfMaxDiagonal(vector<vector<int>>& dimensions) 
{
    int maxDiag{-1};
    int maxArea{-1};
    int maxI{0};
    for(vector<int> rectangle : dimensions)
    {
        int diag = (rectangle[0] * rectangle[0]) + (rectangle[1] * rectangle[1]);
        int area = rectangle[0] * rectangle[1];
        if(diag > maxDiag)
        {  
            maxArea = area;
            maxDiag = diag;
        }   
            else if (diag == maxDiag && area > maxArea)
                maxArea = area;  
    }
    return maxArea;
}

int main()
{
    vector<vector<int>> test = {{9,3}, {6,8}};
    cout << areaOfMaxDiagonal(test);
}

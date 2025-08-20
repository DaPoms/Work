#include <vector>
#include <iostream>
using namespace std;

int averageAdjacent(int targetX, int targetY, vector<vector<int>>& img) //returns the average of the element and all it's adjacent elements in the matrix
{
    // implimenting tests bounds: do we have a 3x3 or a 2x2? (those are the only 2 possible cases for square matrices)
    //bool isUpperLeftInBounds{ (targetX - 1 >= 0 && targetX - 1 < img.size()) && (targetY - 1 >= 0 && targetY < img[0].size()) }; //bool for if the upper left most square is in bounds
    //bool isLowerRightInBounds{ (targetX + 1 >= 0 && targetX + 1 < img.size()) && (targetY + 1 >= 0 && targetY < img[0].size()) }; //bool for if the lower right most square is in bounds
    //Adding bounds would make this even more efficient, mainly by limiting the x and y traversal to the squares we know exist. IF the upper left is outof bounds, we start 1 right and 1 down from the the upper left.
    //If the lower right is out of bounds, then we end our traversal one left and 1 up from the lower right bound that failed. I mainly didn't impliment this due to time, though I might come back to it later

    int sum{0};
    int count{0};
    //if(isUpperLeftInBounds && isLowerRightInBounds)
    for(int y{targetY - 1}; y <= targetY + 1; y++)
    {
        for(int x{targetX - 1}; x <= targetX + 1; x++)
        {
            if( (y >= 0 && y < img.size()) && x >= 0 && x < img[0].size())
            {
                sum += img[y][x]; //I previously had all the "x's" called a y's, but later realized that the first box in a 2d vector img[this box][] is y axis and the second box is the x
                count++;
            }
        }
    }
    return sum / count;
}
vector<vector<int>> imageSmoother(vector<vector<int>>& img) 
{
    vector<vector<int>> ans(img.size(), vector<int>(img[0].size())); 
    for(int y{0}; y < img.size(); y++) //traverses horizontally
    {
        for(int x{0}; x < img[0].size(); x++) //traverses vertically (IE: every row is traversed)
        {
            ans[y][x] = averageAdjacent(x, y, img); //does essentially all the work
        }
    }
    return ans;
}

int main()
{
    vector<vector<int>> matrix = { 
    {2,3,4},
    {5,6,7},
    {8,9,10},
    {11,12,13},
    {14,15,16}};
    vector<vector<int>> ans = imageSmoother(matrix);
    for(vector<int> row : ans)
    {
        for(int elem : row)
        {
            cout << elem << " ";
        }
        cout << '\n';
    }
    // for()
}

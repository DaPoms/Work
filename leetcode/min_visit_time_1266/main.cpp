#include <iostream>
#include <vector>

using namespace std;

int abs(int i)
{
    if(i < 0) return i * -1;
    else return i;
}

// apparently theres an even easier algorithm called chebyshev's distance formula which is just for each coordinate (x,y), which ever has the greater difference between both points is the distance between them.
// ex for vector<vector<int>> points = {{1,1}, {3,4}, {-1, 0}} :
/* 
    {1,1} {3,4} --> 1 - 3 = 2 (note this is the difference, so its the absolute val), 1 - 4 = 3. 2 < 3, distance is 3.
    {3,4} {-1,0} --> 3 -- 1 = 4, 4 - 0 = 4, 4 < 5 so distance between points if 4.
    3 + 4 = 7
*/
int moveToPoint(vector<int> start, vector<int>& end) //movement should prioritize diagonals thhen to other methods
{
    int time{0};
    int xDiff = abs(end[0] - start[0]); // direction of the movement doesnt matter when you're only considering one start and end point
    int yDiff = abs(end[1] - start[1]);
    int totalDiagJumpsAllowed;
    if (xDiff != 0 && yDiff != 0)
    { 
        if(xDiff > yDiff) totalDiagJumpsAllowed = yDiff;
        else totalDiagJumpsAllowed = xDiff;            
        xDiff -= totalDiagJumpsAllowed;
        yDiff -= totalDiagJumpsAllowed;
        time += totalDiagJumpsAllowed;
    }
    
    if (xDiff == 0)
        time += yDiff;
    else // case of (yDiff == 0)
        time += xDiff;

    return time;
}


int minTimeToVisitAllPoints(vector<vector<int>>& points) 
{
    int totalTime{0};
    for(int i{0}; i < points.size() - 1; i++) // for every point except the last...
        totalTime += moveToPoint(points[i], points[i + 1]);    
    return totalTime;
}

int main()
{
    vector<vector<int>> points = {{1,1}, {3,4}, {-1, 0}};
    cout << minTimeToVisitAllPoints(points);
}

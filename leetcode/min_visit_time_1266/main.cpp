#include <iostream>
#include <vector>

using namespace std;

int abs(int i)
{
    if(i < 0) return i * -1;
    else return i;
}

int moveToPoint(vector<int> start, vector<int>& end) //movement should prioritize diagonals thhen to other methods
{
    int time{0};
    int xDiff = abs(end[0] - start[0]);
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

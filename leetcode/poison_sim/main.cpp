#include <iostream>
#include <vector>
using namespace std;
int findPoisonedDuration(vector<int>& timeSeries, int duration) 
{
    if(duration == 0) return 0; //if duration is 0 we don't have to do anything obviously
    int totalTime{0};
    for(int i{0}; i < timeSeries.size() - 1; i++) //loops for every element except the last
    {
        if(timeSeries[i] + (duration - 1) >= timeSeries[i + 1])
            totalTime += timeSeries[i + 1] - timeSeries[i];
        else
            totalTime += duration;
    }
    
    totalTime += duration; //for the last element we always add the entire duration, as there is nothing after it to overwrite the poison timer
    return totalTime;
}

int main()
{
    vector<int> poisonProcTimes = {1,2,3,4,5};
    cout << findPoisonedDuration(poisonProcTimes, 5); //asking for the time spent poisioned if each poison proc lasts 5 seconds, but back to back procs of poison reset the poison timer
}   

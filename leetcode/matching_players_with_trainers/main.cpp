#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) 
{
    sort(players.begin(), players.end());
    sort(trainers.begin(), trainers.end());
    int count{0};
    int traversePlayers{0};
    int traverseTrainers{0};
    while(traversePlayers < players.size() && traverseTrainers < trainers.size())
    {
        if(players[traversePlayers] <= trainers[traverseTrainers])
        {
            count++;
            traverseTrainers++;
            traversePlayers++;
        }
        else
            traverseTrainers++;
    }
    return count;   
}

int main()
{
    vector<int> players = {4,7,9};
    vector<int> trainers = {8,2,5,8};
    
    cout << matchPlayersAndTrainers(players,trainers);
}

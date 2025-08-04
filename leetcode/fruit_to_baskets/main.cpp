#include <vector>
#include <map>
#include <iostream>
using namespace std;

//This is a very messy attempt, but I'm proud as it's a proper solution for a medium difficulty leetcode problem
int totalFruit(vector<int>& fruits) 
{
    int maxFruits{-1};
    int currFruits{0};
    int traverse{0};
    int streak{0};
    map<int, int> baskets; //Key is fruit number (The name of the fruit is a number), and value is the count of that fruit

    while(traverse < fruits.size()) //Till we reach the end, makes sure we compare all fruit paths for collection to find the greatest path
    {
        if(baskets.size() == 2 && baskets[ fruits[traverse] ] == 0) //Case of reaching a new fruit with already occupied baskets resets our counter
        { 
            baskets.clear();
            baskets[ fruits[traverse - 1] ] = streak; //Makes sure the values on the right side of the basket we are emptying is saved EX: in 0 1 0 0 2 , we keep the 2 0's but forget the 0 to the left of 1,
                                            // as it is not accessible due to 1 being to the right of it (the rule specified on leetcode is that we must be able to collect a fruit for each index of our path) 
            if(currFruits > maxFruits)
                maxFruits = currFruits;
            currFruits = streak;
            streak = 1;
        }
        if(traverse > 0 && fruits[traverse] == fruits[traverse - 1]) //streak utilized for basket transfer when a new fruit is approached with the baskets already occupied
            streak++;
        else
            streak = 1;
        baskets[fruits[traverse]]++;
        currFruits++;
        traverse++;
        
    }

    if(currFruits > maxFruits)
        maxFruits = currFruits;
    return maxFruits;
}

int main()
{
    //vector<int> test = {0, 1, 2, 2}; //3
    //vector<int> test = {1, 0, 1, 4, 1, 4, 1, 2, 3}; //5
    //vector<int> test = {0, 1, 6, 6, 4, 4, 6}; //5
    vector<int> test {0,0,5,0,0,1,0,4,0,4}; //5
    cout << totalFruit(test);
}

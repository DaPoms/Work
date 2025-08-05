#include <vector>
#include <iostream>
using namespace std;
int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) 
{
    int unplaced{0};
    int difference{0};
    int bI{0}; //Basket index
    for(int i{0}; i < fruits.size(); i++) //fruit index
    {
        while(bI < baskets.size() - 1 && baskets[bI] < fruits[i] ) //Chooses the proper basket (has to have capacity greater or equal to the fruit type's quantity)
            bI++;
        if(baskets[bI] >= fruits[i])
            baskets.erase(baskets.begin() + bI);
        else //Case of fruit not being able to fit in any baskets
            unplaced++;
        bI = 0;
    }   
    return unplaced;
}

int main()
{
    vector<int> testFruits = {5};
    vector<int> testBaskets = {3};
    cout << numOfUnplacedFruits(testFruits, testBaskets); //1 
}

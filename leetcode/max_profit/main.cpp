#include <vector>
#include <limits>
#include <iostream>

using namespace std;
int maxProfit(vector<int>& prices) 
    {
        int currMaxProfit{-1};
        int cheapestPrice = std::numeric_limits<int>::max(); //We have to use max for init value to make sure the cheapest can be set for all values
        int currProfit{-1};
        for(int i{0}; i < prices.size(); i++)
        {
            if(prices[i] < cheapestPrice) //The greatest profit will always be the cheapest price on the left and the higher value sale to the right of it
                cheapestPrice = prices[i];
            currProfit = prices[i] - cheapestPrice;
            if(currProfit > currMaxProfit) //Case of greater profit
                currMaxProfit = currProfit;  
        }
        if(currMaxProfit <= 0)
            return 0;
        return currMaxProfit;    
    }

    int main()
    {
        vector<int> test = {1,5,2,7,3,8};
        cout << maxProfit(test);
    }

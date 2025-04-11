#ifndef STOCK_H
#define STOCK_H

using namespace std;
#include <string>
#include <iostream>
#include <iomanip>
class Stock
{
    private:
        string ticker; //Ticker is just another name for stock symbols, I like ticker more than symbol due to it being less ambiguous 
        int shares; //We assume shares cannot be partial
        double moneySpent; //Total money spent on said stock
    public:
        Stock(string passedTicker = "NULL", int passedShares = -1, double passedMoneySpent = 0.00);
        string getTicker() const;
        void setTicker(string passedTicker);
        int getShares() const;
        void setShares(int passedShares);
        double getMoneySpent();
        void setMoneySpent( double passedMoneySpent);
        friend ostream& operator<<(ostream& os, const Stock& passedStock);
        //Add an average price function
};
#endif

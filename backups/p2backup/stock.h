#ifndef STOCK_H
#define STOCK_H

using namespace std;
#include <string>
#include <iostream>
#include <iomanip>
#include "stockhist.h"
class Stock //Did not do inheritance as a stock HAS a Stock History, but a stock is not a Stock history. (fails the "is a" test), 
            //meaning it would severely limit the modularity of the stock class if I did do inheritance as the 
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
        Stock operator=(StockHist rightHist);
        Stock operator +=(StockHist rightHist);
        friend ostream& operator<<(ostream& os, const Stock& passedStock);
};
#endif

/* 
//string ticker; //Ticker is just another name for stock symbols, I like ticker more than symbol due to it being less ambiguous 
        //int shares; //We assume shares cannot be partial

// string getTicker() const;
// void setTicker(string passedTicker);
// int getShares() const;
//void setShares(int passedShares);
*/

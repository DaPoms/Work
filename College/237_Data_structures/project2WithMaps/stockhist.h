#ifndef STOCKHIST_H
#define STOCKHIST_H
#include <string>
#include <iomanip>

using namespace std;
class StockHist
{
    private:
        int date;
        string ticker;
        char action;
        int shares;
        double price;
    public:
       StockHist(int passedDate = -1, string passedTicker = "NULL", char passedAction = '\0', int passedShares = -1, double passedPrice = 0.00);
       friend ostream& operator<<(ostream& os, const StockHist& myStockHist);

       void setDate(int passedDate);
       int getDate();
       void setTicker(string passedTicker);
       string getTicker();
       void setAction(char passedAction);
       char getAction();
       void setShares(int passedShares);
       int getShares();
       void setPrice(double passedPrice);
       double getPrice();
       

       
};


#endif

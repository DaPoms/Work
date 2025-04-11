#include "stockhist.h"
StockHist::StockHist(int passedDate, string passedTicker, char passedAction, int passedShares, double passedPrice) : date{passedDate}, ticker{passedTicker}, action{passedAction}, shares{passedShares}, price{passedPrice}{}

void StockHist::setDate(int passedDate){date = passedDate;}
int StockHist::getDate() {return date;}
void StockHist::setTicker(string passedTicker) {ticker = passedTicker;}
string StockHist::getTicker() {return ticker;}
void StockHist::setAction(char passedAction) {action = passedAction;}
char StockHist::getAction() {return action;}
void StockHist::setShares(int passedShares) {shares = passedShares;}
int StockHist::getShares() {return shares;}
void StockHist::setPrice(double passedPrice) {price = passedPrice;}
double StockHist::getPrice() {return price;}

ostream& operator<<(ostream& os, const StockHist& myStockHist)
{
    os << left <<  setw(11) << myStockHist.date << setw(10) << myStockHist.ticker << setw(8) << myStockHist.action << 
    setw(10) << myStockHist.shares << fixed << setprecision(2) << myStockHist.price << '\n';
    return os;
}



#include "stock.h"
Stock::Stock(string passedTicker, int passedShares, double passedMoneySpent) : ticker{passedTicker}, shares{passedShares}, moneySpent{passedMoneySpent}{};
string Stock::getTicker() const {return ticker;}
void Stock::setTicker(string passedTicker) {ticker = passedTicker;}
int Stock::getShares() const {return shares;}
void Stock::setShares(int passedShares) {shares = passedShares;}
double Stock::getMoneySpent() {return moneySpent;}
void Stock::setMoneySpent(double passedMoneySpent) {moneySpent = passedMoneySpent;}

Stock Stock::operator= (StockHist rightHist)
{
    ticker = rightHist.getTicker();
    shares = rightHist.getShares();
    moneySpent = shares * rightHist.getPrice();
    return *this;
}

Stock Stock::operator+= (StockHist rightHist)
{
    shares += rightHist.getShares();
    moneySpent += rightHist.getPrice() * rightHist.getShares();
    return *this;
}

ostream& operator<< (ostream& os, const Stock& passedStock)
{
    double spent = passedStock.moneySpent; //Made these because we call them twice in the output, just makes it more readable
    int shares = passedStock.shares;

    double avePrice = spent/shares;
    os << left << setw(10) << passedStock.ticker << left << setw(10) << shares << setw(16) << spent << fixed << setprecision(2) << avePrice << '\n';
    return os;
}

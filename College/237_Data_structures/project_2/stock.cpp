/* 
Author:         Daniel Tripoli                                  
Major:          Computer Science                                 
Creation Date:  April 1st, 2025                       
Due Date:       April 14th, 2025                             
Course:         CSC237 010                                      
Professor Name: Dr.Hussain                              
Project:        #2                                          
Filename:       stock.cpp                                 
Purpose:        Impliments the Stock class, which holds the information pertaining to a stock 
*/
#include "stock.h"

Stock::Stock(string passedTicker, int passedShares, double passedMoneySpent) : ticker{passedTicker}, shares{passedShares}, moneySpent{passedMoneySpent}{}; //Constructor for Stock object
string Stock::getTicker() const {return ticker;}                    //Getter for ticker member variable
void Stock::setTicker(string passedTicker) {ticker = passedTicker;} //Setter for Ticker member variable
int Stock::getShares() const {return shares;}                       //Getter for shares member variable
void Stock::setShares(int passedShares) {shares = passedShares;}    //Setter for shares member variable
double Stock::getMoneySpent() {return moneySpent;}                  //Getter for moneySpent member variable
void Stock::setMoneySpent(double passedMoneySpent) {moneySpent = passedMoneySpent;} //Setter for moneySpent member variable
Stock& Stock::operator+= (StockHist rightHist)                      //Adds elements of a StockHist to a stock Object
{
    shares += rightHist.getShares(); //Adds shares
    moneySpent += rightHist.getPrice() * rightHist.getShares(); //Adds money spent, which is the price * shares of that transaction
    return *this; //Return self for chaining
}

ostream& operator<< (ostream& os, const Stock& passedStock) //Prints the elements of a stock object
{
    double spent = passedStock.moneySpent;                  //Made these because we call them twice in the output, just makes it more readable
    int shares = passedStock.shares;

    double avePrice = spent/shares;
    os << left << setw(10) << passedStock.ticker << left << setw(10) << shares << setw(16) << spent << fixed << setprecision(2) << avePrice << '\n';
    return os;
}

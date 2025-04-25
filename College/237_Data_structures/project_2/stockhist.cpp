/* 
Author:         Daniel Tripoli                                  
Major:          Computer Science                                 
Creation Date:  April 1st, 2025                       
Due Date:       April 14th, 2025                             
Course:         CSC237 010                                      
Professor Name: Dr.Hussain                              
Project:        #2                                          
Filename:       stockhist.cpp                                
Purpose:        Implimentation of the StockHist class, which holds the data pertaining to a stock transaction
*/

#include "stockhist.h"
//StockHist Constructor
StockHist::StockHist(int passedDate, string passedTicker, char passedAction, int passedShares, double passedPrice) : date{passedDate}, ticker{passedTicker}, action{passedAction}, shares{passedShares}, price{passedPrice}{}
void StockHist::setDate(int passedDate){date = passedDate;} //date variable's getter
int StockHist::getDate() {return date;}                     //date variable's setter
void StockHist::setTicker(string passedTicker) {ticker = passedTicker;} //ticker variable's setter
string StockHist::getTicker() {return ticker;}                          //ticker variable's getter
void StockHist::setAction(char passedAction) {action = passedAction;}   //action variable's setter
char StockHist::getAction() {return action;}                            //action variable's getter
void StockHist::setShares(int passedShares) {shares = passedShares;}    //share variable's setter
int StockHist::getShares() {return shares;}                             //share variable's getter
void StockHist::setPrice(double passedPrice) {price = passedPrice;}     //price variable's setter
double StockHist::getPrice() {return price;}                            //price variable's getter

ostream& operator<<(ostream& os, const StockHist& passedStockHist) //Prints the member variables of a StockHist object in a formatted manner
{
    os << left <<  setw(11) << passedStockHist.date << setw(10) << passedStockHist.ticker << setw(8) << passedStockHist.action << 
    setw(10) << passedStockHist.shares << fixed << setprecision(2) << passedStockHist.price << '\n';
    return os;
}



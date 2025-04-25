/* 
Author:         Daniel Tripoli                                  
Major:          Computer Science                                 
Creation Date:  April 1st, 2025                       
Due Date:       April 14th, 2025                             
Course:         CSC237 010                                      
Professor Name: Dr.Hussain                              
Project:        #2                                          
Filename:       stock.h                                 
Purpose:        Declaration of the Stock class, which hold the data pertaining to a stock 
*/

#ifndef STOCK_H
#define STOCK_H

using namespace std;
#include <string>
#include <iostream>
#include <iomanip>
#include "stockhist.h"
class Stock //Did not do inheritance as a stock HAS a Stock History, but a stock is not a Stock history. (fails the "is a" test), 
            //which means changes to StockHist would impact the behavior of the stock class
{
    private:
        string ticker; //Ticker is just another name for stock symbols, I like ticker more than symbol due to it being less ambiguous 
        int shares; //We assume shares cannot be partial
        double moneySpent; //Total money spent on said stock

    public:
        /* 
            Function name:      Stock (constructor)                    
            Description:        The constructor for the Stock class, includes default parameters, 
                                    and allows initializing a Stock object with values
            Parameters:         string passedTicker - The ticker of the stock
                                int passedShares - The shares of the stock
                                double passedMoneySpent - The money spent on the stock        
            Return Value:       None
        */
        Stock(string passedTicker = "NULL", int passedShares = -1, double passedMoneySpent = 0.00);

        /* 
            Function name:      getTicker                   
            Description:        Returns the ticker member variable of the Stock object
            Parameters:         none       
            Return Value:       string
        */
        string getTicker() const;

        /* 
            Function name:      setTicker                   
            Description:        Sets the ticker member variable to the passed ticker for the Stock object
            Parameters:         string passedTicker - The ticker we want to set the member ticker variable to       
            Return Value:       none
        */
        void setTicker(string passedTicker);

        /* 
            Function name:      getShares                   
            Description:        Returns the shares member variable of the Stock object
            Parameters:         none       
            Return Value:       string
        */
        int getShares() const;

        /* 
            Function name:      setShares                   
            Description:        Sets the ticker member variable of the Stock object
            Parameters:         int passedShares - The share value we want to set the shares member variable to       
            Return Value:       none
        */
        void setShares(int passedShares);

        /* 
            Function name:      getMoneySpent                   
            Description:        Returns the moneySpent member variable of the Stock object
            Parameters:         none    
            Return Value:       double - the value of the share member variable
        */
        double getMoneySpent();

        /* 
            Function name:      setMoneySpent                   
            Description:        Sets the moneySpent member variable of the Stock object to the passed double
            Parameters:         double passedMoneySpent - The double we want to set moneySpent to
            Return Value:       none
        */
        void setMoneySpent( double passedMoneySpent);

        /* 
            Function name:      operator+=                  
            Description:        Adds the shares and calculates the moneySpent using the shares 
                                    and price of the StockHist object from the right of the += operator to the Stock object
            Parameters:         StockHist rightHist - the Transaction that we are adding to the Stock object      
            Return Value:       Stock& - The Stock on the left side to allow for chaining (though thats not very important)
        */
        Stock& operator +=(StockHist rightHist);

        /* 
            Function name:      operator<<                  
            Description:        Prints out the elements of a Stock object in a format
            Parameters:         ostream& os - the output stream
                                const Stock& passedStock - The Stock object we are printing the elements of      
            Return Value:       Stock& - The Stock on the left side to allow for chaining (though thats not very important)
        */
        friend ostream& operator<<(ostream& os, const Stock& passedStock);
};
#endif


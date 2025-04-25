/* 
Author:         Daniel Tripoli                                  
Major:          Computer Science                                 
Creation Date:  April 1st, 2025                       
Due Date:       April 14th, 2025                             
Course:         CSC237 010                                      
Professor Name: Dr.Hussain                              
Project:        #2                                          
Filename:       stockhist.h                                 
Purpose:        Declaration of the StockHist class, which holds the data pertaining to a stock transaction
*/

#ifndef STOCKHIST_H
#define STOCKHIST_H
#include <string>
#include <iomanip>

using namespace std;
class StockHist
{
    private:
        string ticker; //Also known as the "symbol" of the stock
        int shares;
        int date; //Date of transaction
        char action; //Whether the transaction was a buy ('B' or 'b') or sell ('S' or 's')
        double price;
    public:
        /* 
            Function name:      StockHist (constructor)                    
            Description:        The constructor for the StockHist class, includes default parameters, 
                                    and allows initializing a StockHist object with values
            Parameters:         int passedDate - The date of the stockHist transaction
                                string passedTicker - The ticker of the stockHist transaction
                                char passedAction - The action of the transaction (B/b for buy, S/s for sell)
                                int passedShares - The shares of the stockHist transaction
                                double passedPrice - The price per share of the stockHist transaction        
            Return Value:       None
        */
       StockHist(int passedDate = -1, string passedTicker = "NULL", char passedAction = '\0', int passedShares = -1, double passedPrice = 0.00);
       
       /* 
            Function name:      operator<<                  
            Description:        Prints out the elements of a StockHist object in a format
            Parameters:         ostream& os - the output stream
                                const StockHist& passedStockHist - The StockHist object we are printing the member variables of      
            Return Value:       StockHist& - The StockHist on the left side to allow for chaining (though thats not very important)
        */
       friend ostream& operator<<(ostream& os, const StockHist& passedStockHist);

       /* 
            Function name:      setDate                 
            Description:        Sets the date member variable to the passed date for the StockHist object
            Parameters:         string passedDate - The date we want to set the member date variable to       
            Return Value:       none
       */
       void setDate(int passedDate);

       /* 
            Function name:      getDate                   
            Description:        Returns the date member variable of the StockHist object
            Parameters:         none       
            Return Value:       int - the date, in number format
       */
       int getDate();

       /* 
            Function name:      setTicker                   
            Description:        Sets the ticker member variable to the passed ticker for the StockHist object
            Parameters:         string passedTicker - The ticker we want to set the member ticker variable to       
            Return Value:       none
       */
       void setTicker(string passedTicker);

       /* 
            Function name:      getTicker                   
            Description:        Returns the ticker member variable of the StockHist object
            Parameters:         none       
            Return Value:       string - The value of the ticker member variable
       */
       string getTicker();

       /* 
            Function name:      setAction                  
            Description:        Sets the action member variable to the passed action for the StockHist object
            Parameters:         char passedAction - The action we want to set the member action variable to       
            Return Value:       none
       */
       void setAction(char passedAction);

       /* 
            Function name:      getAction                 
            Description:        Returns the action member variable of the StockHist object
            Parameters:         none       
            Return Value:       Char - the value of the action member variable
       */
       char getAction();

       /* 
            Function name:      setShares                   
            Description:        Sets the ticker member variable of the StockHist object
            Parameters:         int passedShares - The share value we want to set the shares member variable to       
            Return Value:       none
        */
       void setShares(int passedShares);

       /* 
            Function name:      getShares                   
            Description:        Returns the shares member variable of the StockHist object
            Parameters:         none       
            Return Value:       string - The value of the shares member variable
        */
       int getShares();

       /* 
            Function name:      setPrice                   
            Description:        Sets the price member variable of the StockHist object
            Parameters:         double passedPrice - The price value we want to set the price member variable to        
            Return Value:       none
        */
       void setPrice(double passedPrice);
       /* 
            Function name:      getPrice                   
            Description:        Returns the price member variable of the price object
            Parameters:         none       
            Return Value:       double - The value of the price member variable
        */
       double getPrice();
};


#endif

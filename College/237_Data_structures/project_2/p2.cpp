/* 
Author:         Daniel Tripoli                                  
Major:          Computer Science                                 
Creation Date:  April 1st, 2025                       
Due Date:       April 14th, 2025                             
Course:         CSC237 010                                      
Professor Name: Dr.Hussain                              
Project:        #2                                          
Filename:       p2.cpp                                 
Purpose:        Runner file, organizes stock data
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> //For stringstream, allows catching txt input file errors without actually throwing an error (as all text can be a string)
#include <iomanip>
#include "stock.h"
#include "stockhist.h"
using namespace std;

//PS: Make sure txt file you input does not have open space (INCLUDING at the end of the txt file), I purposefully implimented an error call for that case

/* 
 Function name:     assignToVar                      
 Description:       Reads one element from the passed input string stream, does error checking 
                    to make sure the element is able to be assigned to the passed variable, and assigns it if possible.    
 Parameters:        istringstream& lineReader - The input string stream is read from
                    T& word - The variable we want to assign the element we read from the string stream to
                    const int& lineNum - The line which we got the string stream from
 Return Value:      none
*/
template <typename T>
void assignToVar(istringstream& lineReader, T& word, const int& lineNum) //Helper function for readToStockHist, Does error checking in a more compact way for reading from a line in the txt file

{
    string wordGuard{""}; // A guard to prevent conversion errors, so the file input can be tested on and converted once found to be valid
    if (!(lineReader >> wordGuard)) //Case of nothing being read from stringstream
        throw runtime_error(" ERROR - Missing one or more elements in one or more columns. triggered from line " + to_string(lineNum)  + " of the txt file.\n(PS: This error also flags if you accidentally left an empty line anywhere in the txt file)\n");
     
    if constexpr (is_same<T, string>::value) //Checks if variable we pass through is a string. As far as I know, constexpr in an if statement forces the if statement to compile-time, which allows this to run 
        word = wordGuard;

    else if (is_same<T, char>::value)  //Checks if the type of the variable we passed through can indeed be a char
    {
        if(wordGuard.length() == 1) //Clever way to find if input is a char or not
            word = wordGuard[0];
        else
            throw runtime_error("ERROR - '" +  wordGuard + "' found on line " + to_string(lineNum) + " of the provided txt file is not a char\n"); 
    

        if( (wordGuard[0] != 'b') && (wordGuard[0] != 'B') && (wordGuard[0] != 's') && (wordGuard[0] != 'S') ) //If char is not an accepted value of b B S or s
            throw runtime_error("ERROR - Invalid char of '" + wordGuard + "' in the provided txt file on line " + to_string(lineNum) + ". This input can be 'B', 'b', 'S', or 's' only.\n");
    }

    else //Only two cases left are int and double if this runs
    {
        try
        {
            if(is_same<T, int>::value)
                word = stoi(wordGuard);
            else  //Check if input can be a double
                word = stod(wordGuard);
        }
        catch(invalid_argument) //Error thrown from the stoi() and stod() functions in the case of improper inputs
        {
            throw runtime_error("\nERROR - String: '" + wordGuard + "' found on line " + to_string(lineNum) + " of the provided txt file. Only ints are accepted for this parameter\n");
           
        }
        catch(out_of_range) //Error thrown from the stoi() and stod() functions in the case of exceedingly large inputs
        {
            throw runtime_error("\nERROR - Value: '" + wordGuard + "' on line " + to_string(lineNum) + " of the txt is too large.\n");
            
        }
    }    
}   

/* 
 Function name:     readToStockHist                      
 Description:       Opens a file stream to a passed file name and stores each line in as a separate StockHist object 
                        in the passed vector as long as the given txt file follows the accepted format (int, string, char, int, double). 
 Parameters:        vector<StockHist>& transactions - The vector which we store each stock transaction in
                    string fileName - The name of the file we want to read for input
 Return Value:      none
*/
void readToStockHist(vector<StockHist>& transactions, string fileName) //Reads from a txt at the passed name file of proper stock transaction formatting and stores each transaction in the passed vector
{
    ifstream fileReader{fileName};
    istringstream lineReader{};
    string stringLine{""};
    int lineNum{1}; //For extra error description, this is the current line in the txt being read
    
    int date{-1}; //These 5 variables (below) are all to store the data of a single transaction read from the file
    string ticker{""};
    char action{'\0'};
    int shares{-1};
    double price{-1};
   

    while(getline(fileReader, stringLine)) //Reads each line all the way to the end
    {
        lineReader.str(stringLine);
        assignToVar(lineReader, date, lineNum); //Does error checking and reads one element from the string stream
        assignToVar(lineReader, ticker, lineNum);
        assignToVar(lineReader, action, lineNum);
        assignToVar(lineReader, shares, lineNum);
        assignToVar(lineReader, price, lineNum);
        if(lineReader >> date) //Error catching of having more than 5 elements
          throw runtime_error("ERROR - more than 5 elements given on line " + to_string(lineNum) + " of the rows in the provided txt file\n");
        lineReader.clear(); //string stream must be cleared as it ends when we go out of bounds for each line of text (getline won't work properly when assigning to the out of bounds string stream)
        lineNum++;

        transactions.push_back(StockHist(date, ticker, action, shares, price));
    }  
    

}

/* 
 Function name:     displayTransactions                     
 Description:       Prints out all the StockHist elements of a StockHist vector in a tabular manner
 Parameters:        const vector<StockHist>& transactions - The vector we are printing the contents of    
 Return Value:      none
*/
void displayTransactions(const vector<StockHist>& transactions) //Prints out all StockHist elements in a StockHist vector
{
    cout << "All Transactions:\nDate       Stock    Type    #Shares    Share Price ($)\n-----------------------------------------------------------------------\n";
    for (StockHist transaction: transactions)
        cout << transaction;
    cout << "\n";
}

/* 
 Function name:     displayPortfolio                     
 Description:       Prints out all the Stock elements of a Stock vector in a tabular manner
 Parameters:        vector<Stock> passedPortfolio - The Stock vector we are printing the contents of       
 Return Value:      none
*/
void displayPortfolio(vector<Stock> passedPortfolio) //Prints out all Stock elements in a Stock vector
{
    cout << "Portfolio:\nStock   #Shares   Price Paid ($)  Avg Price ($)\n------------------------------------------------------------------\n";
    for(int i{0}; i < passedPortfolio.size(); i++)
    {
        cout << passedPortfolio[i];
    }
    cout << '\n';
}

/* 
 Function name:     locateInVector                       
 Description:       Attempts to locate a passed ticker in a given vector of Stock objects
 Parameters:        string elem
                    vector<Stock> passedVector      
 Return Value:      int - The index where a stock ticker was found in the passed vector
*/
int locateInVector(string elem, vector<Stock> passedVector) //Attempts to locate a passed ticker in a given vector of Stock objects, returning the index it was found
{
    for(int i{0}; i < passedVector.size(); i++)
        {
            if(passedVector[i].getTicker() == elem) //Compares ticker
                return i;
        }
    return -1;
}

/* 
 Function name:     cancelOutSell                        
 Description:       Searches above the passed index of a sell transaction, cancelling out the sold shares with past buy transactions
 Parameters:        int sellIndex - Index where sell transaction occurs
                    vector<StockHist>& passedTransactions - The vector of StockHist objects where the sell occurs
 Return Value:      double - the price spent on the stocks that were sold
*/
double cancelOutSell(int sellIndex, vector<StockHist>& passedTransactions) //returns the amount of money required to cancel out a single sell transaction,
{                                                                          //assuming the user did not make a sale with a stock they don't own/own yet in the provied txt
    string beingSoldTicker = passedTransactions[sellIndex].getTicker(); //The stock ticker of the sell call
    char action{'\0'};
    double sumSold{0.00};
    int shareDelta = -(passedTransactions[sellIndex].getShares()); //The number of shares we sold, negative. Buying stocks increases shareDelta, making it more positive
    int traverseUp = sellIndex - 1;
    while(traverseUp > -1 && shareDelta < 0) 
    {
        
        if(passedTransactions[traverseUp].getTicker() == beingSoldTicker) //Checks if the transaction is associated to the stock we sold
        {
            
            action = passedTransactions[traverseUp].getAction(); //Stores if transaction is a buy or sell
            if(action == 'B' || action == 'b') //Case of buying
            {
                shareDelta += passedTransactions[traverseUp].getShares();
                if(shareDelta >= 0) //Case of the buy transaction perfectly cancelling out the sell
                {
                    sumSold += ( (passedTransactions[traverseUp].getShares() - shareDelta) * passedTransactions[traverseUp].getPrice()); //Adding the price of the stocks we sold
                    if(shareDelta == 0) //Case of completely selling the stock from a buy transaction
                        passedTransactions[traverseUp].setShares(0); 
                }
        
                else //Case of sell still not being completely balanced out by the buy transaction
                {
                    sumSold += ((passedTransactions[traverseUp].getShares()) * passedTransactions[traverseUp].getPrice()); 
                    passedTransactions[traverseUp].setShares(0); //Stock gets fully sold
                }
            }
        }
        --traverseUp;
    }
    return sumSold;
}

/* 
 Function name:     readToPortfolio                       
 Description:       Reads the passed StockHist vector and stores it as a vector of Stocks,
                        each Stock holds the stock name, share count, and the total money spent on that specific stock, which accounts for stocks sold
 Parameters:        vector<Stock>& passedPortfolio - The Stock vector we want to add Stock elements to
                    vector<StockHist> passedTransactions - the StockHist vector we want to read the transactions of to fill the Portfolio
 Return Value:      none
*/
void readToPortfolio(vector<Stock>& passedPortfolio, vector<StockHist> passedTransactions) //Reads a vector of StockHist's and adds the stocks to the passed Stock vector with the 
                                                                                           //total shares and money spent calculated 
{    
    int located{-1};
    char action{'\0'};
    for(int tIndex{0}; tIndex < passedTransactions.size(); tIndex++)
    {
        located = locateInVector(passedTransactions[tIndex].getTicker(), passedPortfolio); // Returns index of stock in the porfolio, or -1 if it doesn't exist yet

            if(located != -1) // Case of being an already bought stock
            {
                action = passedTransactions[tIndex].getAction();

                if(action  == 'B' || action == 'b') //Case of buying more stock
                {
                    passedPortfolio[located] += passedTransactions[tIndex];
                }
                else // Case of sell -- Proven it can only be S or s as reading to Transaction throws errors when action is not B, b or S, s
                {
                    passedPortfolio[located].setShares( passedPortfolio[located].getShares() - passedTransactions[tIndex].getShares() );
                    
                    passedPortfolio[located].setMoneySpent( passedPortfolio[located].getMoneySpent() - cancelOutSell(tIndex, passedTransactions) ); // cancelOutSell directly changes values in the transaction
                                                                                                                                                    // vector to account for past sales/sold stock 
                                                                                
                }
            }

            else // Case of new element, we assume it's a buy and that the user didn't accidentally sell a nonexistent stock
                passedPortfolio.push_back(Stock(passedTransactions[tIndex].getTicker(), passedTransactions[tIndex].getShares(), passedTransactions[tIndex].getPrice() * passedTransactions[tIndex].getShares()));
    } 
}

/* 
 Function name:     countBuys                    
 Description:       Counts the number of StockHist items that are buy transactions
 Parameters:        string passedTicker - The name of the stock we are counting the buys of
                    vector<StockHist>& passedTransactions - The StockHist vector we want to count the buys of 
 Return Value:      int - the number of buy transactions found of that specific stock
*/
int countBuys(string passedTicker, vector<StockHist>& passedTransactions) // Counts the number of buys in a vector of transactions for a given stock, tells us when we have reached the end
{
    int end = passedTransactions.size() - 1;
    int buyCount{0};
    char transactionAction{'\0'};
    for(int traverseT{end}; traverseT > -1; traverseT--)
        {
            if(passedTransactions[traverseT].getTicker() == passedTicker) // Case of transaction being associated with ticker we are tracking
            {
                transactionAction = passedTransactions[traverseT].getAction(); 
                if(transactionAction == 'B' || transactionAction == 'b')
                    buyCount++; 
            }
        }

    return buyCount;
}

/* 
 Function name:     displayAdvisoryTable                        
 Description:       Prints in a tabular format the most recent unsold stock transaction of each 
                        stock found in the passed StockHist vector. The only case where partially
                        sold stock is displayed is if the last buy is partially sold, and that partial amount is printed.
 Parameters:        vector<StockHist>& passedTransactions - The StockHist vector we traverse to find the 1st unsold stock of 
                    vector<Stock>& passedPortfolio - The Stock vector we use to know which stocks we are looking for
 Return Value:      none
*/
void displayAdvisoryTable(vector<StockHist>& passedTransactions, vector<Stock>& passedPortfolio) //Idea: start from bottom, subtract = adds to debt, buy = takes away from debt. Print sale that is one after debt
{
    int end;
    int shareDelta{0};
    char transactionAction{'\0'};
    int transactionShares;
    int sellCount{0}; //The count of sell transactions we have seen so far
    int buyCount{0}; //The count of buy transactions we have seen so far
    int buyTotal{0}; //The total amount of buy transactions we can come across for that particular stock
    int consecutivePosDelta{0}; //Accounts for case when shareDelta only partially sells a buy, so you print the next buy if the next transaction is a buy

    cout << "Advisory Table (Latest Unsettled Stock):\nStock     Date       #Unsold Shares    Share Price\n------------------------------------------------------------------\n";
    for(int tickerIndex{0}; tickerIndex < passedPortfolio.size(); tickerIndex++) //Ticker that we are hunting for
    {
        end = passedTransactions.size() - 1;
        for(int traverseT{end}; traverseT > -1; traverseT--) //We traverse from the end up 
        {
            
            if(passedTransactions[traverseT].getTicker() == passedPortfolio[tickerIndex].getTicker()) //Case of transaction being associated with ticker we are tracking
            {
                
                transactionAction = passedTransactions[traverseT].getAction();
                transactionShares = passedTransactions[traverseT].getShares();
                

                if(transactionAction == 'B' || transactionAction == 'b') //If a buy transaction
                {
                    

                    if(sellCount == 0) //If there are not prior sells, then it belongs on the advisory board
                    {
                        cout << setw(10) << passedTransactions[traverseT].getTicker() << setw(11) << passedTransactions[traverseT].getDate() << setw(18) << transactionShares << fixed << setprecision(2) << passedTransactions[traverseT].getPrice() << '\n';
                        break;
                    }

                    else //The count of shareDelta becomes more positive, by the amount of shares in this buy transaction
                    {
                        buyCount++;
                        shareDelta += transactionShares;
                    }
                }

                else //Case of selling, shareDelta gets more negative
                {
                    shareDelta -= transactionShares;
                    sellCount++;
                }
                
                if(shareDelta >= 0) //Case of if we no longer owe shares for the given stock
                {
                    consecutivePosDelta++;
                    buyTotal = countBuys(passedTransactions[traverseT].getTicker(), passedTransactions); //Tracks the "end" of transactions for that particular stock 

                     if(buyTotal == buyCount)//Case of having no more buy transactions to offset deltaShares, so we print the difference we have left
                     {
                         transactionShares = transactionShares - (transactionShares - shareDelta); //We subtract whatever is left in delta if we are at the end of buys (might need to make mechanism for this)                    
                         cout << setw(10) << passedTransactions[traverseT].getTicker() << setw(11) << passedTransactions[traverseT].getDate() << setw(18) << transactionShares << fixed << setprecision(2) << passedTransactions[traverseT].getPrice() << '\n';
                     }

                     else if(consecutivePosDelta == 2) //Prevents partially sold stocks from being printed, as only the last or unsold transactions are allowed on the advisory table
                     {
                        cout << setw(10) << passedTransactions[traverseT].getTicker() << setw(11) << passedTransactions[traverseT].getDate() << setw(18) << transactionShares << fixed << setprecision(2) << passedTransactions[traverseT].getPrice() << '\n';
                        break;
                    }
                 
                }
                else    
                    consecutivePosDelta = 0;             
            }
        }
        
        consecutivePosDelta = 0; //These all reset for each stock
        buyCount = 0;
        sellCount = 0;
        shareDelta = 0;
        
    }
    cout << '\n';
}

int main() //impliment everything outside of main
{    
    vector<StockHist> transactions;
    readToStockHist(transactions, "transactions.txt");
    displayTransactions(transactions);

    vector<Stock>portfolio{};
    readToPortfolio(portfolio, transactions);
    displayPortfolio(portfolio);

    displayAdvisoryTable(transactions, portfolio);
}

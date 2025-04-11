#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> //For stringstream, allows catching txt input file errors without actually throwing an error
//#include <cassert>
#include <map>
#include "stock.h"
#include "stockhist.h"
using namespace std;

template <typename T>
void assignToVar(istringstream& lineReader, T& word, const int& lineNum) //Helper function for readToStockHist, Does error checking in a more compact way for reading from a line in the txt file
{
    string wordGuard{""}; //A guard to prevent conversion errors, so the file input can be tested on and converted once found to be valid
    if(!(lineReader >> wordGuard))
    {
        throw runtime_error(" ERROR - Missing one or more elements in one or more columns. triggered from line " + to_string(lineNum)  + " of the txt file.\n");
        //return;
    }    

    if constexpr(is_same<T, string>::value) //GO TO GRADUATES OFFICE AND ASK FOR THIS HUREHIGERHUOGEHRIUGERHUGERHGEUE   As far as I know, constexpr if statement forces if statement to compile-time 
        word = wordGuard;

    else if(is_same<T, char>::value) //NEED TO FIX FOR CASE OF NUMBER IN CHAR FIELD
    {
        if(wordGuard.length() == 1) //Clever way to find if input is a char or not
            word = wordGuard[0];
        else
        {
            throw runtime_error("ERROR - '" +  wordGuard + "' found on line " + to_string(lineNum) + " of the provided txt file is not a char\n"); 
            //return;
        }

        if( (wordGuard[0] != 'b') && (wordGuard[0] != 'B') && (wordGuard[0] != 's') && (wordGuard[0] != 'S') )
            throw runtime_error("ERROR - Invalid char of '" + wordGuard + "' in the provided txt file on line " + to_string(lineNum) + ". This input can be 'B', 'b', 'S', or 's' only.\n");
    }

    else
    {
        try
        {
            if(is_same<T, int>::value)
                word = stoi(wordGuard);
            else 
                word = stod(wordGuard);
        }
        catch(invalid_argument)
        {
            throw runtime_error("\nERROR - String: '" + wordGuard + "' found on line " + to_string(lineNum) + " of the provided txt file. Only ints are accepted for this parameter\n");
            //return;
        }
        catch(out_of_range)
        {
            throw runtime_error("\nERROR - Value: '" + wordGuard + "' on line " + to_string(lineNum) + " of the txt is too large.\n");
            //return;
        }
    }    
}   

void readToStockHist(vector<StockHist>& transactions, string fileName)
{
    ifstream fileReader{fileName};
    istringstream lineReader{};
    string stringLine{""};
    StockHist newHist;
    int date{-1};
    string ticker{""};
    char action{'\0'};
    int shares{-1};
    double price{-1};
    int lineNum{1};
    while(getline(fileReader, stringLine))
    {
        lineReader.str(stringLine);
        assignToVar(lineReader, date, lineNum);
        assignToVar(lineReader, ticker, lineNum);
        assignToVar(lineReader, action, lineNum);
        assignToVar(lineReader, shares, lineNum);
        assignToVar(lineReader, price, lineNum);
        if(lineReader >> date) //Error case of having more than 5 elements
            throw runtime_error("ERROR - more than 5 elements given on line " + to_string(lineNum) + " of the rows in the provided txt file\n");
        lineReader.clear();
        lineNum++;

        transactions.push_back(StockHist(date, ticker, action, shares, price));
    }  
    

}

void displayTransactions(const vector<StockHist>& transactions)
{
    cout << "Date       Stock    Type    #Shares    Share Price ($)\n-----------------------------------------------------------------------\n";
    //int end = transactions.size();
    //for(int i{0}; i < end; i++)
    for (StockHist transaction: transactions)
        cout << transaction;
}

void displayPortfolio(const map<string, Stock>& passedPortfolio)
{
    for(pair<string, Stock> oneStock: passedPortfolio)
    {
        cout << oneStock.second;
    
    }
}

void readToPortfolio(map<string,Stock>& passedPortfolio, vector<StockHist> passedTransactions) 
{
    string transactionTicker;
    int transactionShares;
    char transactionAction;
    int portfolioShares;
    double portfolioSpent;
    double transactionSpent;
    Stock stockToBeAdded;

    
    for(StockHist transaction : passedTransactions)
    {
        transactionTicker = transaction.getTicker();
        transactionShares = transaction.getShares();
        transactionAction = transaction.getAction(); //Whether stock was bought or sold
        //portfolioShares = passedPortfolio[transactionTicker].getShares();
        //portfolioSpent = passedPortfolio[transactionTicker].getMoneySpent();
        transactionSpent = transaction.getPrice() * transactionShares;
        
       cout << "--------\n" << transactionSpent << "------\n";
        if(passedPortfolio.find(transactionTicker) != passedPortfolio.end()) //Case of already in the map
        {
            portfolioShares = passedPortfolio[transactionTicker].getShares();
            portfolioSpent = passedPortfolio[transactionTicker].getMoneySpent();

            if(transactionAction == 'B' || transactionAction == 'b') 
            {
                passedPortfolio[transactionTicker].setMoneySpent(portfolioSpent + transactionSpent);
                passedPortfolio[transactionTicker].setShares(portfolioShares + transactionShares);
            }
            else
            {
                passedPortfolio[transactionTicker].setShares(portfolioShares - transactionShares);
                passedPortfolio[transactionTicker].setMoneySpent(portfolioSpent - transactionSpent);
            }
        }
        else
            passedPortfolio[transactionTicker] = Stock(transactionTicker, transactionShares, transactionSpent);
        
    } 

}



//impliment reading from file function
//Impliment advisory board
//Impliment output for table of stocks
int main() //impliment everything outside of main
{
    //string passed{""};
    //cout << "Enter file name: ";
    //cin >> passed;
    
    vector<StockHist> transactions;
    readToStockHist(transactions, "t.txt");
    displayTransactions(transactions);

    map<string, Stock> portfolio{};
    readToPortfolio(portfolio, transactions);
    displayPortfolio(portfolio);

}
//Impliment stock hist object that store all functions
//DO WE NEED TO PRINT IN ORDER FROM SHOWING UP?
//<< "Date       Stock    Type    #Shares    Share Price ($)\n" << sHist;
    //cout << "Stock     #Shares   Price Paid ($)  Avg Price ($)\n";

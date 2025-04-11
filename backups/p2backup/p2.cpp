#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> //For stringstream, allows catching txt input file errors without actually throwing an error
#include <iomanip>
#include "stock.h"
#include "stockhist.h"
using namespace std;

template <typename T>
void assignToVar(istringstream& lineReader, T& word, const int& lineNum) //Helper function for readToStockHist, Does error checking in a more compact way for reading from a line in the txt file
//Make sure txt file does not have open space (especially at te end of the txt file)
{
    string wordGuard{""}; //A guard to prevent conversion errors, so the file input can be tested on and converted once found to be valid
    if(!(lineReader >> wordGuard))
        throw runtime_error(" ERROR - Missing one or more elements in one or more columns. triggered from line " + to_string(lineNum)  + " of the txt file.\n(PS: This error also flags if you accidentally left an empty line anywhere in the txt file)\n");
     

    if constexpr(is_same<T, string>::value) //GO TO GRADUATES OFFICE AND ASK FOR THIS HUREHIGERHUOGEHRIUGERHUGERHGEUE   As far as I know, constexpr if statement forces if statement to compile-time 
        word = wordGuard;

    else if(is_same<T, char>::value) //NEED TO FIX FOR CASE OF NUMBER IN CHAR FIELD
    {
        if(wordGuard.length() == 1) //Clever way to find if input is a char or not
            word = wordGuard[0];
        else
            throw runtime_error("ERROR - '" +  wordGuard + "' found on line " + to_string(lineNum) + " of the provided txt file is not a char\n"); 
    

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
           
        }
        catch(out_of_range)
        {
            throw runtime_error("\nERROR - Value: '" + wordGuard + "' on line " + to_string(lineNum) + " of the txt is too large.\n");
            
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
        //if(lineReader)
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
    cout << "All Transactions:\nDate       Stock    Type    #Shares    Share Price ($)\n-----------------------------------------------------------------------\n";
    for (StockHist transaction: transactions)
        cout << transaction;
    cout << "\n";
}

void displayPortfolio(vector<Stock> passedPortfolio)
{
    cout << "Portfolio:\nStock   #Shares   Price Paid ($)  Avg Price ($)\n------------------------------------------------------------------\n";
    for(int i{0}; i < passedPortfolio.size(); i++)
    {
        cout << passedPortfolio[i];
    }
    cout << '\n';
}

int locateInVector(string elem, vector<Stock> passedVector)
{
    for(int i{0}; i < passedVector.size(); i++)
        {
            if(passedVector[i].getTicker() == elem)
                return i;
        }
    return -1;
}


double cancelOutSell(int sellIndex, vector<StockHist>& passedTransactions) //returns the amount of money required to cancel out sell.
{ //Assuming user did not make a sale with a stock they don't own/own yet in the provied txt
    string beingSoldTicker = passedTransactions[sellIndex].getTicker();
    char action{'\0'};
    double sumSold{0.00};
    int shareDelta = -(passedTransactions[sellIndex].getShares());
    int traverseUp = sellIndex - 1;
    //for(int buyIndex{sellIndex - 1}; buyIndex > -1; buyIndex--) //Go upwards the list
    while(traverseUp > -1 && shareDelta < 0)
    {
        
        if(passedTransactions[traverseUp].getTicker() == beingSoldTicker) //Look into cases of 2 sale transactions together
        {
            
            action = passedTransactions[traverseUp].getAction();
            if(action == 'B' || action == 'b')
            {
                shareDelta += passedTransactions[traverseUp].getShares();
                if(shareDelta == 0) //Case of perfectly selling
                {
                    sumSold += (passedTransactions[traverseUp].getShares() * passedTransactions[traverseUp].getPrice()); 
                    passedTransactions[traverseUp].setShares(0); //new addons
                    /* if(beingSoldTicker == "IONQ")
                        cout  << sellIndex << " " <<  traverseUp + 1 << " Case == 0 " << shareDelta << " " << sumSold << '\n'; */
                }
                else if(shareDelta > 0) //Case of surplus
                {
                    sumSold += ( (passedTransactions[traverseUp].getShares() - shareDelta) * passedTransactions[traverseUp].getPrice()); //Issue: selling all the shares in all cases, not partial
                    passedTransactions[traverseUp].setShares(passedTransactions[traverseUp].getShares() - shareDelta); //new addons
                    /* if(beingSoldTicker == "IONQ")
                        cout << sellIndex << " " << traverseUp + 1 << " Case > 0 " <<  shareDelta << " " << sumSold << '\n'; */
                }
                else //Case of under
                {
                    

                    sumSold += ((passedTransactions[traverseUp].getShares()) * passedTransactions[traverseUp].getPrice()); //Issue: selling all the shares in all cases, not partial
                    passedTransactions[traverseUp].setShares(0); //new addons
                }
                //cout << "M " <<  passedTransactions[2].getShares() << " M\n";





                /* if(shareDelta + passedTransactions[traverseUp].getShares() == 0)
                {
                    shareDelta += passedTransactions[traverseUp].getShares();
                    sumSold += (passedTransactions[traverseUp].getShares() * passedTransactions[traverseUp].getPrice()); 
                }
                else if(shareDelta + passedTransactions[traverseUp].getShares() > 0) //Case of surplus
                {
                    shareDelta += passedTransactions[traverseUp].getShares();
                    sumSold += ((passedTransactions[traverseUp].getShares() - shareDelta) * passedTransactions[traverseUp].getPrice()); //Issue: selling all the shares in all cases, not partial
                }
                else
                {
                    shareDelta += passedTransactions[traverseUp].getShares();
                    sumSold += ((passedTransactions[traverseUp].getShares()) * passedTransactions[traverseUp].getPrice()); //Issue: selling all the shares in all cases, not partial
                }
 */
            }
        }
        --traverseUp;
    }
    return sumSold;
}
void readToPortfolio(vector<Stock>& passedPortfolio, vector<StockHist> passedTransactions) //NEED TO FIX:
/* 
    Make similar system to advisory table, if sell order is exceedingly large, traverse upwards, adding price paid by shares * share price till you run out of by shares
*/
 
{    
    //vector<StockHist> beforeSell = passedTransactions;
    int located{-1};
    char action{'\0'};
    //map<string, double> recentBuyPrice; //To store recent prices
    for(int tIndex{0}; tIndex < passedTransactions.size(); tIndex++)
    {
        located = locateInVector(passedTransactions[tIndex].getTicker(), passedPortfolio);

            if(located != -1) //Case of being an already bought stock
            {
                action = passedTransactions[tIndex].getAction();

                if(action  == 'B' || action == 'b')
                {
                    passedPortfolio[located] += passedTransactions[tIndex];
                }
                else //Proven it can only be S as reading to Transaction throws errors when action is not B or S
                {
                    passedPortfolio[located].setShares( passedPortfolio[located].getShares() - passedTransactions[tIndex].getShares() );
                    passedPortfolio[located].setMoneySpent( passedPortfolio[located].getMoneySpent() - cancelOutSell(tIndex, passedTransactions) );
                }
            }

            else //Case of new element, we assume it's a buy and that the user didn't accidentally sell a nonexistent stock
                passedPortfolio.push_back(Stock(passedTransactions[tIndex].getTicker(), passedTransactions[tIndex].getShares(), passedTransactions[tIndex].getPrice() * passedTransactions[tIndex].getShares()));
    } 
    //passedTransactions = beforeSell;
}

int countBuys(string passedTicker, vector<StockHist>& passedTransactions) //Counts the number of buys in a vector of transactions for a given stock, tells us when we have reached the end
{
    int end = passedTransactions.size() - 1;
    int buyCount{0};
    char transactionAction{'\0'};
    for(int traverseT{end}; traverseT > -1; traverseT--)
        {
            if(passedTransactions[traverseT].getTicker() == passedTicker) //Case of transaction being associated with ticker we are tracking
            {
                transactionAction = passedTransactions[traverseT].getAction(); 
                if(transactionAction == 'B' || transactionAction == 'b')
                    buyCount++; 
            }
        }

    return buyCount;
}


void displayAdvisoryTable(vector<StockHist>& passedTransactions, vector<Stock>& passedPortfolio) //Idea: start from bottom, subtract = adds to debt, buy = takes away from debt. Print sale that is one after debt
{
    int end;
    int shareDelta{0};
    char transactionAction{'\0'};
    int sellCount{0};
    int transactionShares;
    int buyCount{0};
    int buyTotal{0};
    int consecutivePosDelta{0}; //NEED TO TEST THIS VAR, case when you buy midway through, but delta only partially sells the buy, so you print the next buy

    cout << "Advisory Table (Latest Unsettled Stock):\nStock     Date       #Unsold Shares    Share Price\n------------------------------------------------------------------\n";
    for(int tickerIndex{0}; tickerIndex < passedPortfolio.size(); tickerIndex++) //Ticker that we are hunting for
    {
        end = passedTransactions.size() - 1;
        for(int traverseT{end}; traverseT > -1; traverseT--)
        {
            
            if(passedTransactions[traverseT].getTicker() == passedPortfolio[tickerIndex].getTicker()) //Case of transaction being associated with ticker we are tracking
            {
                
                transactionAction = passedTransactions[traverseT].getAction();
                transactionShares = passedTransactions[traverseT].getShares();
                

                if(transactionAction == 'B' || transactionAction == 'b')
                {
                    

                    if(sellCount == 0)
                    {
                        cout << setw(10) << passedTransactions[traverseT].getTicker() << setw(11) << passedTransactions[traverseT].getDate() << setw(18) << transactionShares << fixed << setprecision(2) << passedTransactions[traverseT].getPrice() << '\n';
                        break;
                    }

                    else
                    {
                        buyCount++;
                        shareDelta += transactionShares;
                    }
                }

                else //Case of selling
                {
                    shareDelta -= transactionShares;
                    sellCount++;
                }
                
                if(shareDelta >= 0)  //Test case when shareDelta == 0
                {
                    consecutivePosDelta++;
                    buyTotal = countBuys(passedTransactions[traverseT].getTicker(), passedTransactions);

                     if(buyTotal == buyCount)//If buyCount == buyTotal, it means we have no more ways to remove deltaShares, so we print the difference
                     {
                         transactionShares = transactionShares - (transactionShares - shareDelta); //We subtract whatever is left in delta if we are at the end of buys (might need to make mechanism for this)                    
                         cout << setw(10) << passedTransactions[traverseT].getTicker() << setw(11) << passedTransactions[traverseT].getDate() << setw(18) << transactionShares << fixed << setprecision(2) << passedTransactions[traverseT].getPrice() << '\n';
                     }

                     else if(consecutivePosDelta == 2) //For not printing partially solds
                     {
                        cout << setw(10) << passedTransactions[traverseT].getTicker() << setw(11) << passedTransactions[traverseT].getDate() << setw(18) << transactionShares << fixed << setprecision(2) << passedTransactions[traverseT].getPrice() << '\n';
                        break;
                    }
                 
                }
                else    
                    consecutivePosDelta = 0;             
            }
        }
        
        consecutivePosDelta = 0;
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

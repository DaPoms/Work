#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> //For stringstream, allows catching txt input file errors without actually throwing an error
#include "stock.h"
#include "stockhist.h"
using namespace std;

template <typename T>
void assignToVar(istringstream& lineReader, T& word, const int& lineNum) //Helper function for readToStockHist, Does error checking in a more compact way for reading from a line in the txt file
{
    
        
    
    string wordGuard{""}; //A guard to prevent conversion errors, so the file input can be tested on and converted once found to be valid
    if(!(lineReader >> wordGuard))
    {
        cerr << " ERROR - Missing one or more elements in one or more columns. triggered from line " << lineNum << " of the txt file.\n";
        return;
    }
    
    
    //cout << is_same<T, string>::value << "\n";
    
    if constexpr(is_same<T, string>::value) //GO TO GRADUATES OFFICE AND ASK FOR THIS HUREHIGERHUOGEHRIUGERHUGERHGEUE   As far as I know, constexpr if statement forces if statement to compile-time 
        word = wordGuard;

    if (!(is_same<T, string>::value) && !(is_same<T, char>::value))
    {
        try
        {
            stoi(wordGuard);
        }
        catch(invalid_argument)
        {
            cerr << "\nERROR - String: '" << wordGuard << "' found on line " << lineNum << " of the provided txt file. Only ints are accepted for this parameter\n";
            return;
        }
        catch(out_of_range)
        {
            cerr << "\nERROR - Value: " << wordGuard << " on line " << lineNum << " of the txt is too large.\n";
            return;
        }
        word = stoi(wordGuard); //Implicit conversion
    }    

    else if(is_same<T, char>::value) //NEED TO FIX FOR CASE OF NUMBER IN CHAR FIELD
    {
        if(wordGuard.length() == 1) //Clever way to find if input is a char or not
            word = wordGuard[0];
        else
        {
            cerr << "ERROR - " << wordGuard << " found on line " << lineNum << " of the provided txt file is not a char\n"; 
            return;
        }

        if( (wordGuard[0] != 'b') && (wordGuard[0] != 'B') && (wordGuard[0] != 's') && (wordGuard[0] != 'S') )
          cerr << "ERROR - Invalid char of '" << word << "' in the provided txt file on line " << lineNum << ". This input can be 'B', 'b', 'S', or 's' only.\n";
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
            cerr << "ERROR - more than 5 elements given on line " << lineNum << " of the rows in the provided txt file";
        lineReader.clear();
        lineNum++;

        transactions.push_back(StockHist(date, ticker, action, shares, price));
    }  
    

}

void displayTransactions(const vector<StockHist> transactions)
{
    int end = transactions.size();

    for(int i{0}; i < end; i++)
        cout << transactions[i];
}



//impliment reading from file function
//Impliment advisory board
//Impliment output for table of stocks
int main() //impliment everything outside of main
{
    string passed{""};
    cout << "Enter file name: ";
    cin >> passed;
    
    vector<StockHist> transactions;
    readToStockHist(transactions, passed);
    displayTransactions(transactions);
    

}
//Impliment stock hist object that store all functions
//DO WE NEED TO PRINT IN ORDER FROM SHOWING UP?
//<< "Date       Stock    Type    #Shares    Share Price ($)\n" << sHist;
    //cout << "Stock     #Shares   Price Paid ($)  Avg Price ($)\n";

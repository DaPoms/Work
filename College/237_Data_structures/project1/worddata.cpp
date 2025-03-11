/* 
Author:         Daniel Tripoli                                  
Major:          Computer Science                                 
Creation Date:  March 7th, 2025                       
Due Date:       March 12th, 2025                             
Course:         CSC237 010                                      
Professor Name: Dr.Hussain                              
Project:        #1                                          
Filename:       worddata.cpp                              
Purpose:        Impliments the WordData class, which is designed to store an int and string,
                corresponding to the frequency of the word and a word found in a txt file respectively
*/

#include "worddata.h"
#include <iomanip>
using namespace std;

WordData::WordData(string passedWord, int passedCount) : word{passedWord}, count{passedCount}{} //Constructor for WordData objects
string WordData::getWord() const {return word;}                 // Returns word member variable from WordData object
int WordData::getCount() const {return count;}                  // Returns count member variable from WordData object  
void WordData::setWord(string passedWord){word = passedWord;}   // Sets the word member variable from WordData to the passed string
void WordData::setCount(int passedCount){count = passedCount;}  // Sets the count member variable from WordData to the passed int
void WordData::setWordData(string passedWord , int passedCount) // Sets both the word and count member variable from WordData to the passed string and int respectively
{
    word = passedWord;
    count = passedCount;
}

WordData WordData::operator++(int) //Increments the count member variable of a WordData by 1
{
    count++;
    return *this;
}

ostream &operator<<(ostream &output, const WordData &data) //Prints out the member variables of a WordData object in a tabular format
{
    cout << data.getWord() << setw(21 - data.getWord().size()) << data.getCount();

    return output;
}





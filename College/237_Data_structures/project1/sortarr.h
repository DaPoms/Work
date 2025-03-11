/* 
Author:         Daniel Tripoli                                  
Major:          Computer Science                                 
Creation Date:  March 7th, 2025                       
Due Date:       March 12th, 2025                             
Course:         CSC237 010                                      
Professor Name: Dr.Hussain                              
Project:        #1                                          
Filename:       sortarr.h                                   
Purpose:        Declares the SortArr class, which is designed to create a sorted
                    array of WordData objects
*/

#ifndef SORTARR_H
#define SORTARR_H
using namespace std; 
#include "worddata.h" 
class SortArr : public Scoreboard
{
    private:
        WordData arr[10];      // Array of WordData objects
        
    public:

/* 
 Function name:   SortArr         
 Description:     Constructor for SortArr objects, by default, has a capacity of 10 (though it doesn't change much).
 Parameters:      capacity - the capacity of the array (not the used to instantiate the size of the array, only used for functions that need to know the size of the array)      
 Return Value:    none 
*/
        SortArr(int cap = 10);                   // Creates a SortArr object which is a sccoreboard but with a WordData array
/* 
 Function name:   get_entry                     
 Description:     returns WordData object at a given index of the arr member variable array
 Parameters:      int i - the index of the WordData we want to get      
 Return Value:    const WordData& - A WordData object taht cannot be altered, only viewed 
*/
        const WordData& get_entry(int i) const; 
/* 
 Function name:   add                   
 Description:     Creates a WordData object based on the parameters count and word and puts it where it belongs based on the frequency of the WordData object 
 Parameters:      int count - the count of the WordData we are creating and then adding to the SortArr
                  const string& word - the "word" member variable of the WordData we are creating and then adding to the SortArr      
 Return Value:    none 
*/
        void add(int count, const string& word);

};

#endif

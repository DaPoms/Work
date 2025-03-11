/* 
Author:         Daniel Tripoli                                  
Major:          Computer Science                                 
Creation Date:  March 7th, 2025                       
Due Date:       March 12th, 2025                             
Course:         CSC237 010                                      
Professor Name: Dr.Hussain                              
Project:        #1                                          
Filename:       sortarr.cpp                                   
Purpose:        impliments sortarr.h functions, which is designed to make a 
                    sorted WordData array
*/

#include <string>
#include "scoreboard.h"
#include "sortarr.h"
using namespace std;

SortArr::SortArr(int cap) : Scoreboard(cap){}                       // Creates a SortArr object which is a sccoreboard but with a WordData array
const WordData& SortArr::get_entry(int i) const { return arr[i]; }  // returns the WordData object at the passed index;
void SortArr::add(int count, const string& word) { //adds the passed element in order by count into SortArr by creating a WordData object out of the parameters
    // is the new entry a really a high count?
    if (num_entries < capacity || count > arr[num_entries - 1].getCount()) {
        if (num_entries < capacity)            // no count drops from the arr
            num_entries++;                     // so overall number increases

        // shift any lower scores rightward to make room for the new entry
        int j = num_entries - 1;               // index where last entry should be
        while (j > 0 && arr[j - 1].getCount() < count) {
            arr[j] = arr[j - 1];               // shift entry from j-1 to j
            j--;                               // and decrement j
        }
        arr[j] = WordData(word, count);        // when done, add new entry
    }
}


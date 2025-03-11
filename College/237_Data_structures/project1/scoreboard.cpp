/*	File:			scoreboard.cpp
	Last Modified:	18-Feb-25
	Purpose:		Implements the scoreboard for a video game
					The main function is to be written by the students to demonstrate:
						1. addition of random game entries to the scoreboard
						2. removal of game entries from the scoreboard
	Source:			Code Fragments 5.1.1 and 5.1.2 in the zyBook Text
	Simplifications:
		1. Scoreboard is defined as a static array of game entries
		2. Array size is fixed, 10 elements, where each element is a game entry object.
	To Compile:		g++ scoreboard.cpp
*/
/*
*/
#include <iostream>
#include <string>
#include "scoreboard.h"
using namespace std ;
                                                                  
GameEntry::GameEntry(const string& n, int s) : name{n}, score{s} {}	// Constructs a game entry with the given arguments
    const string& GameEntry::get_name() const { return name; }						// Returns the user's name
    int GameEntry::get_score() const { return score; }								// Returns the user's score  

// Class for storing high scores ordered within an array
// Write comments for the following class 

Scoreboard::Scoreboard(int cap) : capacity{cap} {} ;		// Constructs an empty scoreboard with the given capacity for storing entries
int Scoreboard::get_capacity() const { return capacity; }		// Returns the capacity of the scoreboard
int Scoreboard::get_num_entries() const { return num_entries; }	// Returns the number of current entries stored
const GameEntry& Scoreboard::get_entry(int i) const { return board[i]; }	// Returns a reference to the entry at index i

// Attempts to add a new score to the scoreboard (if it is high enough)
void Scoreboard::add(int score, const string& name) {
    // is the new entry e really a high score?
    if (num_entries < capacity || score > board[num_entries - 1].get_score()) {
        if (num_entries < capacity)            // no score drops from the board
            num_entries++;                     // so overall number increases

        // shift any lower scores rightward to make room for the new entry
        int j = num_entries - 1;               // index where last entry should be
        while (j > 0 && board[j - 1].get_score() < score) {
            board[j] = board[j - 1];           // shift entry from j-1 to j
            j--;                               // and decrement j
        }
        board[j] = GameEntry(name, score);     // when done, add new entry
    }
}

// Removes and returns the scoreboard entry at index i
GameEntry Scoreboard::remove(int i) 
{
    if (i < 0 || i >= num_entries) {
            cout << "Error - Invalid Index: " << i << " (Number of entries = " << num_entries << ")" << endl ;
            exit (1) ;
    }
    else {
    GameEntry temp{board[i]};                  // save the entry to be removed

    // shift entries to the right of the removed one to the left
    for (int j = i; j < num_entries - 1; j++)  // count up from i
        board[j] = board[j + 1];
    num_entries--;
    return temp;
    }
}
// end of Scoreboard class




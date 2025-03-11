/*	File:			scoreboard.h
	Last Modified:	18-Feb-25
	Purpose:		Implements the scoreboard for a video game
					The main function is to be written by the students to demonstrate:
						1. addition of random game entries to the scoreboard
						2. removal of game entries from the scoreboard
	Source:			Code Fragments 5.1.1 and 5.1.2 in the zyBook Text
	Simplifications:
		1. Scoreboard is defined as a static array of game entries
		2. Array size is fixed, 10 elements, where each element is a game entry object.
*/

#ifndef SCOREBOARD_H
#define SCOREBOARD_H
using namespace std ;
                                                                 
class GameEntry {
  private:
    string name; //The name of a GameEntry object       
    int score;   //The score associated with a GameEntry object      

  public:
/* 
 Function name:   GameEntry                 
 Description:     Constructor for the Gameentry class, which stores a string, name, and an int, score.
 Parameters:      string& n - the passed value to initialize the name member variable of the object to  
                  int s - the passed value to initialize the score member variable of the object to    
 Return Value:    none 
*/
    GameEntry(const string& n = "", int s = 0);

/* 
 Function name:   get_name                       
 Description:     Function to return the "name" member variable of a GameEntry object
 Parameters:      none      
 Return Value:    const string& - the "name" member variabke of the GameEntry object 
*/
    const string& get_name() const;

/* 
 Function name:   get_score                       
 Description:     Function to return the "score" member variable of a GameEntry object
 Parameters:      none      
 Return Value:    int - the "score" member variabke of the GameEntry object 
*/
    int get_score() const;							
};	  // end of GameEntry class

class Scoreboard {
  protected:
    int capacity;       //The amount of elements that can be added to a Scoreboard object's board array         
    int num_entries{0}; //The current amount of elements in the member array board

  private:
    GameEntry board[10]; //The array of GameEntry's for each Scoreboard object

  public:
/* 
 Function name:   Scoreboard                     
 Description:     Constructor of the Scoreboard class, sets the capacity that we access of the GameEntry object  
 Parameters:      int cap - the capacity of Scoreboard, though we'd have to change the size
                      of they array manually in the code, this just limits the amount of elements that can be accessed   
 Return Value:    none (constructor)
*/
    Scoreboard(int cap = 10);

/* 
 Function name:   get_capacity                      
 Description:     returns the capacity member variable of the Scoreboard object
 Parameters:      none      
 Return Value:    int - the value of the capacity member variable 
*/		
    int get_capacity() const;		
  /* 
 Function name:   get_num_entries                    
 Description:     Function to return the num_entries member variable of the Scoreboard object, 
                  which is the current number of elements in the array of Scoreboard
 Parameters:      none      
 Return Value:    int - the value of num_entries 
*/
    int get_num_entries() const;	
/* 
 Function name:   get_entry                    
 Description:     Returns the WordData at the given index of the "board" member array of a Scoreboard object
 Parameters:      int i - the index of the element on the board array that we want to return      
 Return Value:    const GameEntry& - The WordData at the passed index of the "board" member array 
*/
    const GameEntry& get_entry(int i) const;	

    /* 
 Function name:   add                
 Description:     Adds a GameEntry object to the "board" member array in a sorted manner, sorted by the "score" member variable of the GameEntrys
 Parameters:      int score - The score member variable of the new WordData object we are creating and adding
                  const string& - The name member variable of the new WordData object we are creating and adding       
 Return Value:    none
*/
    void add(int score, const string& name);

/* 
 Function name:   remove                   
 Description:     Removes the WordData at the given index of the "board" member array
                      of a Scoreboard object, and shifts every element depending on which element you delete
 Parameters:      int i - the index of the element on the board array that we want to remove    
 Return Value:    GameEntry - the element we removed from the "board" member array 
*/
    GameEntry remove(int i);
};  


#endif

/*******************************************************************/
/*    Course:        CPSC237                                       */
/*    Filename:      WordData.h                                    */
/*    Provided by:   Course Instructor (Dr. Hussain)               */
/*	  Last Modified: 28-Feb-2024								                   */
/*    Purpose:       Declare a class, WordData, to provide member  */
/*					         data and interfaces for member functions.     */
/*					         WordData is a simple object designed to hold a*/
/*                   string and an int. The string is meant to hold*/
/*                   a word and the int is meant to hold the number*/
/*                   of occurences(frequency)of the word in a file.*/
/*                   The int and the string can be retrieved and   */
/*                   set both on their own as well as at the same  */
/*                   time. The object also has the ability to      */
/*                   increment the word's frequency.               */
/*	  Resource:		   WordData.cpp, where definitions of member     */
/*					 functions should be written.				                   */
/*******************************************************************/

#ifndef WORDDATA_H
#define WORDDATA_H
#include <iostream>
#include <string>
using namespace std;

class WordData {
  private: 
	string word;  //Object's word
	int count;    //Object's occurrence counter; shows the occurences of word for the WordData object
  public:

  /*****************************************************************/
  /*    Function name:   constructor                               */
  /*    Description:     Will construct a default word data object.*/
  /*                     Default values are an empty string, and   */
  /*                     zero as the count.		  				           */
  /*    Parameters (In): string word - Word to be placed in object */
  /*                     int count - Value to be placed in counter */
  /*    Return Value:    none                                      */
  /*****************************************************************/  
  WordData(string word = "", int count = 0);
  
  //SETTERS
  /*****************************************************************/
  /*    Function name:   setWord                                   */
  /*    Description:     Will set the object's string.             */
  /*    Parameters (In): string passedWord - Word to be placed in  */
  /*                     the object                                */  
  /*    Return Value:    none                                      */
  /*****************************************************************/
  void setWord(string passedWord);

  /*****************************************************************/
  /*    Function name:   setCount                                  */
  /*    Description:     Will set the occurence counter.           */
  /*    Parameters (In): int count - Value to be placed in counter */
  /*    Return Value:    none                                      */
  /*****************************************************************/
  void setCount(int count);

  /*****************************************************************/
  /*    Function name:   setWordData                               */  
  /*    Description:     Will set both the object's string and the */
  /*                     object's occurence count.                 */
  /*    Parameters (In): string word - Word to be placed in object */
  /*                     int count - Value to be placed in counter */
  /*    Return Value:    none                                      */
  /*****************************************************************/
  void setWordData(string passedWord , int passedCount);

  //GETTERS
  /*****************************************************************/
  /*    Function name:   getWord                                   */
  /*    Description:     Will retrieve the object's string.        */
  /*    Parameters:      none                                      */
  /*    Return Value:    string                                    */
  /*****************************************************************/
  string getWord() const;

  /*****************************************************************/
  /*    Function name:   getCount                                  */
  /*    Description:     Will retrieve the occurence counter.      */
  /*    Parameters:      none                                      */
  /*    Return Value:    int                                       */
  /*****************************************************************/  
  int getCount() const;
  
  /*****************************************************************/
  /*    Function name:   operator ++                               */
  /*    Description:     Will increment the occurrence counter.    */
  /*    Parameters (In):      int inc - Value to be incremented by */
  /*    Return Value:    none                                      */
  /*****************************************************************/
  WordData operator++(int);	// postincrement
  

};		// end of class declaration

/*****************************************************************/
/*    Function name:   operator <<                               */
/*    Description:     Associated stream-insertion operator      */
/*    Parameters:      ostream &output - output stream	         */
/*		       		       const WordData &word  - object to print   */
/*    Return Value:    none                                      */
/*****************************************************************/
ostream &operator<< ( ostream &output, const WordData &data);

#endif

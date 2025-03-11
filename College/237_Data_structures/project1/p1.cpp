/* 
Author:         Daniel Tripoli                                  
Major:          Computer Science                                 
Creation Date:  March 7th, 2025                       
Due Date:       March 12th, 2025                             
Course:         CSC237 010                                      
Professor Name: Dr.Hussain                              
Project:        #1                                          
Filename:       p1.cpp                                 
Purpose:        Runner file, through UI lets the user do 4 different techniques of holding
                data (words) read from a txt file
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include "scoreboard.h"
#include "sortarr.h"

/*
    Function name:       printTableHeader                      
    Description:         prints the header for the table UI    
    Parameters:          none                                  
    Return Value:        none                                  
*/
 void printTableHeader()
 {
     cout << "----------------------------------\n" <<
                 "Word           Frequency\n"       <<
             "----------------------------------\n";
     
 }
 
/*
    Function name:  printTerminal                               
    Description:    Print the UI for the menu     
    Parameters:     none        
    Return Value:   none                                     
*/
 void printTerminal()
 {
     cout << "\n==========================\n"
          << "1: PARALLEL ARRAYS\n" 
          << "2: OBJECTS ARRAY (unsorted)\n"
          << "3: OBJECTS ARRAY (sorted)\n"
          << "4: STL VECTOR\n"
          << "5: EXIT\n"
          << "==========================\n";
 }

/*
    Function name:  isDupe                        
    Description:    checks if a word can be found in the member variables of any 
                        WordData objects of the passed unsorted array. Adds 1 to the count 
                        member variable if the word is a duplicate. 
    Parameters:     string& s - the word that is checked on if it is stored in the array's objects
                    WordData passedArr[] - An array of WordData objects that are to be checked by isDupe   
                    int numElements - the number of elements to check for if "s" is a duplicate    
    Return Value:   true - The passed string was found in an object inside the array
                    false - THe passed string is found to not be a duplicate, meaning it is a unique word                                    
*/
bool isDupe(string& s, WordData passedArr[], int numElements) //Hunts for string in the array, make another for scoreboard search
{
    for(int i{0}; i < numElements; i++) //We know capacity is 10
    {
        if(passedArr[i].getWord() == s) //If we have find a duplicate, we increment the "count" member variable of the duplicate WordData by 1
        {
            passedArr[i]++; 
            return true;
        }
    }
    return false;
}

/*
    Function name:  readToUnArr                          
    Description:    Reads all elements of a txt file as strings, and stores each
                            instance up to 10 words as WordData objects inside of the passed
                            array, keeping track of the number of occurences for each word found
    Parameters:     ifstream& file - variable used to read input from an outside file,
                            must be passed already pointing to a file (which is done by the function menu())        
                    WordData passedArr[] - An array of WordData objects that will store each word read from the txt file (up to 10 words)
    Return Value:   int - the index in which we stop adding elements to the array (the index which we would've added the next item). 
                            Soley used as a helper function for sorted arrays only                                    
*/
int readToUnArr(ifstream& file, WordData passedArr[])
{
  
    int addIndex{0};
    string word{""};
    
    while(file >> word) //Reads through the entire txt file
    {
        if(!isDupe(word, passedArr, addIndex) && (addIndex < 10) ) //Adds element to array if it is not already found in the array
        {
            passedArr[addIndex] = WordData(word, 1);
            ++addIndex;
        }
    }
    
    return addIndex;
}

/* 
 Function name:   printUnArr                             
 Description:     prints out an unsorted array in a tabular manner
 Parameters:      WordData unsortedArr[] - the array we want to print
                  size - the number of elements of the array      
 Return Value:    none 
*/
void printUnArr(WordData unsortedArr[], int size)
{
    cout << "==========================\nObjects Array (unsorted)\n";
    printTableHeader();
    for(int i{0}; i < size; i++) //prints every element stored in the unsorted array
        cout << unsortedArr[i] << '\n';
        
}

/* 
 Function name:   scanFileUnArr                              
 Description:     Calls the readToUnArr function which reads all the data in a txt file,
                        then prints out the elements of the resulting array.
 Parameters:      ifstream& file - variable used to read input from an outside file,
                        must be passed already pointing to a file (which is done by the function menu() ).       
 Return Value:    none 
*/
void scanFileUnArr(ifstream& file) 
{

    WordData unsortedArr[10];
    int addIndex{ readToUnArr(file, unsortedArr) }; //txt file is read and stored to unsortedArr, with the total # of elements stored in addIndex
    printUnArr(unsortedArr, addIndex);
    file.clear();
    file.seekg(0);
}

/* 
 Function name:   printSortArr                             
 Description:     prints out the elements of a SortArr object in a tabular manner
 Parameters:      SortArr& unsortedArr - the SortArr we want to print the elements off (using the array that SortArrs have)
                  int size - the number of elements of the array stored in SortArr      
 Return Value:    none 
*/
void printSortArr(SortArr& sortedArr, int size)
{
    cout << "==========================\nObjects Array (sorted)\n";
    printTableHeader();
    for(int i{0}; i < size; i++) //Outputs the elements of the sorted array
        cout << sortedArr.get_entry(i) << '\n';
} 

/* 
 Function name:   scanFileSortArr                           
 Description:     Calls the readToUnArr function which reads all the data in a txt file,
                        then sorts it by adding the unsorted array's values into a sortArr object, 
                        which automatically is sorted via the function add().
                        All the elements of the sorted array are printed.      
 Parameters:      ifstream& file - variable used to read input from an outside file,
                        must be passed already pointing to a file (which is done by the function menu())       
 Return Value:    none 
*/
void scanFileSortArr(ifstream& file)
{
    SortArr sArr{};
    WordData unSortArr[10];
    int addIndex{readToUnArr(file, unSortArr)};
    
    for(int i{0}; i < addIndex; i++) //Adds elements of the unsorted array to the sorted array, automatically sotring it via sArr.add()
    {
        sArr.add(unSortArr[i].getCount(), unSortArr[i].getWord());
    }
    printSortArr(sArr, addIndex);
    file.clear(); 
    file.seekg(0);
}

/*
    Function name:  isDupe                        
    Description:    checks if a word can be found in the member variables of any 
                            words in the passed wordArr. Adds 1 to the count found
                            in countArr at the same index as the wordArr if the passed 
                            word is a duplicate. 
    Parameters:     string& s - the word that is checked on if it is stored in the word array
                    string wordArr[] - An array of words that are to be checked by isDupe
                    int countArr[] - The array of frequency for each word, associated by indexes with wordArr       
                    int numElements - the number of elements stored in both wordArr and countArr, which increases program efficiency and modularity
    Return Value:   true - The passed string was found in the word array
                    false - THe passed string is found to not be a duplicate, meaning it is a unique word                                    
*/
bool isDupe(string& s, string wordArr[], int countArr[], int numElements) 
{
    for(int i{0}; i < numElements; i++) //Checks every element stored in the wordArr
    {
        if(wordArr[i] == s) //If we have find a duplicate, we increment the "count" member variable of the countArr by 1
        {
            countArr[i]++; 
            return true;
        }

    }
    return false;
}

/* 
 Function name:   printParaArr                             
 Description:     prints out the elements of the parallel arrays in a tabular manner
 Parameters:      WordData unsortedArr[] - the array we want to print
                  size - the number of elements of the array      
 Return Value:    none 
*/
void printParaArr(string wordArr[], int countArr[], int size)
{
    cout << "==========================\nParallel Arrays\n";
    printTableHeader();
    for(int i{0}; i < size; i++) //prints all of the elements from the parrallel arrays
        cout << wordArr[i] << setw(21 - wordArr[i].size()) << countArr[i] << '\n';
}

/* 
 Function name:   scanFileParaArr                           
 Description:     Reads all the data in a txt file,
                        then stores the unique word in wordArr and the count (frequency)
                        of each word at the same index as wordArr but in the countArr. 
 Parameters:      ifstream& file - variable used to read input from an outside file,
                        must be passed already pointing to a file (which is done by the function menu())       
 Return Value:    none 
 */
void scanFileParaArr(ifstream& file) 
{
    string wordArr[10];
    int countArr[10];
    int addIndex{0};
    string word{""};
    
    while(file >> word) //Reads all the way to the end of the file
    {
        if(!isDupe(word, wordArr, countArr, addIndex) && (addIndex < 10) ) //Adds element to array if it is not already found in the array
        {
            wordArr[addIndex] = word;
            countArr[addIndex] = 1;
            ++addIndex;
        }

    }
    printParaArr(wordArr, countArr, addIndex);
    file.clear(); 
    file.seekg(0);
}

/*
    Function name:  isDupe                        
    Description:    checks if a word can be found in the member variables of any 
                        WordData objects of the passed vector. Adds 1 to the count 
                        member variable at the location where the duplicate was 
                        found if the passed word is a duplicate. 
    Parameters:     string& s - the word that is checked on if it is stored in 
                            the array's objects
                    vector<WordData> v - A vector of WordData objects that are to 
                            be checked by isDupe for an occurance of the passed word 
                            in any WordData object      
    Return Value:   true - The passed string was found in an object inside the vector
                    false - THe passed string is found to not be a duplicate, meaning it is a unique word                                    
*/
bool isDupe(string& s, vector<WordData>& v) 
{
    for(int i{0}; i < v.size(); i++) //Checks every element stored in the vector for the string s
    {
        if(v[i].getWord() == s)      //If we have find a duplicate, we increment the "count" member variable of WordData at the found index in the vector
        {
            v[i]++; 
            return true;
        }
    }
    return false;
}

/* 
 Function name:   printVector                           
 Description:     prints out the WordData elements stored in the vector in a tabular manner
 Parameters:      vector<WordData> v - the vector we want to print out   
 Return Value:    none 
*/
void printVector(vector<WordData>& v)
{
    cout << "==========================\nSTL Vector\n";
    printTableHeader();
    for(int i{0}; i < v.size(); i++) //prints every element stored in the vector
        cout << v[i] << '\n';
}

/* 
 Function name:   scanFileVector                         
 Description:     Reads all the data in a txt file, then stores the unique words in a vector, 
                        increasing the count of a WordData object via the isDupe function in 
                        the case of multiple occurences of a word.
 Parameters:      ifstream& file - variable used to read input from an outside file,
                        must be passed already pointing to a file (which is done by the function menu())       
 Return Value:    none 
 */
void scanFileVector(ifstream& file)
{
    vector<WordData> vect;
    string word{""};
    
    while(file >> word)         //Reads all the way to the end of the txt file
    {
        if(!isDupe(word, vect)) //Adds element to array if it is not already found in the array
        {
            vect.push_back(WordData(word, 1)); //New elements are added to the end
        }
    }

    printVector(vect);
    file.clear(); 
    file.seekg(0);
    
}

/* 
 Function name:   askFile                      
 Description:     Asks user for a txt file to read from and won't stop till a proper txt file is supplied (mainly used to make the sortingSim function code more compact)
 Parameters:      ifstream& file - The ifstream that is used to read from the txt file    
 Return Value:    none 
*/
void askFile(ifstream& file)
{
    string input{""};
    cout << "==========================\n\nenter a file name to use: ";
    cin >> input;

    file.open(input);
    while(!file) //Case for file is not found
    {
        cout << "File does not exist! try again: ";
        cin >> input; 
        file.open(input);
    }
}

/* 
 Function name:   sortingSim                      
 Description:     Collects user input of file to be read from then carries out the 
                  logic of the menu UI
 Parameters:      none      
 Return Value:    none 
*/
void sortingSim()
{
    ifstream file{};
    askFile(file); //asks user for file until they supply a valid one
    string input{""}; //Used for menu input
    while(input != "5") //Keeps going till exit value "5" is typed
    {
        printTerminal(); 
        cin >> input;

        if      (input == "1") scanFileParaArr(file);
        else if (input == "2") scanFileUnArr(file);
        else if (input == "3") scanFileSortArr(file);
        else if (input == "4") scanFileVector(file);
        else if (input != "5") cout << "incorrect input! try again:\n";
    }
    file.close();
}

int main()
{
    sortingSim();
}



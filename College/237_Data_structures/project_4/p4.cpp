#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include "insertionSort.h"
#include "mergeSort.h"
#include "quickSort.h"
using namespace std;

//getClockTime();
void storeRandom(vector<int>& passedVect, int n) //n is number of elements being added
{
    
   
    srand(9000);

    for(int i{0}; i < n; i++)
    {
        passedVect.push_back(rand());
    }
    
}

template<typename T>
void displayVect(const vector<T>& passedVect, int printStatement = -1, int elemCount = -1) //Displays 30 per row
{
    switch(printStatement)
    {
        case(0):
            cout << "\nUnsorted Numbers:\n";
            break;
        case(1):
            cout << "\nInsertion-Sort (n=" << elemCount << ")\n\n    Sorted Numbers:\n\n";
            break;
        case(2):
            cout << "\nMerge-Sort (n=" << elemCount << ")\n\n    Sorted Numbers:\n\n";
            break;
        case(3):
            cout << "\nQuick-Sort (n=" << elemCount << ")\n\n    Sorted Numbers:\n\n";
            break;
    }
    

    int count{0};
    for(int i{0}; i < passedVect.size(); i++)
    {
        if(count == 30)
        {
            cout << '\n';
            count = 0;
        }
        cout << passedVect[i] << " ";
        count++;
    }
    cout << '\n';
    
}

/* template<typename T>
void displayTable(T passedArr[3][3])
{
    for(int i{0}; i < 3; i++)
    {
        if (i == 0)
            cout << setw(8) << "Insertion Sort |";
        if(i == 1)
            cout << setw(8) << "Merge Sort     |";
        if(i == 2)
            cout << setw(8) << "Quick sort     |";
        for(int j{0}; j < 3; j++ )
        {
            cout << setw(8) << passedArr[i][j] << " |";
        }
        cout << '\n';
    }
} */



 void dispSummary(unsigned long long summary[][3], int algCount)
{
    cout << "\nSummary of Statistics\n-----------------------------\n1. Performance Criterion: Number of comparisons\n               |                2000 |               10000 |              100000 |\n-------------------------------------+---------------------+---------------------+\n";
    for(int r{0}; r < algCount * 2; r++) 
    {    
        if(r == algCount)
            // cout << "\n\n";
            cout << "\n2. Performance Criterion: Execution time measured as number of clock ticks\n               |                2000 |               10000 |              100000 |\n-------------------------------------+---------------------+---------------------+\n";
    
        switch(r)
        {
            case(0):
            case(3):
                cout << "Insertion Sort |";
                break;
            case(1):
            case(4):
                cout << "Merge Sort     |";
                break;
            case(2):
            case(5):
                cout << "Quick Sort     |";
                break;
        }

        for(int c{0}; c < 3; c++)
            cout << setw(20) << summary[r][c] << " |"; 

        cout << '\n';
    }   
}
 

//void getStats(vector<int>& smallData, vector<int>& mediumData, vector<int>& largeData, int algCount) //Do we want the vector to actually be sorted at the end or leave it unsorted?
void getStats(vector<vector<int>>& data, unsigned long long summary[][3])
{
    int comparisonCount{0};
    //int summary[algCount][3]; //Stores comparison  data
    //int summary[algCount][3]; //Stores comparison  data
    int r{0};
    int c{0};
    clock_t before;
    clock_t after;
    for(vector<int> elem : data) //Need to add clockData insertion, possible increase comp data
    {
        vector<int> oldElem = elem;

        before = clock();
        insertion_sort(elem, comparisonCount);
        after = clock();
        if(elem.size() == 2000) //Is it ok to hard code this in?
            displayVect(elem, 1, 2000);
        summary[r + 3][c] = difftime(after, before);
        summary[r][c] = comparisonCount;
        
        comparisonCount = 0;
        r++;
        elem = oldElem;

        before = clock();
        merge_sort(elem, comparisonCount);
        after = clock();

        if(elem.size() == 2000)
            displayVect(elem, 2, 2000);
        summary[r + 3][c] = difftime(after, before);
        summary[r][c] = comparisonCount;
        
        comparisonCount = 0;
        r++;
        elem = oldElem;

        before = clock();
        quick_sort(elem, comparisonCount);
        after = clock();
        if(elem.size() == 2000)
            displayVect(elem, 3, 2000);
        summary[r + 3][c] = difftime(after, before);
        summary[r][c] = comparisonCount;
        comparisonCount = 0;

        r = 0;
        c++;
    }
}

int main() //Can we use cout in main for the "unsorted 2k elems" header?
{
    //vector<vector<int>> data; //Did this to make program more modular
    vector<int> myVect2k;
    vector<int> myVect10k;
    vector<int> myVect100k;
    storeRandom(myVect2k, 2000);
    storeRandom(myVect10k, 10000);
    storeRandom(myVect100k, 100000);
    vector<vector<int>> data;
    data.push_back(myVect2k);
    data.push_back(myVect10k);
    data.push_back(myVect100k);
    //cout << "Unsorted Numbers:\n";

   displayVect(myVect2k, 0);
    unsigned long long summary[6][3]; //You only have to change this to add more algorithms to test, though you can ONLY add more algorithms to test, not more than 3 samples
    getStats(data, summary); //WE want to store data in main, then call displaySummary(data) in main
    dispSummary(summary, 3);



    ////////////////////DO WE NEED TO USE DISPSUMMARY IN MAIN??? 


}

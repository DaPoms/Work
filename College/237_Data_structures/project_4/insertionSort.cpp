#include "insertionSort.h"

// Sorts an array of n elements                                                                                    
// void insertion_sort(vector<int>& data, int& comparisonCount) 
void insertion_sort(vector<int>& data, int& comparisonCount)
{
   

    for (int k = 1; k < data.size(); k++) {               // begin with second character
        int cur{data[k]};                         // might relocate cur=data[k]
        int j{k};  
                                     // find correct index j for cur
        while (j > 0 && cur < data[j - 1])  // thus, data[j - 1] must move after cur
        {   
            comparisonCount++; 
            data[j] = data[j - 1];              // slide data[j - 1] rightward
            j--;                                // and consider previous j
        }
        
        data[j] = cur;                          // this is the proper place for cur
    }
   
}

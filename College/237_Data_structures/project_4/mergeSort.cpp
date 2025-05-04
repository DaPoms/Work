#include "mergeSort.h"

// Merges the contents of sorted vectors S1 and S2 into result S
template <typename T>
void merge(const vector<T>& S1, const vector<T>& S2, vector<T>& S, int& comparisonCount) { //Only works for int
    S.resize(S1.size() + S2.size());
    int i{0}, j{0}, k{0};
    while (k < S.size()) 
    {
        comparisonCount++;

        if (j == S2.size() || (i < S1.size() && S1[i] < S2[j]))
        {
            if(j != S2.size())   
                comparisonCount++;
            S[k++] = S1[i++];                            // copy ith element of S1 to S
        }
        else
            S[k++] = S2[j++];                            // copy jth element of S2 to S
    }
}



// void merge_sort(vector<int>& S, int& comparisonCount) 
void merge_sort(vector<int>& S, int& comparisonCount) 
{
    int n(S.size());
    if (n < 2)  // vector is trivially sorted
    return;                                  

    int mid{n / 2};
    vector<int> S1(S.begin(), S.begin() + mid);            // copy of first half
    vector<int> S2(S.begin() + mid, S.end());              // copy of second half
    // conquer (with recursion)
    merge_sort(S1, comparisonCount);
    merge_sort(S2, comparisonCount);
    // merge results
    merge(S1, S2, S, comparisonCount);                              // merge sorted halves back into original
}

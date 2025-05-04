#include "quickSort.h"
// Sorts the contents of vector S using the given comparator to define the element ordering

//void quick_sort(vector<int>& S, int& comparisonCount) 
void quick_sort(vector<int>& S, int& comparisonCount) 
{
    int n(S.size());
    if (n < 2) 
        return;                                   // list is trivially sorted
    
    // divide
    int pivot = S.back();
    vector<int> L,E,G;                                       // three empty lists
    for (int element : S) {
        if (element < pivot)                        // element strictly less than pivot
        {
            comparisonCount++;
            L.push_back(element);
        }
        else if (element > pivot)                   // element strictly greater than pivot
        {
            comparisonCount+=2;
            G.push_back(element);
        }
        else                                             // element is equal to pivot  //Does this count as a comparison??? eghorjkhrtioghjirhjijhijrihbjiarjrgioma
        {
            comparisonCount+=2;
            E.push_back(element);
        }
    }

    // conquer
    quick_sort(L, comparisonCount);
    quick_sort(G, comparisonCount);

    // concatenate results back into S
    S.clear();
    for (int elem : L)
        S.push_back(elem);
    for (int elem : E)
        S.push_back(elem);
    for (int elem : G)
        S.push_back(elem);
}

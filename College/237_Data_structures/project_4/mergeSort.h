#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
using namespace std;
template <typename T>
void merge(const vector<T>& S1, const vector<T>& S2, vector<T>& S, int& comparisonCount);


// void merge_sort(vector<int>& S, int& comparisonCount);
void merge_sort(vector<int>& S, int& comparisonCount);

#endif

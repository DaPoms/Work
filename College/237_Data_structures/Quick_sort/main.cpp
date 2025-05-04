#include <list>
#include <iostream>
using namespace std;

//NOT MY CODE
// Sorts the contents of vector S using the given comparator to define the element ordering
template <typename T>
void quick_sort(list<T>& S)
 {
    int n(S.size());
    if (n < 2) return;                                   // list is trivially sorted

    // divide
    T pivot = S.back();
    list<T> L,E,G;                                       // three empty lists
    for (T element : S) {
        if (element < pivot)                        // element strictly less than pivot
            L.push_back(element);
        else if (element > pivot)                   // element strictly greater than pivot
            G.push_back(element);
        else                                             // element is equal to pivot
            E.push_back(element);
    }

    // conquer
    quick_sort(L);
    quick_sort(G);

    // concatenate results back into S
    S.clear();
    for (T elem : L)
        S.push_back(elem);
    for (T elem : E)
        S.push_back(elem);
    for (T elem : G)
        S.push_back(elem);
}

// All (the very simple) code below IS my code
template<typename T>
void dispSeq(const list<T>& S)
{
    for(T item : S)
        cout << item << " ";
    cout << '\n';
}

int main()
{
    list<int> myList{6,3,1,8,1,12,15,-1,9,11};
    dispSeq(myList);
    quick_sort(myList);
    dispSeq(myList);
}

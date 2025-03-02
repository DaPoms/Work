#include <iostream>
using namespace std;

template <typename T>
void passArr(T arr[], int size)
{
    for(int i{0}; i < size; i++)
    {
        cout << arr[i] << " ";
    }
}

int main()
{
    int arr[4][2] = {1,2,3,5,6,7};

    passArr(arr[1],4); //You can pass pieces of a 2d aray, one row at a time
}

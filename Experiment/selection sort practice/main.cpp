#include <iostream>
void printIntArr(int arr[], int numElements);
void swapArrVals(int& left, int& right);
void insertionSort(int arr[], int numElements);

void swapArrVals(int& left, int& right)
{
    int placeholder = left;
    left = right;
    right = placeholder;
}

void insertionSort(int arr[], int numElements)//checi if this is how to insert arr
{
    int minindex{};
    int traverse{};

    for (int i{0}; i < numElements; i++)
        {

        traverse = i;
    
        while( (arr[traverse] < arr[traverse - 1]) && (traverse > 0))
        {
            swapArrVals(arr[traverse], arr[traverse - 1] );
            --traverse;
        }
        
        printIntArr(arr, 5);

            

        }
}

void printIntArr(int arr[], int numElements)
{
    for(int i{0}; i < numElements; i++)
        std::cout << arr[i] << " ";
    std::cout << '\n';
}

int main()
{
    system("CLS");

    int arr[5] = {10,31,2,105,25};


    insertionSort(arr, 5);

    //printIntArr(arr,5);


}

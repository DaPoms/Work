#include <iostream>
void printArr(int arr[], int amountNum)
{
    for(int i{0}; i < amountNum; i++)
        std::cout << arr[i] << " ";
}

void swapInts(int& left, int& right) //tried a different swap int this time, learned about '&' from teacher
{
    int placeholder{left};
    left = right;
    right = placeholder;
}


void selectionSort(int arr[], int amountNum)
{
    
    int minindex{0};

    for(int sorted{0}; sorted < amountNum - 1; sorted++) //we do -1 as once we've sorted the 2nd to last val, we already know the last one is sorted
    {
        minindex = sorted;

        for(int traverseRight{sorted}; traverseRight < amountNum; traverseRight++)
            {

            if(arr[traverseRight] < arr[minindex])
            {
                minindex = traverseRight;
            }

            
            }

            swapInts(arr[sorted], arr[minindex]);
            //std::cout << "\n\n"; // TEST CODE
            //printArr(arr, amountNum);//prints steps
    }  
}


int main()
{
    int arr[5] = {105, 25, 3, 32, 6};
    selectionSort(arr, 5);
    printArr(arr, 5);
}

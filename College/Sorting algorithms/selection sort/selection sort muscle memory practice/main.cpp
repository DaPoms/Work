#include <iostream>

void printArr(int arr[], int arrLen)
{
    for(int i{0}; i < arrLen; i++)
        std::cout << arr[i] << " ";
}

void swapInt(int& min, int& sortSlot)
{
    int placeholder{min};
    min = sortSlot;
    sortSlot = placeholder;
}

void selectionSort(int arr[], int arrLen) //Decided to program it again from scratch just to go through the logic of why this program works
{
    int minIndex;

    for(int toBeSorted{0}; toBeSorted < arrLen - 1; toBeSorted++) //toBeSorted is the index where the next minimum will go, arrLen -1 for end as we
    //don't need to compare last val to itself
    {
        minIndex = toBeSorted;

        for(int findMin{toBeSorted + 1}; findMin < arrLen; findMin++) //is toBeSprted more efficient with +1? (as the first for usualy compares sortedindex with itself, making it pointless)
        {
            if(arr[findMin] < arr[minIndex])
                minIndex = findMin;
        }

        swapInt(arr[minIndex], arr[toBeSorted]);
        std::cout << "\n\n";
        printArr(arr, arrLen);

    }
}

int main()
{
    int arr[7] = {90, 53, 152, 4, 1052, 97, 34};
    selectionSort(arr, 7);
}

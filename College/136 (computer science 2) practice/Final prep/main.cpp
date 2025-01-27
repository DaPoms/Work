#include <iostream>

void selectionSort(int arr[], int numElts);

void insertionSort(int arr[], int numElts);

void bubbleSort(int arr[], int numElts);

void printArr(int arr[], int numElts);

void printArr(int arr[], int numElts)
{
    for(int i{0}; i < numElts; i++)
    {
        std::cout << arr[i] << " ";
    }
}

void bubbleSort(int arr[], int numElts)
{
    int placeholder{};
    for(int indexToBeSorted{numElts - 1}; indexToBeSorted > 0; indexToBeSorted--)
    {
        for(int bubbleIndex{0}; bubbleIndex < indexToBeSorted; bubbleIndex++)
        {
            if(arr[bubbleIndex] > arr[bubbleIndex + 1])
            {
                printArr(arr, numElts);
                std::cout << "\n";
                placeholder = arr[bubbleIndex];
                arr[bubbleIndex] = arr[bubbleIndex + 1];
                arr[bubbleIndex + 1] = placeholder;
                
            }
             
        }
    }
   
}

void insertionSort(int arr[], int numElts)
{
    int placeholder{};
    int traverse{};
    for(int indexToBeSorted{1}; indexToBeSorted < numElts; indexToBeSorted++)
    {
        traverse = indexToBeSorted;
        while(traverse > 0 && arr[traverse] < arr[traverse - 1])
        {
            placeholder = arr[traverse];
            arr[traverse] = arr[traverse - 1];
            arr[traverse - 1] = placeholder;
            traverse--;
        }
    }
    printArr(arr, numElts);
}

void selectionSort(int arr[], int numElts)
{
    int minIndex{0};
    int placeholder{};
    for(int indexToBeSorted{0}; indexToBeSorted < numElts - 1; indexToBeSorted++)
    {
        int minIndex = indexToBeSorted; //

        for(int traverseArr{indexToBeSorted}; traverseArr < numElts; traverseArr++)
        {
            if(arr[minIndex] > arr[traverseArr])
            {
                minIndex = traverseArr;
            }
        }
        
        placeholder = arr[minIndex];
        arr[minIndex] = arr[indexToBeSorted];
        arr[indexToBeSorted] = placeholder;
    }
    printArr(arr, numElts);

}





int main()
{
    int arr[7] = {12,5,1,50,3,70,4};

    //selectionSort(arr,7);
    //insertionSort(arr,7);
    bubbleSort(arr,7);
}



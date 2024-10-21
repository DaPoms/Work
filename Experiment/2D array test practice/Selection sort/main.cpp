#include <iostream>

void selectionSort(int arr[3][3], int numElementsPerRow, int numRows) //Only works on array that is 3 by 3
{
    int minIndex{0};
    int placeholder;

    for(int currRow{0}; currRow < numRows; currRow++)
    {

        for(int sortedIndex{0}; sortedIndex < numElementsPerRow; sortedIndex++)
        {
            minIndex = sortedIndex;

            for(int traverse{sortedIndex}; traverse < numElementsPerRow; traverse++)
            {
                if(arr[currRow][minIndex] > arr[currRow][traverse])
                    minIndex = traverse;
            }
            
            placeholder = arr[currRow][sortedIndex];
            arr[currRow][sortedIndex] = arr[currRow][minIndex];
            arr[currRow][minIndex] = placeholder;
        }

    }
}

int main()
{
    int arr[3][3] = { {3,2,1}, {1,3,2}, {3,1,2} };

    selectionSort(arr, 3, 3);

    for(int r{0}; r < 3; r++)
    {
        for(int c{0}; c < 3; c++)
            std::cout << arr[r][c] << " ";
        std::cout << "\n";
    }

}

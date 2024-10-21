#include <iostream>


void insertionSort(int arr[3][3], int numElementPerRow, int numRows)
{
    int traverse;
    int placeholder;

    for(int currRow{0}; currRow < numRows; currRow++)
    {

        for(int sortedIndex{1}; sortedIndex < numElementPerRow; sortedIndex++)
        {
            traverse = sortedIndex;

            while(arr[currRow][traverse] < arr[currRow][traverse - 1] && (traverse > 0) )
            {
                placeholder = arr[currRow][traverse];
                arr[currRow][traverse] = arr[currRow][traverse - 1];
                arr[currRow][traverse - 1] = placeholder;
                traverse--;
            }

        }

    }
}


int main()
{
    int arr[3][3] = { {3,2,1}, {1,3,2}, {3,1,2} };

    insertionSort(arr, 3, 3);

    for(int r{0}; r < 3; r++)
    {
        for(int c{0}; c < 3; c++)
            std::cout << arr[r][c] << " ";
        std::cout << "\n";
    }

}

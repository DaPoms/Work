#include <iostream>
//should I add forward declaration
void swapInts(int array[], int index1, int index2)
{
    int placeholder = array[index1];
    array[index1] = array[index2];
    array[index2] = placeholder;
} 

void insertionSort(int array[], int listCount) //NEED TO FIX!!!
{
    for(int sortedIndex{1}; sortedIndex < listCount; sortedIndex++)
    {
        int traverseLeft{sortedIndex}; //Used to move var down till it reaches the point is belongs

        while ( (array[traverseLeft - 1] > array[traverseLeft]) && (traverseLeft > 0)) //Keeps on moving value left till it is greater than the val to the left of it
        {
            swapInts(array, traverseLeft, traverseLeft - 1);
            traverseLeft--;
        }
    }   
}





int main() 
{
    int list[6] = {120,23,1,10,5,2};
   

    insertionSort(list, 6);


    for (int i{0}; i < sizeof(list) / 4 ; i++)
        std::cout << list[i] << " ";
}

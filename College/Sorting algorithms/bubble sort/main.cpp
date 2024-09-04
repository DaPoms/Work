#include <iostream>

void swapVal(int array[], int index1, int index2) //Got inspiration for this from my teachers creation of the sorting method, thought it is not a copy
{
    int placeholder{array[index1]};
    array[index1] = array[index2];
    array[index2] = placeholder;
}

void bubbleSort(int array[], int listCount)
{
    int placeholder{};
    int right{};
    
    for (int sorted{listCount - 1}; sorted > 0; sorted--) //sets to end when sorted all the way, did -1 as index starts at 0, not 1 in c++
    //makes code efficient as we know if something made is in the sorted area, the greatest value is to the right
    {

        

        for(int left{0}; left < sorted; left++)  //Does bubble sort by comparing value on the left to the one on the right, and moving to the right the larger one.
            {
                right = left + 1; //made with var to make code more understandable
                if( array[left] > array[right] ) //process of swapping values
                {
                    swapVal(array, left, right);
                }
                    
            }   
    }
}


int main ()
{
    int list[10] = {12,96,35,102,502,1,9,80,56,21};
    int endIndex{ (sizeof(list) / 4) - 1};
    

  
    bubbleSort(list, 10);
   
   

    for(int i{0}; i < endIndex + 1; i++)
        std::cout << list[i] << " ";

}

#include <iostream>
int main ()
{
    int list[10] = {12,96,35,102,502,1,9,80,56,21};
    int endIndex{ (sizeof(list) / 4) - 1};
    int placeholder{};
    int right{};

   for (int sorted{endIndex}; sorted > 0; sorted--) //sets to end when sorted all the way, 
   //makes code efficient as we know if something made is in the sorted area, the greatest value is to the right
   {

      

    for(int left{0}; left < sorted; left++)  //Does bubble sort by comparing value on the left to the one on the right, and moving to the right the larger one.
        {
            right = left + 1; //made with var to make code more understandable
            if( list[left] > list[right] ) //process of swapping values
            {
                placeholder = list[left];
                list[left] = list[right];
                list[right] = placeholder;
            }
                
        }

   }
   

    for(int i{0}; i < endIndex + 1; i++)
        std::cout << list[i] << " ";

}

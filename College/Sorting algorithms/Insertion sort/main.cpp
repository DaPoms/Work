#include <iostream>

int main() //Need to test if this is actually insertion sort, but it does work...
{
    int list[5] = {23,1,10,5,2};
    int size = sizeof(list) / 4;
    int val{1};
    int placeholder{};

    for(int sorted{0}; sorted < size; sorted++)
    {
        

        while(val < size) //statement to move down the line
        {
            if(list[val] < list[sorted]) //tests if next value in unsorted portion is smaller than the smallest value of the organized list, changes places if true
                {
                    placeholder = list[val];
                    list[val] = list[sorted];
                    list[sorted] = placeholder;
                }
            val++;
            
        }
        
        val = sorted + 1;
    }

    for (int i{0}; i < size; i++)
        std::cout << list[i] << " ";
}

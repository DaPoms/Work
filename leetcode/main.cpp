#include <iostream>
#include <vector>

//Task - create program that stores a large int in the form of an array, with the end being the 1st and smallest digit and the first index being the largest.
//Make an increment function which adds +1 to the lowest digit, rounding up if it goes beyond 10. 

//My implimentation works for only the last digit rounding, so 109 + 1 --> 110, but 199 + 1 doesn't work
using namespace std;

void dispArr(vector<int> arr, int n);

void increment(vector<int> arr, int n)
{
       arr[n-1] = arr[n-1] + 1;

       if (arr[n-1] >= 10)
       {
            arr[n-1] = 0;

            if(arr.size() > 1)
                arr[n-2] = arr[n-2] + 1;
            else    
            {
                arr.insert(arr.begin(),1);
                n++;
            }
       }
    dispArr(arr,n);
}

void dispArr(vector<int> arr, int n)
{
    for(int i{0}; i < n; i++)
    {
        cout << arr.at(i) << " ";
    }
    cout << '\n';
}
int main()
{
    vector<int> arr{9};
    vector<int> arr2{2,0,9};
    vector<int> arr3{4,3,2,1};
   

   

    increment(arr2,3);
   

    increment(arr3,4);
   

    increment(arr,1);
    

}

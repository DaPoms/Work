#include <iostream>

void isNonDecreasing(int arr[], int n) //Returns false when array of size 4 has decreasing pattern or a not strictly increasing pattern, true when it is strictly increasing
{
    int i{0};

    while(i < n && ( arr[i] < arr[i+1] ) )
        i++;
    if(arr[i] < arr[i+1])
        std::cout << "True";
    else
        std::cout << "False";
}

void hasConsecutivePair(int arr[], int n) //Returns true if consecutive elements in an array are the same value
{
    int i{0};

    while(i < n && arr[i] != arr[i + 1])
    {
        i++;
    }

    if(arr[i] == arr[i + 1])
        std::cout << "True";
    else
        std::cout << "False";
}

bool containsSumOfZero(int arr[], int n) //Returns true if any numbers in array summed together equal 0
{
    for(int curr{0}; curr < n; curr++)
    {
        int i = curr + 1;
        while(i < n)
        {
            if(arr[curr] + arr[i] == 0)
                return true;
            i++;
        }
    }

    return false;
}

int main()
{
    // Test cases for isNonDecreasing
    //int arr[4] = {1,2,3,4}; //True
    // int arr[4] = {1,2,6,1}; //False
    // int arr[4] = {1,2,6,1}; //False
    //int arr[4] = {1,1,1,1}; //False
    // isNonDecreasing(arr,4);

    //Test cases for hasConsecutivePair
    // int arr[4] = {1,2,5,5}; //True
    // int arr[4] = {1,2,5,1}; //False
    // hasConsecutivePair(arr,4);

    //Test cases for containsSumOfZero
    // int arr[4] = {-5,2,5,-5}; //True
    //int arr[4] = {1,2,20,3}; //False
    int arr[4] = {1, 0, 3, 0}; //True
    std::cout << containsSumOfZero(arr,4);
}

//I only wrote main for this, not binary_search(). That was supplied by my teacher
#include <iostream>
using namespace std;

bool binary_search(int data[], int target, int low, int high) {
    if (low > high)
        return false;
    else {
        int mid{(low + high) / 2};
        if (target == data[mid])
            return true;
        else if (target < data[mid])
            return binary_search(data, target, low, mid - 1);
        else
            return binary_search(data, target, mid + 1, high);
    }
 }

 
int main()
{
    int arr[6] = {2, 10, 18, 36, 54, 86};
    int input{-1};
    cout << "What value are you looking for?: ";
    cin >> input; 

    if(binary_search(arr, input, 0, 5))
        cout << "element was found in the array!";
    else
        cout << "element was not found in the array :C";
}

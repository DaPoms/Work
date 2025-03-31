//I only wrote main for this, not binary_search(), though I wrote the comments. binary_search() was supplied by my teacher
#include <iostream>
using namespace std;

bool binary_search(int data[], int target, int low, int high) {
    if (low > high) //Case of item not being found
        return false;
    else {
        int mid{(low + high) / 2}; //Finding midpoint
        if (target == data[mid]) //Case of element being found
            return true;
        else if (target < data[mid]) //Case of element being on the left side of the array
            return binary_search(data, target, low, mid - 1);
        else //Case of element being on the right side of the array
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

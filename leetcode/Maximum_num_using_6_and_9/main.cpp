#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//This version finds the max number with 6 and 9 if you can only change one digit to a 9
int vectToInt(vector<int> digits) //requires a vector of ints
{
    int ans{0};
    for(int i{0}; i < digits.size(); i++)
        ans += digits[i] * pow(10,i); //adds each digit
    return ans;
}

int maximum69Number (int num) 
{
    int number = num; //backup of num
    vector<int> digits;
    while(number) //extracts digits
    {
        digits.push_back(number % 10);
        number = number / 10;
    }
    int highest6{static_cast<int>(digits.size()) - 1};
    while( highest6 > -1 && digits[highest6] != 6)
        highest6--;

    if(highest6 == -1) //We don't need to do anything if the number is all 6's or all 9's
        return num;
    digits[highest6] = 9;
    return vectToInt(digits);
}

/* This version I built for finding the max num if you're only allowed to SWAP 2 digits
int vectToInt(vector<int> digits) //requires a vector of ints
{
    int ans{0};
    for(int i{0}; i < digits.size(); i++)
        ans += digits[i] * pow(10,i); //adds each digit
    return ans;
}
void swapVals(int *left, int *right) //using pointers you can swap values in data structures without outright passing them as params!
{
    int* placeholder = left;
    left = right;
    right = placeholder;
}

int maximum69Number (int num) 
{
    int number = num; //backup of num
    vector<int> digits;
    while(number) //extracts digits
    {
        digits.push_back(number % 10);
        number = number / 10;
    }
    int highest6{static_cast<int>(digits.size()) - 1};
    while( highest6 > -1 && digits[highest6] != 6)
        highest6--;

    int lowest9{0};
    while(lowest9 < digits.size() && digits[lowest9] != 9)
        lowest9++;
    if(highest6 == -1 || lowest9 == digits.size()) //We don't need to do anything if the number is all 6's or all 9's
        return num;
    swapVals(&digits[highest6], &digits[lowest9]); //On the negative this function is less readable than if you passed the vector
    return vectToInt(digits);
}
 */

int main()
{
    cout << maximum69Number(9996);
}

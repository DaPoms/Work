#include <vector>
#include <iostream>

using namespace std;
vector<int> plusOne(vector<int>& digits)
{
    int currDigit{static_cast<int>(digits.size()) - 1}; //starts by adding at end
    digits[currDigit]++; //Increments by 1

    while (currDigit >= 0 && digits[currDigit] == 10)
    {
        digits[currDigit] = 0; // Incrementing the val 9 brings that digit back to 0 and gives + 1 to the next digit
        if(currDigit != 0) //Did this to prevent seg fault for case when == 0, I wanted this as the above code will set the digit to 0, preparing for the conditions in the next if statement
            digits[currDigit - 1]++; 
        currDigit--;
    }    

    if(currDigit == -1 && digits[0] == 0) //Case of adding new digit EX: 99 + 1 = 100
        digits.insert(digits.begin(), 1);

    return digits;
}

int main()
{
    vector<int> test = {9};
    plusOne(test);

    for(int num : test)
        cout << num << " ";
}

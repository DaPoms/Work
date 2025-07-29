//Task : add digits of an int together till you're left with a one digit answer
#include <iostream>
int addDigits(int num) 
{
    int val = num;
    int sum{0};
    while(num > 9) //Rule to stop once our answer is one digit
    {
        while(val > 0) //Rule to stop once you add the last digit
        {
            sum += (val % 10); //Adds the lowest digit
            val = val / 10; //Removes the digit we just added, making the next digit the new "lowest"
        }
        val = sum; //Used for adding digits
        num = sum; //Used to identify when we have reached a single digit answer
        sum = 0;    
    }
    return val;
}

int main()
{
    std::cout << addDigits(38);
}

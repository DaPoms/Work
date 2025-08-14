#include <iostream>
#include<iostream>
using namespace std;

string largestGoodInteger(string num) //This approach I learned of from other examples, much more consise, and a little bit more memory efficient
{
    char maxDigit = ' ';
    for(int i{0}; i < num.size() - 2; i++)
    {
        if(num[i] == num[i + 1] && num[i + 1] == num[i + 2])
            maxDigit = max(num[i], maxDigit);
    }
    if(maxDigit == ' ')
        return "";
    return string(3, maxDigit); //Also learned this constructor for creating a string with the same char
}
/* string largestGoodInteger(string num) 
{
    int maxGood{-1};
    char uniqueDigit{'\0'};
    int uniqueDigitCount{0}; //unique digit must == 3 in order to be a good integer
    for(int i{0}; i < num.size(); i++)
    {
        if(num[i] != uniqueDigit)
        {
            uniqueDigit = num[i];
            uniqueDigitCount = 1;
        }    
        else
            uniqueDigitCount++;
        
        if(uniqueDigitCount == 3) //Case of finding a good number
        {
            int goodVal = stoi(string() + uniqueDigit + uniqueDigit + uniqueDigit ); //This is a cool trick I learned for concatenating chars together
            if(goodVal > maxGood)
                maxGood = goodVal;
            uniqueDigitCount = 0;
        }
    }
    if(maxGood == 0) // two edge cases formed from the fact that I used maxGood as an int
        return "000";
    if(maxGood == -1)
        return "";
    return to_string(maxGood); 
}
 */
int main()
{
    cout << largestGoodInteger("118881222333");
}

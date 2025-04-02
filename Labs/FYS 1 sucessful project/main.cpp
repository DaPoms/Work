#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <ctime> //for seeding of randomness
int main() //solving by brute force
{
    system("CLS");
    std::string value{"0123456789"};
    int found = 0;
    unsigned long long num;
    while (found != 1)
    {
        //std::srand(time(NULL)); //manual seed setting for shuffle, optional
        std::random_shuffle(value.begin(), value.end()); 
        num = std::stoull(value); //decided to do a long long so I didn't have to worry about overflow, and unsigned to get even more digits as we know our # is not negative
        //std::cout << value << "\n"; //prints all numbers to make it look "cool"
        ////////ans = value;

        if( ( (num / 100000000) % 2) == 0) //tests for all the puzzle requirements
            if( ( (num / 10000000) % 3) == 0)
                if( ( (num / 1000000) % 4) == 0) 
                    if( ( (num / 100000) % 5) == 0) 
                        if( ( (num / 10000) % 6) == 0) 
                            if( ( (num / 1000) % 7) == 0) 
                                if( ( (num / 100) % 8) == 0) 
                                    if( ( (num / 10) % 9) == 0) 
                                        if( (num % 10) == 0) 
                                            {
                                            std::cout << "Winner!: " << value << '\n'; //prints winner when it fits the puzzle
                                            found++;
                                            }
                                            
        //answers found to the puzzle so far:
        /*
        3816547290
        */
        
       
    }
}

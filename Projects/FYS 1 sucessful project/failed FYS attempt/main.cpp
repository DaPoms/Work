/*
Assignment:

find a 10-digit positive integer abcdefghij such that
• a, b, c, d, e, f, g, h, i, j are distinct;
• a is divisible by 1;
• ab is divisible by 2;
• abc is divisible by 3;
• abcd is divisible by 4;
• abcde is divisible by 5;
• abcdef is divisible by 6;
• abcdefg is divisible by 7;
• abcdefgh is divisible by 8;
• abcdefghi is divisible by 9; and
• abcdefghij is divisible by 10.
*/

#include <iostream>

int main() //solving by brute force
{
    system("CLS");
    int value{1000000000};
    int ans{};
    

    while (value < 9999999999)
    {
        std::cout << value << "\n";
        ////////ans = value;

        if( ( (value / 100000000) % 2) == 0)
            if( ( (value / 10000000) % 3) == 0)
                if( ( (value / 1000000) % 4) == 0) 
                    if( ( (value / 100000) % 5) == 0) 
                        if( ( (value / 10000) % 6) == 0) 
                            if( ( (value / 1000) % 7) == 0) 
                                if( ( (value / 100) % 8) == 0) 
                                    if( ( (value / 10) % 9) == 0) 
                                        if( (value % 9) == 0) 
                                            {
                                            std::cout << "Winner!: " << value;
                                            break;
                                            }
                                            
               
        value++;
    }
            

   
}




#include <iostream>

int TOTAL{0};
int BOTTOMTOTOP{0};
void recursivelyAdd(int end)
{
    while(TOTAL != end)
    {
        TOTAL++;
        
        recursivelyAdd(end);
        //Anything under is printed from the base case first up
        
        std::cout << BOTTOMTOTOP++ << "\n";
    }
}

int main()
{
    recursivelyAdd(100);
    std::cout << TOTAL;
}

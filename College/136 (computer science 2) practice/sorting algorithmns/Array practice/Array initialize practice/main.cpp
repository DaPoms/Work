#include <iostream>

int main()
{
    int listLiteral[4][4] {
        {1,2,3,4},
        {1,2,3,4},
        {1,2,3,4},
        {1,2,3,4} 
    };

    for (int r{0}; r < (sizeof(listLiteral) / sizeof(listLiteral[0])); r++)
    {
        for (int c{0}; c < (sizeof(listLiteral[0]) / sizeof(int)); c++) 
        {
            std::cout << listLiteral[r][c] << " ";
        }
        std::cout << '\n';
    }

}

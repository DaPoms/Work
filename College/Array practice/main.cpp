#include <iostream>


//int arrayReader(int array[][]) //still figuring out how to put a 2d array in a function, will come back to fix it!


/* //ASK
void fillMatrix(int array[][]) //I decided to not port over row and col vars to 
//instead discover how to find row + col of an array without the knowledge of it, but this is not efficient, only done for learning purposes
{
    for (int r ; r < sizeof(array) / sizeof(array[0]) ; r++) //Nested for loop (taught in APCSA) to traverse an array/matrix
        {
            for (int c ; c < sizeof(array[0]) / sizeof(int); c++)
            {
                std::cout << "What do you want to put in row " << sizeof
            }

        }
}

*/

int main()
{
    system("CLS");

    std::cout << "Enter how many rows you want: ";
    int row{};
    std::cin >> row;

    std::cout << "Enter how many collumns you want: ";
    int col{};
    std::cin >> col;

    int testArray[row][col];

    
    for (int r{0} ; r < row ; r++) //Nested for loop (taught in APCSA) to traverse an array/matrix
        {

            for (int c{0} ; c < col ; c++)
            {
                std::cout << "What int do you want to put in row [" << r << "], column [" << c << "]? : ";
                std::cin >> testArray[r][c];
                //std::cout << '\n';
            }

        }

    std::cout << "-------------------------\n";

    for (int r{0} ; r < row ; r++) //Nested for loop (taught in APCSA) to traverse an array/matrix
        {
            for (int c{0} ; c < col ; c++)
            {
                std::cout << testArray[r][c] << " ";
            }

            std::cout << '\n';

        }
    
}

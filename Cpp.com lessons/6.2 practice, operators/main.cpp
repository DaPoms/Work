#include <iostream>

int main()
{
    system("CLS"); //cosmetic code


    std::cout << "Enter a number: ";
    int num{};
    std::cin >> num;
    
    //shows various implementations of arithmetic operator
    std::cout << "\nThis is unary operator + --> " << "+num = " << +num; //makes positive (redundant)
    std::cout << "\nThis is binary operator + --> " <<  " num + 1 = " << (num + 1); //adds two values together
    std::cout << "\n\nThis is unary operator - --> " << "-num = " << -num; //makes negative 
    std::cout << "\nThis is binary operator - --> " << "num - 1 = " << (num - 1); //subtracts 2 values together

    std::cout << "\nThis is binary operator * --> " << "num * 2 = " << (num * 2); //multiplies 2 values together
    std::cout << "\nThis is binary operator / --> " <<  "num / 2 = " << (num /2); //divides 2 values from left to right
    std::cout << "\nThis is binary operator / with a float --> " <<  "num / 2.0 = " << (num / 2.0); //divides 2 values from left to right
    std::cout << "\nThis is binary operator % --> " << "num % 3 = " << num % 3; //returns the remainder of the left value divided by the right

    std::cout << "=============================\n\n";

/////////////////////////////////////////////////////

std::cout << "Static cast to double of 2 int division: 5/3 = " << (static_cast<double>(5)/3) << '\n';
// any of the above operators with the '=' sign after it will assign the variable with the value resulting by the binary operator
num *= 5;
std::cout << "*= demonstration: " << num;






    

    
    
    
}

#include <iostream>
#include <string> //allows string class
int main()
{


    system("CLS");
    std::string name {};

    std::cout << "What is your full name name?: ";
    std::getline(std::cin >> std::ws , name );


    std::cout <<"\nEnter your age: ";
    int age{};
    std::cin >> age; 

    std::cout << "\nYour age + length of name is: " <<  (age + std::ssize(name) );
}


#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
int main()
{
    std::string placeholder;
    std::ifstream extract{"text.txt"};
  
    extract >> placeholder;
    std::cout << placeholder << "\n";
    extract.close(); //closing stops on position before hand

    extract >> placeholder;
    std::cout << "This is the closed one: " << placeholder;
}

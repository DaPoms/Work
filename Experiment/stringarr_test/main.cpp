#include <iostream>
#include <string>

int main() //Test of new behavior I learned about strings
{
    std::string arr[3]{"apple","pear","pineapple"};
    
    std::cout << arr[2][3]; //should print "e"
}

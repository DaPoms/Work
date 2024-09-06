#include <fstream> //for I/O stream
#include <iostream>
#include <string>
int main()
{
    std::string pl{};
    std::ifstream extract{"userInput.txt"}; //a variable of input stream type // does extract return 0 if it can't access the file?

    if (!extract) //how does this work?, doing cout extract does not print 0...
    {
        std::cerr << "File could not be found!"; //It is a standard to use cerr for errors
        return 1;
    }
    extract >> pl; //acts as a cin but from the input file
    std::cout << pl; // << takes one element at a time, ignoring whitespace
    
        
}

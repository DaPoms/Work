#include <fstream> //for I/O stream
#include <iostream>
#include <string>
int main()
{
    /////////////////////////////////////////
    /*  Use:  Used to reset file from      */
    /*             previous run            */
    /////////////////////////////////////////
    std::ofstream output{"userInput.txt"}; 
    output << "Glorbert 25 50.25\nBlorbert 89 81.3\nMorberte 148 32.5";
    output.close(); //Update: You can indeed only have 1 stream at a time, and have to close the previous one to do the next
    
    /////////////////////////////////////////

    std::string pl{};
    int num{};
    float decimal{};
    std::ifstream extract{"userInput.txt"}; //a variable of input stream type // does extract return 0 if it can't access the file?

    if (!extract) //how does this work?, doing cout extract does not print 0...
    {
        std::cerr << "File could not be found!"; //It is a standard to use cerr for errors
        return 1;
    }
    extract >> pl; //acts as a cin but from the input file
    std::cout << pl << '\n'; // << takes one element at a time, ignoring whitespace

    extract >> num; //acts as a cin but from the input file
    std::cout << num << '\n'; // << takes one element at a time, ignoring whitespace

    extract >> decimal; //acts as a cin but from the input file
    std::cout << decimal << '\n'; // << takes one element at a time, ignoring whitespace

    //ifstreams do collect any data type in the file!

    ////////////////////////////Below is a test of replacing text of separate file + reopening a closed stream

    
    
    output.open("userInput.txt");
    output << "Woah I'm in userInput.txt!!!";
        
}

#include <iostream>
int main()
{
    std::string* myPtr;
    std::string text{"Hello world!"};

    std::cout << "Memory address: " << &text << "\n";
    myPtr = &text; //& retrieves address of said variable
    std::cout <<"Should be same thing as above: " << myPtr << "\n\n";

    std::cout << "Whats stored in the variable: " << text << "\n"; // *pointer dereferences a pointer to whatever its pointing at (NOTE: It can even derefrence to another pointer if it was set on its address, if that pointer was pointing to the desired object/variable, then do **pointer)
    std::cout <<"Should be same thing as above: " << *myPtr;
}

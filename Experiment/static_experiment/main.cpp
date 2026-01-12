#include <iostream>
#include "staticTest.h"
int main()
{
    hasStaticInside(); //lesson: make helper functions static!
    StaticClass myObj;
    myObj.printAll(); // woah it works!!!
    StaticClass::printAll(); // woah because printAll() is static it also works with this! (note the requirement of the scope resolution)
}
        
#include <iostream>
#include "staticTest.h"

void printTest(){ std::cout << "Yoo!"; }
//theres no reason to include a static in the .h file as the definition is here and static means no other file gets this definition.
static void staticMessage(){ std::cout << "I'm ecstatic that I'm static!\n"; } // this one throws an error in main as static prevents a function from being inherited with #include
void hasStaticInside() {staticMessage();}

int StaticClass::stat1 = 20; // note the VERY WEIRD syntax of having to define the type 
                               //of the var you already set in the class declaration (in the .h). This is because the .h only declared that such a static int existed, so we have to create it ourselves
int StaticClass::stat2 = 3; //declaration syntax of static var
void StaticClass::printAll() 
{
    std::cout << stat1 << " " << stat2 << '\n';
    stat1 += 3; //note that these changes apply globally as there is only one instant of stat1 and stat2 for the entire StaticClass
    stat2 += 2;
} //because printAll() is a static function, nonStat CANNOT be used
// void StaticClass::printAll() {std::cout << nonStat;} //non static works fine (of course)

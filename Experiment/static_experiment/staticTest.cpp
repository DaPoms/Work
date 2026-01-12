#include <iostream>
#include "staticTest.h"

void printTest(){ std::cout << "Yoo!"; }
//theres no reason to include a static in the .h file as the definition is here and static means no other file gets this definition.
static void staticMessage(){ std::cout << "I'm ecstatic that I'm static!"; } // this one throws an error in main as static prevents a function from being inherited with #include
void hasStaticInside() {staticMessage();}

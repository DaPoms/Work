#include <string>
#include <string_view>
#include <iostream>


void test(std::string_view x) //testing an error I get from my CodeRunner extension where it doesn't 
//run the #include 's for some reason 
{
    std::cout << x;
}

int main()
{
    std::string_view x{"Hello world!"};

    test(x);
}

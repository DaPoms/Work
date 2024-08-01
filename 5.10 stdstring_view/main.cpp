#include <iostream>
#include <string_view> //allows string_view functionality
#include <string>



/*  USING std::string_view
void stringPrinter(std::string_view x) // This lesson is about efficiently using strings, as every time you call this function without using stirng_view,
//the function would have to be initialized and then deleted at the end of the function EACH time



{
    std::cout << x;
}

int main()
{
    std::string_view x{"Hello World! (but efficiently)"}; 
    
    stringPrinter(x);
}

*/


//--------------------------------------------------------//

//how to allow conversion from string_view to string


void stringPrinter(std::string x) 
{
    std::cout << x;
}

int main()
{
    using namespace std::string_literals; //allows suffix of s  (string)
    using namespace std::string_view_literals; //allows suffix of sv (string_view)

    
    std::string_view x {"Hello Worlds!\n"sv}; //sv makes the literal string_view, not purpose here but just to show it off

    stringPrinter(static_cast<std::string>(x));

    constexpr std::string_view con {"I can't change!"}; //Using a constexpr allows compile-time replacement --> making code repeat uses of 'con' more efficient 

    std::cout << con;

}

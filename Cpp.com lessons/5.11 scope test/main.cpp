#include <iostream>
#include <string>
#include <string_view>

int main()
{
    system("CLS");


    std::string_view x {};

    { //nested block (Makes a separate scope here)
        std::string del{"Undefined behavior\n"};
        x = del;
    } //end of scope for del
 std::cout << x; //going to be undefined behavior due to x's object it was viewing being deleted

//--------------------------- Testing std:;view text modification -----------------//

    std::string_view y{"12345"};
    std::cout << y << '\n';

    y.remove_prefix(2); //Lesson: remove_(pre/suff)ix functions actually modify the std::string_view var
    std::cout << y << '\n';

    y.remove_suffix(2); 
    std::cout << y << '\n';
   
}

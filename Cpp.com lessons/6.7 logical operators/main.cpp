#include <iostream>

int main()
{
    int x{5};
    int y{3};
    std::cout << ( !(x == y) ) << '\n'; //not operator, flips true to false and the inverse.
    std::cout << ( (x == y) || (x + y == 8) ) << '\n'; //or statement, at least one must be true for true output
    std::cout << ( (x != y) && (x + y == 8) ) << '\n';  //and statement, both must be true for true output

    bool a{true};
    bool b{false};
    std::cout << (a != b) << '\n'; //xor for bools, true only when 1 var is true
    std::cout << ( (5 < 3) != (3 < 5) ) << '\n'; //Xor works fine as long as statements breaks down to bools

    std::cout << ( (x == 3) != (y == 3) ) << '\n';

    std::cout << ( (x > 3) and ( y == 3) ); //you can use words too (and, or, not), though its a little bit harder to read
}

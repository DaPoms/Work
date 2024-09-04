#include <iostream>
#include <bitset>

int main()
{
    //using [[maybe_unused]] constexpr int (var) allows you to define what indexes are for what behavior in a bitstring!!!!!!!



    system("CLS");

    std::bitset<8> bit{0b0000'1011}; //reminder that you can use ' as spaces to make bool literals more readable 
    
    ///printing bitstrings////

    std::cout << "Bitstring: " << bit << '\n' ; //Use this to print bitsets out (NOT in decimal)
    std::cout << "Decimal value of bitstring: " << bit.to_ulong() << "\n-----------------\n" ; //0b prefix makes literal a bool, allows printing decimal val of bitstring,
    // but to_ulong is required to convert a bitset var to decimal
    ////bitset manipulators///

    std::cout << "status of first bit in bitstring: " << bit.test(0) << '\n'; //all of the bitset manipulators return the var used.
    std::cout << "Bitset with 4th value reset: " << bit.reset(3) << '\n'; //first bit is on index 0, not 1
    std::cout << "Bitset with 8th value set: "  << bit.set(7) << '\n';
    std::cout << "Bitset with 3rd value flipped: "  << bit.set(2) << "\n\n";


    ////////////
     std::cout << "Size of bitset: "  << bit.size() << '\n';
     std::cout << "# of true's or 1's in bitset: "  << bit.count() << '\n';
     std::cout << "Are all bits true?: "  << bit.all() << '\n';
     std::cout << "Is there at least one true bit?: "  << bit.any() << '\n';
     std::cout << "Are no bits true?: "  << bit.none() << '\n';








}

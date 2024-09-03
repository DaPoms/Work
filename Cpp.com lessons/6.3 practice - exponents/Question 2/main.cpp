#include <iostream>
#include <typeinfo> //used to test how types change with ! operator
constexpr bool isOdd(int x) //if false even
{
    std::cout << "! converts int to: " <<  typeid( !((x % 2)) ).name() << '\n'; //as shown, type changes from int to bool when using operator!
                                                                                //note to self, do !! to convert something to bool without changing the result if needed
    return !((x % 2)); //when even we get 0 and it is converted to a bool, so !0 = 1, when the number is not 0, 
}

int main()
{
    std::cout << "Give an integer: ";

    int x{};
    std::cin >> x ;

    

    if (isOdd(x))
        std::cout << x << " is even.";



    else
        std::cout << x << " is odd.";
}

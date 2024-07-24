#include <iostream>


double askRadius()
{
    double r{};
    std::cout << "Give the radius of your circle: ";
    std::cin >> r;

    return r;
}

double calcCircumfrence()
{
 const double pi{3.14159};

 return 2 * pi * askRadius(); //Formula for circumfrence

}


int main()
{
    system("CLS");

   std::cout << calcCircumfrence();    
}

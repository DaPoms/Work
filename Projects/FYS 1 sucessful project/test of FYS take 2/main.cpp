#include <iostream>
#include <algorithm>
int main()
{
std::string numbList{"012345678"};

for (int i; i < 3 ; i++ )
{
std::random_shuffle(numbList.begin(), numbList.end()); //testing shuffle functionality
std::cout << numbList << '\n';

std::stoi(numbList); //we are having trouble with this, out of range error

std::cout << numbList;
}

}

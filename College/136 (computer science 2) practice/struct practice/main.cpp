#include <iostream>

struct myStruct
{
    int num{-1};
};

void setNum(myStruct& passedStruct ,const int& passedNum) //Only useful when your struct has lots of member variables
{
    passedStruct.num = passedNum;
}

int main()
{
    myStruct str{};
    setNum(str, 4);
    std::cout<< str.num;
}

#include <iostream>

double getDouble()
{
    double x{};

    std::cout << "Enter a double value: ";
    std::cin >> x;

    return x;
}

char getOperator()
{
    char op{};
    std::cout << "Enter +, -, *, or / : ";
    std::cin >> op;

    return op;
}

void calcDouble(double x, double y, char op)
{
    if (op == '+')
        std::cout << x << " + " << y << " is: " << x + y;

    else if (op == '-')
        std::cout << x << " - " << y << " is: " << x - y;

    else if (op == '*')
        std::cout << x << " * " << y << " is: " << x * y;

    else if (op == '/')
        std::cout << x << " / " << y << " is: " << x / y;

    else //added operator check here too, in case a programmer were to directly input the wrong value
        return;
}

int main()
{
    system("CLS"); //Makes terminal pretty, ignore

    double x{ getDouble() };
    double y{ getDouble() };

    char op {getOperator()};
    

    calcDouble(x, y, op);


    
}

#include <stdio.h>
double calculate(double leftOperand, char operation, double rightOperand)
{
    if(operation == '+')
        goto add;
    else if (operation == '-')
        goto subtract;
    else if (operation == '*')
        goto multiply;
    else if (operation == '/')
        goto divide;
    else 
        return -1; //error case

    add:
        return leftOperand + rightOperand;
    subtract:
        return leftOperand + rightOperand;
    multiply:
        return leftOperand * rightOperand;
    divide:
        return leftOperand / rightOperand;
       
}

int main()
{
    float leftOperand, rightOperand;
    char operation;
    printf("Type what you want to calculate (format: double operationSymbol double):");
    scanf("%f %c %f", &leftOperand, &operation, &rightOperand);
    printf("Answer: %f\n", calculate(leftOperand, operation, rightOperand));
}

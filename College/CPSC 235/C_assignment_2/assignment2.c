/*******************************************************************/
/* Author: Daniel Tripoli                                          */
/* Filename: assignment2.c                                         */
/* Creation Date: October 1, 2025                                  */
/* Last Modified: October 1, 2025                                  */
/* Due Date: October 4, 2025                                       */
/* Course: CPSC235-010                                             */
/* Professor Name: Professor Jacklitsch                            */
/* Assignment: Total Bill Calculator                               */
/* Purpose: Demonstrate understanding of if and goto by simulating */
/*          the behaviour of proper conditionals and loops         */
/*******************************************************************/
#include <stdio.h>
int main()
{
    printf("Welcome to the bill calculator!\nEnter how many items were purchased: ");
    int count = -1;
    float price;
    int loops = 1;
    float billSum = 0;

    
    askCountAgain:
        scanf("%d", &count);
        if(count >= 0)
            goto nextStep;
        
        printf("%s", "Number of items purchased cannot be negative, try again: ");
        goto askCountAgain;

    nextStep: //jumps out of negative value case to make sure error text does not print
        if(count == 0) //special case
            goto zeroAns;
    
    askPriceAgain:
        printf("Enter the price of item %d: ", loops);
        scanf("%f", &price);
        loops++;
        if(price >= 0)
            goto nextItem;
        //negative number case
        printf("%s", "Price cannot be negative\n");
        loops--; //sorta inefficient but its works!
        goto askPriceAgain;
    nextItem: //jumps out of negative value case to make sure error text does not print
        billSum += price;
        if(loops <= count)
            goto askPriceAgain;
        
        zeroAns:
        printf("The total bill is $%.2f.", billSum); //This is another way to format printf
        

}

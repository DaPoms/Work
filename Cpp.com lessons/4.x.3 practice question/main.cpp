#include <iostream>

double getHeight()
{
    double x{};
    std::cout << "Enter the height of the ball in meters: \n";
    std::cin >> x;

    return x;

}

double calcHeight(double init, int time) //gives new height of ball after given seconds
{

    double end{init - ( ((time * time) / 2.0 ) * 9.8) };

    if(end < 0)
        return 0.0;

    else
        return end;

    
}

void calcAndPrintHeight(double init, int time)
{


    double current{ calcHeight(init, time) }; //current = current Height

    if (current < 0.0)
        std::cout << "\nAt " << time << " seconds, the ball is on the ground.";
    
    
    else
       std::cout << "\nAt " << time << " seconds, the ball is at a height of: " << current << " meters.\n";
}


int main()
{
    system("CLS");

    double init{ getHeight() };

    calcAndPrintHeight(init, 0);
    calcAndPrintHeight(init, 1);
    calcAndPrintHeight(init, 2);
    calcAndPrintHeight(init, 3);
    calcAndPrintHeight(init, 4);
    calcAndPrintHeight(init, 5);
    




}


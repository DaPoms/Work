#include <iostream>
#include <string>
struct plant
{
    std::string name;
    std::string color;
    int yearsAlive;
};

plant createPlant(std::string passedName, std::string passedColor, int passedYearsAlive)
{
    plant plantEntity;
    plantEntity.name = passedName;
    plantEntity.color = passedColor;
    plantEntity.yearsAlive = passedYearsAlive;

    return plantEntity;
}

void printPlant(plant plantEntity)
{
    std::cout << "Name: " << plantEntity.name << "\nColor: " << plantEntity.color << "\nYears alive: " << plantEntity.yearsAlive;
}

int main()
{
    plant tree{"Coniferous", "yellow", 5};

    printPlant(tree);
}

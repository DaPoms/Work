#include "dog.h"
#include <iostream>



int main()
{
    dog animal{"Borbert", "Mastiff", 'M', true, gigantic};
    dog puppy(animal);
    
    puppy.printDog();
    std::cout << "\n================\n";
    animal.printDog();


}

///////dog class////////////////////////////////////////////////////////////////
dog::dog() //Why do you needd this if you can do default vars
{

    name = "NULL";
    breed = "NULL";
    sex = 'N';
    isCute = false;

}

dog::dog(std::string nameInput, std::string breedInput, char sexInput , bool isCuteInput, size sizeInput)
{
    name = nameInput;
    breed = breedInput;
    sex = sexInput;
    isCute = isCuteInput;
    dogSize = sizeInput;
}

dog::dog(const dog& passedReference) //copy constructor
{
    name = passedReference.name;
    breed = passedReference.breed;
    sex = passedReference.sex;
    isCute = passedReference.isCute;
    dogSize = passedReference.dogSize;
}

dog::~dog()
{}

std::string dog::getName()
{
    return name;
}

void dog::setName(std::string passedName)
{
    name = passedName;
}

std::string dog::getBreed()
{
    return breed;
}

void dog::setBreed(std::string passedBreed)
{
    breed = passedBreed;
}

char dog::getSex()
{
    return sex;
}

void dog::setSex(char passedSex) //Debating whether to call input "passed" or "Input"
{
    sex = passedSex;
}

bool dog::getCute()
{
    return isCute;
}

void dog::setCute(bool passedIsCute)
{
    isCute = passedIsCute;
}

void dog::printDog()
{
    std::string sexTranslate{};
    std::string size{};

    if((sex == 'm') || (sex == 'M') )
        sexTranslate = "Male";
    else if((sex == 'f') || (sex == 'F') )
        sexTranslate = "Female";

    switch(dogSize) //first time doing switches
    {
        case 1: size = "Tiny";
        
        case 2: size = "Small";

        case 3: size = "Medium";

        case 4: size = "Large";

        case 5: size = "Gigantic";
    }
        
    std::cout << "Name: " << name 
              << "\nBreed: " << breed
              << "\nSex: " << sexTranslate
              << "\nIs " << name << " cute?: " << std::boolalpha << isCute //boolalpha makes bools true/false
              << "\nSize: " << size;
}


#include <iostream>

#ifndef DOG_H
#define DOG_H

//enum test
enum size {tiny, small, medium, large, gigantic}; //will allow these enum vals to be attributed to # values in whatever file includes dog.h, can lead to naming conflicts

class dog
{
    public:
        dog();

        dog(std::string name, std::string breed, char sex , bool isCute, size sizeInput );

        ~dog();

        std::string getName();

        void setName(std::string dogsName);

        std::string getBreed();

        void setBreed(std::string dogsBreed);

        char getSex();
        
        void setSex(char passedSex);

        bool getCute();

        void setCute(bool passedIsCute);

        void printDog();
       
    private:

        std::string name;

        std::string breed;

        char sex;

        bool isCute;

        size dogSize;
};

#endif

#include <map>
#include <iostream>
#include <string>
//This experiment is about a new structure I learned about, dictionaries/maps! 
//They are very nice for storing pairs and searching said pairs, as the left term of the pair is used in the [] call to automatically find the pair
//Parts: Key and value (key is what you use in myMap[key], but the return of that call is the value. EX: Lets say theres a pair: 1,2 in myMap. myMap[1] returns 2)

class myClass
{
    private:
        int num;
        std::string name;
    public:
        myClass(int passedNum = 0, std::string passedName = "") : num{passedNum}, name{passedName}{}

        bool operator<(const myClass rightObj) const
        {
            if(num < rightObj.num)
                return true;
            else    
                return false;
        }
};

struct myStruct
{
    std::string name{" "};
    int count{0};

    bool operator<(const myStruct rightObj) const
    {
        if(count < rightObj.count)
            return true;
        else
            return false;
    }

    friend std::ostream& operator<<(std::ostream& os, myStruct rightObj)
    {
        std::cout << rightObj.name << " " << rightObj.count << '\n';
        return os;
    }
};

int main()
{
    myStruct s{"bob", 2};
    std::map<int, myStruct> myMap1{}; //Creates a map with int as key
    myMap1[50] = s; //Similar to array synax, you specify which index, which in the case of maps, is the key term, then assign the value to that key/index.
    std::cout << myMap1[50].name << '\n';
 
    std::map<myStruct, int> myMap2{}; //Creates a map with a struct as key
    myMap2[s] = 1000;
    std::cout << myMap2[s] << '\n';
 
    std::map<myClass, int> myMap3{ {myClass(5,"bob"), 4} };
    std::cout << myMap3[myClass(5,"bob")] << '\n'; //Tada! 

    std::cout << '\n' << (myMap3.find(myClass(5,"bob")) != myMap3.end());
    std::cout << '\n' << (myMap3.find(myClass(20,"")) != myMap3.end());

    std::map<myClass, int> myMap4;
    std::cout << '\n' << (myMap4.find(myClass(20,"")) == myMap4.end()); //should be true
}


//The one thing I learned is having a struct as a key is troublesome due to it the functionality required to behave as a key. You'd have to 
//Add the operator overload for the operator<, but that is honestly easier to do for a class than a struct. Structs are fine values in maps though.

//NOTE: Operator overload of operator< must have const parameters

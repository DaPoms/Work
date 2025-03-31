#include <iostream>
//testing post const functionality. post const means that the function it is called on cannot change any member variable only INSIDE this function
class myClass
{
    private:
        int x;
        int y;

    public:
        myClass(int passedX, int passedY) : x{passedX}, y{passedY}{}; //Handy list initialization! I learned that if x or y were const, you'd have to do a list initialization as you can't change a const in compile time
        const int& getX() const {return x;} //Pre const must be added with referenced returns. I believe this is because the compiler won't allow you to return something that can change a member var, so a const is required to ensure it
        int getY() const {return y;} 
        //int getY(){return y;} //Breaks myTask as a post const function requires all the function calls in it to also be post const
        int myTask() const { return getX() + getY(); }
};

int main()
{
    myClass myObj{5,4};
    std::cout << myObj.myTask() << '\n';
    std::cout << myObj.getX() + myObj.getY() << '\n';
   
}

//Lesson: Post const will also make sure that the value returned from the function is not capable of changing a member variable. Thus if you return by reference, &, you must
        //declare it as const. Now if you're returning a non member variable, then it doesn't care. Thats why getter functions are allowed in my case, with int y, as it creates
        //a separate instance of that object and const int& x as it is passed explicitly as const. Now, the object's private variable cannot actually be changed. post const functions can only use other post const functions

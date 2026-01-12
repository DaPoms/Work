#ifndef STATICTEST_H
#define STATICTEST_H

class StaticClass
{
    private:
        int nonStat{32};
        static int stat1; // I can see static variables being very good in keeping track of all the objects being used, such as tracking the objectCount, or the count of a specific funtion call, essentially any cross/object statistic
                          //Far better than global vars in terms of this purpose
        static int stat2; // apparently static variables are not a part of the actual class, its just a part of the scope, and the scope is this class, which means it applies to ALL objects (could be useful for )
    public:
        static void printAll(); // static cannot be declared in the implimentation file
    
};





void printTest();
//static void printTest();  // this one throws an error in main as static prevents a function from being inherited with #include
void hasStaticInside();






#endif

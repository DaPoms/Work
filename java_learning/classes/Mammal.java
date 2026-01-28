public class Mammal
{
    String name;
    int age; //age is in years
    int height; // height is in inches

    void timePass(int i)
    {
        int yearsPassed = i / 365;
        age += yearsPassed;
        height += Math.random() * 10 * (yearsPassed / 2); //apparently the math library is imported by default. This implies the mammal can increase height for forever!
        System.out.println(yearsPassed + " years have passed.");
    }

    void describe()
    {
        System.out.println("The " + name + " is " + age + " years old, standing at " + height + " inches tall");
    }

}

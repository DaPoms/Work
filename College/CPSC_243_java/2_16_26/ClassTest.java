
class MyClass
{
    public int myInt;

    MyClass()
    {myInt = 0;}

    MyClass(int myInt)
    {this.myInt = myInt;}
}

public class ClassTest
{
    public static void main(String[] args)
    {
        MyClass test = new MyClass();
        MyClass test2 = new MyClass(5);
        System.out.println(test.myInt);
        System.out.println(test2.myInt);
        OtherClass test3 = new OtherClass();
        System.out.println(test3.myString);

    }
}

import java.util.Arrays;
import java.util.Scanner;
class Doo
{
    int i1;
    int i2;
    String s1;

    Doo(int i1,int i2,String s1){this.i1 = i1; this.i2 = i2; this.s1 = s1;}
    Doo(int i1, int i2) { this(i1,i2,"NULL"); }
    Doo(int i1) { this(i1, -1,"NULL"); }
    Doo() { this(-1,-1,"NULL");}

    public String toString()
    {
        return "" + i1 + " " + i2 + " " + s1;
    }
}


class Foo
{
    public static void alterPassByVal(int[] lst)
    {
        lst = new int[]{1,2,3}; // should do nothing to the lst that was passed, as passing by value means that the parameter in the call is not changed
    }

    public static int sum(int acc, int... nums) // note that the variable length argument MUST be the last element, which means only 1 allowed
    {
        for(int num : nums)
            acc += num;

        return acc;
    }

    int fault = 1; // data field / attribute for type Foo

    public static void main(String[] args) 
    {
        // Demonstration of pass by value impacts
        int[] myArr = {5,5,5,5};
        alterPassByVal(myArr);
        System.out.println(Arrays.toString(myArr));

        //Variable arguments example
        int[] nums = {1,1,2,1};
        System.out.println("Sum of array: " + sum(0, nums));
        System.out.println("Sum of elements that get turned into an array: " + sum(0, 5,5,5,5,5));

        Doo myDoo = new Doo(1);
        System.out.println(myDoo);
        myDoo = new Doo(2,2);
        System.out.println(myDoo);
        myDoo = new Doo(4,4, "Bob");
        System.out.println(myDoo);

        //static workaround demonstration
        Foo myFoo = new Foo();
        System.out.println(myFoo.fault);
        // static functions cannot access nonstatic values from outside. This would throw an error:
        // System.out.println(fault)


        int x = 5;

        //switch example
        switch(x % 2)
        {
            case 0  -> {System.out.println(x + " is even");}
            default -> {System.out.println(x + " is odd");}
        }

        //Ternary operator example
        String s = (x % 2 == 0) ? "even" : "odd";
        System.out.println("Not to be repetitive guys, but I think " + x + " is " + s);
        
        //Narrowing conversion
        int y = (int)3.24;
        System.out.println(y);
        //Conversion of int to string
        System.out.println(String.valueOf(y));
        System.out.println(Double.parseDouble(String.valueOf(y)) + x); //very pointless flip between int -> string -> int 

        //input
        Scanner scan = new Scanner(System.in);
        System.out.println("Returned single string (as in no whitespace inbetween): " + scan.next());
        scan.nextLine(); // flush
        System.out.println("Returned full input string : " + scan.nextLine());
        System.out.println("This better be a int or ima throw an error! : " + scan.nextInt());


        

    }
}

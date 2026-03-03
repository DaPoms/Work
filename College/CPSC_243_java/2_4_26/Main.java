import java.util.Scanner; 
public class Main {
    public static void main(String[] args)
    {
        System.out.println("Enter a # between 1-10 : ");
        Scanner cin = new Scanner(System.in);

        int val = cin.nextInt();

        switch(val)
        {
            case 1,3,5,7,9 -> System.out.println(val + " is odd");
            case 2,4,6,8,10 -> System.out.println(val + " is even");
            default -> System.out.println(val + " is not within the range");
        }

        System.out.println(val % 2 == 0 ? val + " is even" : val + " is odd"); //one liner with better behavior than the above

    }
}

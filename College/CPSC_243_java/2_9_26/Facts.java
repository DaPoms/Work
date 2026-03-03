import java.util.Scanner;
class Facts {

    static int factorial(int x)
    {
        if(x == 0) return 1;
        return x * factorial(x-1);
    }
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);
        int val = cin.nextInt();
        System.out.format("The value of %d! is: %d", val, factorial(val)); // 3 * 2 * 1
    }
    
}

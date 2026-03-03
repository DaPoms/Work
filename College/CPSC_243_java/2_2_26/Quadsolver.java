import java.util.Scanner;
public class Quadsolver
{
    public static void main(String[] main)
    {
        int a, b, c;
        Scanner cin = new Scanner(System.in);
        System.out.println("Please enter coefficient a:");
        a = cin.nextInt();

        System.out.println("Please enter coefficient b:");
        b = cin.nextInt();

        System.out.println("Please enter coefficient c:");
        c = cin.nextInt();

        double discriminant = Math.pow( (Math.pow(b,2) - (4 * a * c) ), 0.5);

        double zero1 = (-b + discriminant) / (2 * a);
        double zero2 = (-b - discriminant) / (2 * a); 

        System.out.printf("The zeroes of %dx^2 + %dx + %d are: %n and %n", a, b, c, zero1, zero2);

        System.out.printf("x = %f AND x = %f%n", zero1, zero2);
    }
}

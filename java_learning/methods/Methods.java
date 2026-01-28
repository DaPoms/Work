import java.util.Scanner;
public class Methods {
    static int addInput() // note due to the .nextInt() only accepting ints, this throws an error if the user misinputs (this would require error handling or a for loop to repeat the input, with the input being .nextLine() to allow for handling instead of nextInt())
    {
        System.out.println("Enter the 2 integers that you want to be added:");
        Scanner cout = new Scanner(System.in); // creating a new stream via a function call guarantees passthrough cannot occur, but theres also easy ways to avoid passthrough issues
        return cout.nextInt() + cout.nextInt(); // you can do cool input reading like this unlike c++ (cin >> var does not return var, rather it returns 'cin'/ the input stream to allow for chaining) 
    }
    public static void main(String[] args)
    {
      System.out.println("Your answer is: " + addInput());
      Scanner cout = new Scanner(System.in);
      var test = cout.nextInt();
      var test2 = cout.nextInt(); // this does trigger a passthrough stream effect if the user enters more than requested at once (as the leftovers get put on the stream)
      System.out.println(test2);
    }
    
}

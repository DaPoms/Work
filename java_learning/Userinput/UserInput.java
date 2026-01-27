import java.util.Scanner;
public class UserInput
{
    public static void main(String[] args)
    {
        Scanner myObj = new Scanner(System.in);
        String adjective;
        do //forces the user to say they are stinky (how rude!) :C
        {
            System.out.println("Now what are you, say it!");
            adjective = myObj.nextLine();
        }
        while(!adjective.equalsIgnoreCase("stinky"));
        System.out.println("That's right, you are " + adjective);
    }

    
}

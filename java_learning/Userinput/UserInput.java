import java.util.Scanner;
public class UserInput
{
    public static void main(String[] args)
    {
        Scanner myObj = new Scanner(System.in); //Think of it as that we are scanning the system's input to store in myObj
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

public class Ifs
{
    public static void main(String[] main)
    {

        
        System.out.println( true ? 2 : 3); // compact if statement format (useful for using a function with an if statement or very simple ifs)
        System.out.println( false ? 2 : 3);

        // NESTED TERNARY???
        for(int i = 0; i < 3; i++)
        {
            String ans = (i == 0) ? "Hello!" // I sort of like this format, but I doubt many people know operator?
                    :    (i == 1) ? "Goodbye!"
                    :               "See you soon!";

            System.out.println(ans);
        }
    }


};

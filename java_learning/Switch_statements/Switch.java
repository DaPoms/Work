public class Switch
{
    public static void main(String[] args)
    {
        int num = 4;
        switch(num)
        {
            case 0: 
                System.out.println(0);
                break; // without breaks, every statement below the one if evaluates to will also be run
            case 1: 
                System.out.println(1);
                break;
            case 2: 
                System.out.println(2);
                break;
            case 3:
            case 4:
            case 5:
                 System.out.println("Yucky!"); 
            default: //default can be used as an "else" case
                System.out.println(-1);
            
        }

        //rule switch, much cleaner
        switch(num)
        {
            case 0 -> {
                System.out.println(0);
                System.out.println("I'm in a rule switch with more than 1 statement!");
            } //rule switches require brackets for multi statement cases
            case 1 -> System.out.println(1);
            case 2 -> System.out.println(2);
            case 3,4,5 -> System.out.println("This is the benefit of rule switches!"); // more readable multi case variant
            default -> System.out.println(-1);
            
        }
    }
};

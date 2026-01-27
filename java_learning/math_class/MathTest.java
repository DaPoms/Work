public class MathTest
{
    public static void main(String[] args)
    {
        int x = 2;
        int y = 4;
        System.out.println(Math.max(x,y));
        System.out.println(Math.min(x,y));
        System.out.println(Math.sqrt(4)); // sqrt returns double
        System.out.println(Math.abs(-2));
        System.out.println(Math.pow(x,y)); //returns as double
        double z = 3.51;
        System.out.println(Math.round(z)); //rounds up/down based on > 5 or < 5. Note that it returns type LONG
        System.out.println(Math.ceil(z)); //round up. Note it returns type double
        System.out.println(Math.floor(z)); //round down
        System.out.println(Math.random()); //by default return 0.0 - 1.0, thus we can manipulate this to get the random values we want
        System.out.println((int)(Math.random() * 100) ); // ex: this effectively does 0 - 100 random num generation
        
    }
}

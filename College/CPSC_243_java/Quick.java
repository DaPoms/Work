public class Quick
{
    static void modify(int x, Integer y)
    {
        x+=5;
        y+=5;
    }
    public static void main(String[] args)
    {
        int x = 10;
        Integer y = 10;
        modify(x, y);

        System.out.println(x + " " + y);
    }
}

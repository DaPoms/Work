public class Unicode
{
    public static void main()
    {
        int num = 0x1F60;
        String emoji = new String(Character.toChars(num));
        System.out.println(emoji);

    }
}

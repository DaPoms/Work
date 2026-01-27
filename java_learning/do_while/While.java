public class While
{
    public static void main(String[] args) {
    {
        int num = 3;
        int ans = num;
        int pow = 3;
        do // this is useful if we want to enforce doing something at least once even if the while statement is false
        {
            ans *= num;
            --pow;
        }
        while(pow != 1); // I see do while being my preferred format for asking user input (we ask once, but we keep on asking while user input is improperly formatted/wrong)

        System.out.println(ans);

        num = 3;
        ans = num;
        pow = 3;
        while(pow != 1) //this behaves the same as the above
        {
             ans *= num;
            --pow;
        }

        System.out.println(ans);
    }
    }
}

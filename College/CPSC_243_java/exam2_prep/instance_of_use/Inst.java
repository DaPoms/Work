

class PInst
{
    protected String data;

    PInst()
    {
        data = "";
    }  
    PInst(String data)
    {
        this.data = data;
    }    

    
/**
 * @author Daniel Tripoli
*   This is my beautiful test javadoc comments
*/
    public static void ambigFunct(Object x)
    {
        if(x instanceof PInst)
        {
            ((PInst) x).describeLength(); // See here, we change the DECLARED TYPE, not the ACTUAL type. Actual type is set at instantiation and CANNOT CHANGE (only way is to copy over values to a new object)
        }
    }

    void describeLength()
    {
        System.out.print("Super class states...");
        if(data.length() < 5) 
            System.out.println("Thats quite a small message there!");
        else if(data.length() > 2 && data.length() < 6) 
            System.out.println("Thats like... maybe a word?");
        else 
            System.out.println("You're getting quite big there buckaroo");
    }


}

public class Inst extends PInst{
    private String data;
    Inst(String data)
    {
        this.data = data;
    }    

    /**
     * This is my javaDocs test. Yes, it doesnt make sense for anything thats happening, I just wanted to play around with the format for the sake of memorizing 
     * @see <a href = "https://www.youtube.com/watch?v=dQw4w9WgXcQ"> Definitely NOT anything suspicious (do not click) </a>
     * @param myStr Type string. nothing is needed, I just said string for the sake of it. 
     * @throws RunTimeException when runnin to long, right? Thats totally what it means
     * @return The cool words that I really like
     * {@inheritDoc} <--- This inherits PInst's describe length java doc info IF it had any 
     */
    void describeLength()
    {
        System.out.print("Subclass states...");
        if(data.length() < 5) 
            System.out.println("Thats quite a small message there!");
        else if(data.length() > 2 && data.length() < 6) 
            System.out.println("Thats like... maybe a word?");
        else 
            System.out.println("You're getting quite big there buckaroo");
    }

    public static void main(String[] args)
    {
        Object a = new Inst("bob");
        Object b = new PInst("times are tough");
        ambigFunct(a);
        ambigFunct(b);
    }

}

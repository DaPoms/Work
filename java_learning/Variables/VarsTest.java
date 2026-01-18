public class VarsTest 
{
    public static void main(String[] args)
    {
        int x,y,z; // mass initialization
        x = y = z = 5;
        // mass declaration
        String myString = "Hi";
        int num = 2313;
        float deci = 1.12f; // f after num shows type float
        double dub = 123.123; //decimal literals are doubles by default (can hold 2 ^ 2n more values i.e. doubled amount of bits)
        boolean bool = true;
        char letter = 'c';
        final int favNum = 2; //final == const in c++
        byte lil = 52;
        byte biglil = (byte)2000;


        System.out.println(myString + " I am " + num + " years old and have $" + deci + " to my name. This is all " + bool);
        System.out.println("The number " + favNum + " and letter " + letter + " will forever be in my heart.");
        System.out.println(num + deci);
        System.out.println("Woah I'm different!: " + num + deci); //everything past a string is interpreted as a string
        System.out.println(x + " " + y + " " + z);
    }
    
}

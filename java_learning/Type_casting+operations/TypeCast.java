public class TypeCast // for some reason my running extension doesn't like a file name fof "TypeCasting.java" so I stuck with this. it keeps on compiling with the first letter being overcase (casusing an error) with the old name.
{
    public static void main(String[] args)
    {
        double num = 10.12;
        int num2 = 3;
        // int i = (int) num; // as shown, lossy conversions must be explicit (unlike c++, which gives a warning a does it anyways instead of an error for lossy conversion)
        //arithmetic operators
        System.out.println("I'm rounded down! " + (int) num ); // narrowing conversion must be done explicitly
        System.out.println( num + " + " + num2 + " = " + (num + num2) ); // prioritizes widening conversions (double over int)
        System.out.println(num + " + " + 10 + " = " + (num + 10) ); //notice the precision point error (the 1 at the end)
        System.out.println(num + " - " + 10 + " = " + (num - 10) ); //notice the precision point error (the 1 at the end)
        System.out.println(num + " * " + 10 + " = " + (num * 10) ); 
        System.out.println(5 + " / " + 10 + " = " + (5 / 10) ); // stays as type int
        System.out.println(5 + " / " + 10 + " = " + ( (double) 5 / 10) ); //requires casting to make a double
        System.out.println(num + " / " + 10 + " = " + (num / 10) ); 
        System.out.println(num + " % " + 10 + " = " + (num % 10) ); 
        System.out.println(num + "-- = " + (--num) ); //note that these are in place, it actually affects the variable the ++/-- operator is used
        System.out.println(num + "++ = " + (++num) ); 
        //asignment 
        int val = 2;
        val += 2; //theres also -= *= %= /= (all arithmetic). sets val to be equal to val + 2

        val <<= 2; //bitshifts left 2, effectively multiplying by 2^2 (4)
        System.out.println( (val >> 2) + " << 2 = " + val ); // in this case, 4 * 2^2 = 16
        System.out.println (val + " << 2 = " + (val >>= 2) ); // in this case, 16 / 2^2 = 4
        System.out.println(val);
        
        int i = 10;
        int c = 9;
        i &= c; //bitwise AND:
                /*  
                    i = 1010
                    c = 1001  AND
                    ----------------
                    1000 = 8
                    
                */
        System.out.println(i);
        // and so on, with | being bitwise OR, ^ being bitwise XOR, and << >> being bitshifts (effectively * 2^n for << and / 2^n for >>)
        //comparison operators are the usual (no need to go over again, <, >, ==, ! are the core symbols)
        //logical operators are the same as c++
        if(true && true) System.out.println("true!");
        if(true || false) System.out.println("true!");

        // With credit from W3 schools, here are the "PEMDAS" of operations:
    /* 
    () - Parentheses
    *, /, % - Multiplication, Division, Modulus
    +, - - Addition, Subtraction
    >, <, >=, <= - Comparison
    ==, != - Equality
    && - Logical AND
    || - Logical OR
    = - Assignment
     */
    }

}

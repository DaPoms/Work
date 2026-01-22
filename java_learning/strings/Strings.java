
public class Strings
{
    public static void main(String[] args)
    {
        String word = "TacoCat";
        
        System.out.println(word + " is " + word.length() + " characters long! Wowzers!");
        System.out.println(word.toLowerCase());
        System.out.println(word.toUpperCase());
        System.out.println(word.indexOf("co")); //returns a 0 indexed location

        String target = "Cat";
        int loc = word.indexOf(target);
        if(loc != -1)
            System.out.println(word.substring(loc)); //prints everything including and past "Cat". Do note this should normally not be done without error handling as if "Cat" were not in the String, an error would get thrown
        else
            System.out.println(target + " not found in " + word);
        System.out.println(word); // note .toUpper and .toLower are not inplace functions (i.e. they did not affect our variable automatically)
        System.out.println(word.charAt(0)); // this is java's way of doing c++'s word[0] for a string

        String word2 = "TacoCat"; // java simplifies duplicate string literals to have the same address, so word2 and word have the same address
        String word3 = new String("TacoCat");
        if(word == word2) System.out.println("test1");  
        if(word == word3) System.out.println("test2"); // note that this fails when we make a deliberately new string with the same value (using the string constructor)
        if(word.equals(word3)) System.out.println("test3"); // using .equals() fixes the above problem by checking by value, not by address (I guess you could say checking by reference?)      
        String spacey = "                                                                                                                                                                I'm hidden! (or not!)                         ";
        System.out.println(spacey.trim());  

        String half1 = "pineapple";
        String half2 = " pizza";
        String half3 = " is certainly something!";
        System.out.println(half1.concat(half2).concat(half3));  //operates from left to right (the nested concat())
    }
}

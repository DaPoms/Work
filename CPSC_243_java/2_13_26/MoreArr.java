class MoreArr
{
    public static int max(int... a) // variable length argument (converts passed elements into an array)
    {
        int maxIdx = 0;
        for(int i = 0; i < a.length; i++)
            if (a[i] > a[maxIdx])
                maxIdx = i;
        return a[maxIdx];
    
    }
    public static void main(String[] args) // args is for command line args. Used by "java exe commandline1 commandline2"
    {
        System.out.println(args[0]);
        System.out.println(max(5,1,2,6,100,8,3,4));
        if(args[0].equals("a")) System.out.println("wow! you accessed a super secret output!");

        
    }
    //System.exit(0) - early exit
} // FOCUS ON tie breaking cases
//Print out answer with leter/char format
//Separatate operations and output (only do one operation at a time)
//export/home/public = all public directories on acad /gyne 

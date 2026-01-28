
public class Recursion {
    static int fibonacci(int i)
    {
        if(i == 0 || i == 1) return i; 
        return fibonacci(i - 1) + fibonacci(i - 2);
    }
    public static void main(String[] args)
    {
        int ans = fibonacci(5);
        //breakdown of what is happening recursive call wise:
        /*
                            fib(5)
                            calls
                    fib(4)          fib(3)
                            calls           
         fib(3)       fib(2)         fib(2)   fib(1)
                            calls
     fib(2) fib(1) fib(1) fib(0) fib(1) fib(0)  
                            calls
    fib(1) fib(0)
        
    then you add bottom up, where fib(0) returns 0, and fib(1) return 1
    fib(0) = 0
    fib(1) = 1
    fib(2) = fib(1) + fib(0) == 1 + 0 == 1
    fib(3) = fib(2) + fib(1) == 1 + 1 == 2
    fib(4) = fib(3) + fib(2) == 2 + 1 == 3
    fib(5) = fib(4) + fib(3) == 3 + 2 == 5
        */
        System.out.println(ans);
    }    
}

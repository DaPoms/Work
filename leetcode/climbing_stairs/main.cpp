    #include <iostream>
    //More efficient non recursive approach
    int climbStairs(int n) 
    {
        int count{2};
        int leftNum{1};
        int rightNum{1};
        int placeholder{-1};

        if(n == 1) // The only "base case" as 0 does not exist in the context of stair count
            return 1;
        while(count != n) //Finds all values before the nth number in the fib sequence, so that we can return the answer afterwards
        {   
            placeholder = rightNum;
            rightNum = rightNum + leftNum;
            leftNum = placeholder;
            count++;
        }
        return rightNum + leftNum;
    } 

    //recursive fib method (slow for big numbers), too slow to be accepted by leetcode. I did this one for fun as this is how I was taught fib in code
    /* int climbStairs(int n) 
    {
        if(n <= 1) //We do fib sequence but 1 ahead, as 0 stairs would mean it doesn't exist
            return 1;
        else
            return climbStairs(n - 1) + climbStairs(n - 2);
    } */

    int main()
    {
        std::cout << climbStairs(1);
    }

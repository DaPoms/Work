/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */


 //NOTE: This code doesn't work on vscode, only on this exact leetcode problem as the problem uses the above guess API function
 /* 
    int helper(long low, long high)
    {
        long mid = (low + high) / 2;
        int ans = guess(mid);
        if(ans == 1)
            return helper(mid + 1, high);
        else if(ans == -1)
            return helper(low, mid - 1);
        else
            return mid;

    }

    int guessNumber(int n) 
    {
        return helper(0,n);
    }
 */

//NOTE: This problem does not work on vs code due to the "isBadVersion" API being utilized for the problem, so read it only
// The API isBadVersion is defined for you as:
// bool isBadVersion(int version);

/* 
int helper(long low, long high) //All I did was a binary search but for calling the API isBadVersion
{
    long mid = (low + high) / 2;
    bool target = isBadVersion(mid);
    if(target == true && isBadVersion(mid - 1) == false) //If this is the first bad version, we found it! Only calls the API for mid - 1 if the 1st part is true
        return mid;
    else if(target == true) //If this is a bad version, but not the first one, we need to go left to find the first bad version
        return helper(low, mid - 1);
    else //If the middle version value is a good version, we need to move right to find the bad version
        return helper(mid + 1, high);
}
int firstBadVersion(int n) 
{
    if(n == 1) //edge case
        return 1;
    else
        return helper(1, n);
}
 */

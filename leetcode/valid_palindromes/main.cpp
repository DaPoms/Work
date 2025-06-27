    #include <iostream>
    #include <string>
    #include <cctype>
    #include <algorithm>
    using namespace std;
    string readBackwards(string s) 
    {
        string ans{""};
        for(int i{s.size() - 1}; i >= 0; i--)
            ans += s[i];
        return ans;
    }
    bool isPalindrome(string s) 
    {
        string ans{""}; //This is not the most memory efficient approach as it is not inplace, but it is very straightforward
        for(char letter : s)
            if(isalnum(letter))
                ans += tolower(static_cast<int>(letter));
        if(ans == readBackwards(ans)) 
            return true;
        return false;
    }

    int main()
    {
        string test{"taco/ cat:"};
        cout << isPalindrome(test);
    }

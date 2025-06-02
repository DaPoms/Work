#include <iostream>
#include <stack>
#include <string>
using namespace std;
 bool isValid(string s) {
        stack<char> openBrackets;
        for(char bracket : s)
        {
            if (bracket == '{' || bracket == '(' || bracket == '[')
                openBrackets.push(bracket);

            else
            {
               
                if (openBrackets.size() == 0 || (openBrackets.top() == '{' && bracket != '}' ||
                    openBrackets.top() == '(' && bracket != ')' ||
                    openBrackets.top() == '[' && bracket != ']' ) ) 
                    return false;
                else
                    openBrackets.pop();
            }
        }


        return openBrackets.empty();
}

int main()
{
    cout << isValid("{}");
}

#include <iostream>
#include <vector>
using namespace std;
void separateDigits(int n, vector<int>& ans)
{

    while(n > 0)
    {
        ans.push_back(n % 10);
        n /= 10;
    }
}
int subtractProductAndSum(int n) 
{
    vector<int> ans;
    int digitProduct{1};
    int digitSum{0};
    separateDigits(n, ans);
    for(int num : ans)
    {
        digitProduct *= num;
        digitSum += num;
    }
    return digitProduct - digitSum;
}
int main()
{
    cout << subtractProductAndSum(234);
}

#include <iostream>
#include <vector>
using namespace std;
//Something I've learned: The first half of the row is always the previous row, the second half is the inverse of the previous row, so just add the previous to the inverse of the previous to get the new row
//That's what makes this the MOST optimal recursive strategy I've done (does 30 rows in 16 seconds on my hardware, 2x faster than the previous implimentation)
//Funnily enough, leetcode still said this was too slow (the only accepted recursion cases I found were formula based, not done via physical bit manipulation)
//The only way I could see this being faster is by only calculating the half where the "k" we are looking for is
void invert(vector<char>& bits)
{
    for(char &bit : bits)
    {
        if(bit == '0')
            bit = '1';
        else
            bit = '0';
    }
}
// void helper(vector<char> &bits, vector<char> &ans, int n, int k)
void helper(vector<char> &bits, int n, int k)
{
    if(n == 1)
        return;
    vector<char> originalBits = bits;
    invert(bits);
    for(char bit : bits)
    {
        originalBits.push_back(bit);
    }
    bits = originalBits;
    helper(bits, --n, k);
} 

int kthGrammar(int n, int k) 
{
    vector<char> bits = {'0'};
    helper(bits, n, k);
    return int(bits[k-1] - '0');
}

//Way more efficient approach, but still not fast enough (took 30 seconds to calculate 30 rows of the rule)
/* 
void helper(vector<int> &bits, vector<int> &ans, int n, int k)
{
    if(n == 1)
        return;
    for(int bit : bits)
    {
        if(bit == 0)
        {
            ans.push_back(0);
            ans.push_back(1);
        }
        else
        {
            ans.push_back(1);
            ans.push_back(0);
        }
    }
    bits = ans;
    ans.clear();
    helper(bits, ans, --n, k);
} 

int kthGrammar(int n, int k) 
{
    vector<int> bits = {0};
    vector<int> ans;
    helper(bits, ans, n, k);
    return ans[k - 1];
    
}
 */
//Inefficient approach (still works, just deemed too slow by leetcode. Took many minutes to do 30 rows of the rule)
/* 
void helper(vector<int>& bits, int n, int k)
{
    if(n == 1)
        return;
    vector<int> changed = bits;
    int addIndex = 0;
    for(int i{0}; i < bits.size(); i++)
    {
        
        if(bits[i] == 0)
        {
            changed.insert(changed.begin() + addIndex + 1, 1);     
            addIndex++;
        }     
        else
        {
            changed.insert(changed.begin() + addIndex + 1, 0);
            addIndex++;
        }
        addIndex++;  
    }
    bits = changed;
    return helper(bits, --n, k);

} 

int kthGrammar(int n, int k) 
{
    vector<int> bits = {0};
    helper(bits, n, k);
    return bits[k - 1];
    
}
 */
int main()
{
    cout << kthGrammar(30,434991989);
}

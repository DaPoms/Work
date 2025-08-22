#include <bitset>
#include <iostream>
using namespace std;
//This technique completely goes around the bit manipulation aspect of this problem. I plan to go back to this once I fully understand bit manipulation
int binaryGap(int n) 
{
    bitset<32> bit = n;
    string bitString = bit.to_string();
    bool hasPrev1{false};
    int gap{0};
    int maxGap{0};
    int traverse{0};
    while(bitString[traverse] != '1')
    {
        traverse++;
    }
    for(int i{traverse}; i < bitString.size() ; i++)
    {
        if(bitString[i] == '0' && hasPrev1)
            gap++;
        else
        {
            if(hasPrev1)
                gap++;
            if(gap > maxGap)
                maxGap = gap;
            hasPrev1 = true;
            gap = 0;
        }
    }
    return maxGap;
}

int main()
{
    cout << binaryGap(5);
}


/* This one is not my work, I put it here because I honestly don't understand some parts of itand would like to learn bit manipulation (particularly operator<< with ints).
int binaryGap(int n) {
		int lastone = 32;
		int ans = 0;
		for (int i = 0; i < 32; i++) {
			if (n & (1 << i)) {
				ans = max(ans, i - lastone);
				lastone = i;
			}
		}
		return ans;
	}
         */

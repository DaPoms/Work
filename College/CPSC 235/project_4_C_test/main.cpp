#include <stdio.h> //Input, output
#include <stdlib.h> //Dynamic memory allocation, randomization
#include <unistd.h> //Sleep
#include <stdbool.h> //Bool
#include <math.h> // for log


//Program/architecture word size
#define DATABUSSIZE 4
//Number of bytes in each cache line, not including overhead
#define CACHELINESIZE 32 
//Total size of the cache, not including overhead
#define CACHESIZE 1024
struct cacheLine
{
    char data[CACHELINESIZE];
    int tag;
    bool dirtyBit; // 0 at start 
    bool validBit; // 0 at start
};


int main()
{
 int memoryAddress = 43121;
 int offsetSize = (int)log2(CACHELINESIZE); // This is where in the cache line data block we want
    int indexSize = (int)log2(CACHESIZE / CACHELINESIZE); // This is the cache line the address belongs to

    //(Learned of approach from user maskacovnik at https://stackoverflow.com/questions/30291562/how-to-generate-a-new-int-with-a-specific-amount-of-bits-in-it 
    //Works by shifting binary for value 1 (0b1) a single place ahead of where we want all 1's, then by subtracting by 1 it makes the single bit that was 1, 0, and all the bits before it now 1.
    unsigned int bitDigitsWantedOffset = (0b1 << offsetSize) - 1; 
    unsigned int bitDigitsWantedIndex = (0b1 << indexSize) - 1;

    int offset = (memoryAddress & bitDigitsWantedOffset); // AND'ing the address's bits with the digits we wanted only being 1 (DigitsWanted variable) and everything else being 0 means it isolates the offset
    int index = ((memoryAddress >> offsetSize) & bitDigitsWantedIndex); // % CACHELINECOUNT tells which cacheline address will be stored at. We do memAddress >> to remove the offset val and focus on the index val
    int tag = (memoryAddress >> (offsetSize + indexSize) ); // Tag is just an identifier, we'll use to check if cache contains the address we want for reading 

    printf("%d %d %d", offset, index, tag);

    char dataBus[4] = {1,2,3,4};
    cacheLine test;
    for(int i = 0 ; i < CACHELINESIZE; i++)
    {
        test.data[i] = '2';
    }

    bool isOverwrite = true;
    if(isOverwrite)
    {
        for(int i = 0; i < CACHELINESIZE; i++) // clears cache line first
            (test).data[i] = '-'; // I decided to use '-' for empty cache line just to match the RAM implimentation, also who knows, the user might want to purposely insert 0's, so I'd like to be able to differentiate 
    }

    for(int i = offset; i < (offset + DATABUSSIZE); i++) //have to assume that offset is within bounds of bus 
            (test).data[i] = dataBus[i - offset]; // i - offset is just the indexes for the data bus we are reading (always 0-3)

    int b = 0;
    /*     
    struct cacheLine emptyLine; // used to initialize all cache lines of cache
emptyLine.tag = 0;
emptyLine.dirtyBit = 0;
emptyLine.validBit = 0;
struct cacheLine cache[CACHESIZE / CACHELINESIZE];
for(int i = 0; i < (CACHESIZE / CACHELINESIZE); i++)
{
    cache[i] = emptyLine;
    emptyLine.tag++;
}
int memoryAddr = 65535;
int ans = sizeof(memoryAddr);
printf("%i", ans);
int i = 0; */
}
 
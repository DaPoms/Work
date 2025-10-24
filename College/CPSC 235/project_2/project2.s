#**************************************************************#
# Author: Daniel Tripoli                                       #
# Filename: project2.s                                         #
# Creation Date: October 19, 2025                              #
# Last Modified:                                               #
# Due Date: October 26, 2025                                   #
# Course: CPSC235-010                                          #
# Professor Name: Professor Jacklitsch                         #
# Project: 2                                                   #
# Purpose: To convert a C-String to ints, multiply by an int,  #
#          and return it as a char                             #
#                                                              #
#**************************************************************#

.intel_syntax noprefix
.global _start

.data
    ioArray: .zero 20
    ioSize: .int 20
    presetMutiplier: .int 9

_start:
    # reads 20 bytes of user input (so 20 chars)
    mov eax, 3 #eax stores the num of elements typed???? + enter key CRAZY!!!
    mov ebx, 0
    lea ecx, [ioArray]
    mov edx, 20
    int 0x80

    # STEP 1: Converts input (which are chars) to int digits (each digit is in it's own byte)

    dec eax  #I subtract by 1 as eax includes the newline char, making a total offset of 2
    charToIntDigits:
    cmp ebx, eax  # ebx is the loop counter as reading uses ecx unfortunately. 
    jz exitCharToIntDigits 
    sub BYTE PTR[ecx + ebx], '0' # converts char -> int val. We use [eax + ebx] as it traverses every char for us
    inc ebx
    jmp charToIntDigits
    exitCharToIntDigits:
    
    #STEP 1.5: Uses the int digits and converts them to an int (by mutiplying each digit by 10n times for it's digits place, n)
    mov edx, eax #holds where we should end
    dec edx # I decrement by 1 as I want to end early if we have only 1 char entered
    mov eax, 0 # eax will hold our answer (sum of each digit)
    mov ecx, 0 # ecx acts as the incrementer
    
    intDigitsToInt: #This is a novel but fun way to do digit conversion
    #movzx is needed or else we cannot properly add our elems
    movzx ebx, byte ptr[ioArray + ecx] #This is required to allow adding without carry issues (when I did user input of 512 with: add al, [ioArray + ecx] 510 + 2 would be stored as 256 due to the carrybit being flagged and not being used)
    add eax, ebx #adds digit
    cmp ecx, edx
    jz exitIntDigitsToInt
    imul eax, 10 #Makes room for the next digit, while bringing every currently added digit up one digit (which is why the one's digit is outside of the for loop)
    inc ecx
    jmp intDigitsToInt
    exitIntDigitsToInt:
    
    imul eax, [presetMutiplier] # STEP 2: Multiply user input by presetMutiplier!

    #STEP 3: Counts how many digits we have in our product
 
    mov edx, 0 #edx must be 0 or else you get a really high value for div
    mov ecx, 0 # ecx acts as the incrementer for counting the size of the value in eax
    mov ebx, 10 #stores the value we want to divide by (10)
    digitCounter: #This is a novel but fun way to do digit conversion
    inc ecx
    div ebx #EDX STORES THE DIGIT WE REMOVED (like %/mod operator)!
    add edx, '0'
    push edx
    mov edx, 0 #for 32 bit divison we MUST clear edx each time or else you get very large numbers in division (as 4 byte div combines EDX:EAX for 64 bit div)
    cmp eax, 0
    jnz digitCounter
   
    mov edx, ecx #moved ecx to edx to use ecx as an incrementer, edx now holds the size of the int
    mov ecx, 0 #used as incrementer
    putCharInArr:
    cmp ecx, edx
    je exitputCharInArr
    pop ebx #removes element from top, which is the highest digit place of our int
    mov [ioArray + ecx], ebx
    inc ecx
    jmp putCharInArr
    exitputCharInArr:

    ##STEP 4: Store number back in ioArray while converting it into chars, with highest digit being in the first address of ioArray, will overwrite old values
    
    # output ioArray
    mov eax, 4 
    mov ebx, 1
    lea ecx, [ioArray]
    mov edx, 20
    int 0x80

    #exit system call
    mov eax, 1
    mov ebx, 0
    int 0x80

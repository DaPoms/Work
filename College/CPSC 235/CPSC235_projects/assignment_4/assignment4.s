#**************************************************************#
# Author: Daniel Tripoli                                       #
# Filename: assignment4.s                                      #
# Creation Date: October 28, 2025                              #
# Last Modified:                                               #
# Due Date: October 31, 2025                                   #
# Course: CPSC235-010                                          #
# Professor Name: Professor Jacklitsch                         #
# Assignment: 4                                                #
# Purpose: impliment the fibonacci sequence                    #
#**************************************************************#
.intel_syntax noprefix
.global _start

.data
    desiredPosition: .int 5
    timesCalled: .int 0

_start:
    lea ebx, [timesCalled] #edx will hold the value
    push [desiredPosition] # val of desiredPos
    push ebx #the address of the iteration of the fib sequence
    call FibonacciFinder

    #exit system call
    mov eax, 1
    mov ebx, 0
    int 0x80

# Procedure Name: FibonacciFinder
# Description: Finds the nth fib number of the fib sequence
# Params: [ebp + 12] - Index of the fibonacci number we want
#         [ebp + 8] - Reference to int that keeps track of number of Fib function calls
# Returns: The fibonacci number at the given index
FibonacciFinder:
    push ebp #if doing ebp must + 4 to all current []
    mov ebp, esp

    mov edx, [ebp + 12] #Index
    mov ecx, [ebp + 8] # timesCalled REMINDER THIS IS THE ADDRESS 
    inc DWORD PTR[ecx]
 
    cmp edx, 1
    ja recursionCase
    # Base case 
    mov eax, 1 #I don't need this as timesCalled will preset this, yes?
    pop ebp
    ret 

    recursionCase:
    push edx # saves n
    dec edx # does n-1
    push edx # passing params (index number)
    push ecx # nums called param
    call FibonacciFinder 
    add esp, 8 # removes params we added once out of loop WE DONT CARE ABOUT EM!
    pop edx #restores n
    push eax # answer of f(n-1)

    
    sub edx, 2 # does n-2
    push edx
    push ecx
    call FibonacciFinder
    add esp, 8
    pop edx #stores answer of f(n-1) in edx

    add eax, edx #answer will be stored in eax
    pop ebp
    ret

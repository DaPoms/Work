#***************************************************************
# Author: Daniel Tripoli                                       #
# Filename: assignment3.s                                      #
# Creation Date: October 14, 2025                              #
# Last Modified: October 15, 2025                              #
# Due Date: October 17, 2025                                   #
# Course: CPSC235-010                                          #
# Professor Name: Professor Jacklitsch                         #
# Assignment: 3                                                #
# Purpose: To suffer the experience and witness the whismsy    #
#  of assembly                                                 #
#***************************************************************

1. What are the values in the “truly” general purpose registers after task 7?
    eax = 219411620
    ebx = 134516756 (address of studentID)
    ecx = 0
    edx = 15
2. What would happen if we had used edx instead of dx in step 3?
    Data would get lost as we'd be trying to fit 20 bytes in total into shortArray which only holds 10 bytes, meaning not all bytes will be transfered.
3. What would happen if we had used dl instead of dx in step 3?
    dl would work just fine in this case as edx has 15 stored in it and 15 is contained within 1 byte, and this byte is within dl
4. Why are the numerical values in shortArray not printed out in step 11?
    shortArray contains ints but the system call for writing interprets shortArray as chars, 

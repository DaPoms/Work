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

.intel_syntax noprefix
.global _start

# ADD COMMENT BLOCK ON TOP
.data
	genericData: .zero 20 # dedicates 20 bytes
	studentID: .int 11547980
	shortArray: .short 10, 20, 30, 40, 50 #
	welcomePrecursor: .asciz "Welcome, "

_start:
    # Step 1: sets all general registers to 0
    mov eax, 0
    mov ebx, 0
    mov ecx, 0
    mov edx, 0
    mov esi, 0
    mov edi, 0


    add edx, 15 # Step 2: moves 15 to edx # what about add dx, 15

    # Step 3: manipulates each value in the shortArray with various assembly functions with dx
    add [shortArray],     dx
    sub [shortArray + 2], dx
    and [shortArray + 4], dx
    or  [shortArray + 6], dx
    xor [shortArray + 8], dx
    
    # Step 4: adds all the elements of shortArray to eax
    add ax, [shortArray]
    add ax, [shortArray + 2]
    add ax, [shortArray + 4]
    add ax, [shortArray + 6]
    add ax, [shortArray + 8] 

    #Step 5: divides eax by 8 also known as (2 ^ 3)
    shr eax, 3

    #Step 6: stores address of studentID in ebx 
    lea ebx, [studentID] 
    
    
    #Step 7: Signed multiplication of eax with ebx, which holds the studentID val
    imul eax, [ebx] 
    # mov ebx, studentID uses imul eax, ebx


    # Step 8: system calling reading stdin to genericData
    mov eax, 3
    mov ebx, 0
    lea ecx, [genericData]
    mov edx, 20
    int 0x80

    # Step 9: system calling for writing welcomePrecursor
    mov eax, 4
    mov ebx, 1
    lea ecx, [welcomePrecursor]
    mov edx, 10
    int 0x80

    # Step 10: write contents of genericData to stdout
    mov eax, 4
    mov ebx, 1
    lea ecx, [genericData]
    mov edx, 20
    int 0x80

    # Step 11: write the content of shortArray to stdout
    mov eax, 4
    mov ebx, 1
    lea ecx, [shortArray]
    mov edx, 10
    int 0x80

    # Step 12: exits the program
    mov eax, 1
    mov ebx, 0
    int 0x80

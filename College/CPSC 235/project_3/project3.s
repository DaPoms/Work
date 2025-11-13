# **************************************************************#
# Author: Daniel Tripoli                                       #
# Filename: project3.s                                         #
# Creation Date: November 7, 2025                              #
# Last Modified: November 12, 2025                             #
# Due Date: November 12, 2025                                  #
# Course: CPSC235-010                                          #
# Professor Name: Professor Jacklitsch                         #
# Project: 3                                                   #
# Purpose: To convert a C-String to ints, multiply by another  #
#	       user inputted int, and return it as a char     	   #                        
#                                                              #
# **************************************************************#
.intel_syntax noprefix
.global _start 

#NOTE: The comment blocks above procedures are essentially directly taken from Professor Jacklitsch (so credit does not go to me for them)
.data
	multiplierRequestMessage: .asciz  "Please enter your multiplier: " 
	multiplicandRequestMessage: .asciz "Please enter your multiplicand: "
	productNoticeMessage: .asciz "Your product is "

_start:
	lea eax, [multiplicandRequestMessage] # I had to do this as push multiplierMessage doesnt pass address for some reason (Goofy intel x86!)
	push eax #pushes address of productNoticeMessage
	call CstringToStdoutProc # prints the value stored at the address of the parameter pushed above
	add esp, 4 # removes parameter

	call InputIntStdinProc
	push eax # we now care about eax! which is the mulplicand here 

	mov esi, 4
	lea eax, [multiplierRequestMessage]
	push eax
	call CstringToStdoutProc
	add esp, 4

	call InputIntStdinProc # collects multiplier
	mov esi, 4

	
	pop ebx # the multiplicand of user input
	mul ebx # esp stores the value of the multiplicand, mul automatically multiplies to eax
	mov esi, 2
	push eax # product gets put on stack

	lea eax, [productNoticeMessage]
	push eax
	call CstringToStdoutProc
	add esp, 4

	#product is parameter
	call OutputIntStdoutProc # outputs the int ans to stdout
	add esp, 4 # not needed but just for formality sake

	# exit system call
	mov eax, 1
	mov ebx, 0
	int 0x80
	


#NOTE: Parameter MUST be null terminated for this to not infinitely loop
# Procedure Name: CstringToStdoutProc
# Description: Write a C-string to stdout
# Parameters: The address of an array containing the C-string
# Local variables: None
# Returns: The number of characters written, not including the null terminator
CstringToStdoutProc: #do we not need to impliment ebp if it has no use? REJIOGRJERIGOEGJIEOIGERJIGORIJOGEOIJGIJOGRIOJEIJGJIOERJOIGJOGIERJOGJORJIOGIOJREIOJGROIJEOJIGREIOJGER
	mov eax, 4 # write
	mov ebx, 1
	mov ecx, [esp + 4] # need to use ecx as ecx is the buffer for sys call write. [esp+4] due to return address being on stack



	mov edx, 0 # edx acts as the counter
	mov edi, 21
	countTillEnd: 
	cmp BYTE PTR[ecx + edx], 0
	jz exitCount
	inc edx
	jmp countTillEnd
	exitCount:
	int 0x80

	# dec edx  #removes null terminator from count
	mov eax, edx # stores # of chars written, not including null terminator
	ret


# Procedure Name: IntToCstringProc
# Description: Convert an integer to a C-string
# parameters: The address of a character array to put the conversion to and an
#	integer containing the value to be converted
# Local variables: Nothing
# Returns: The number of characters put in the C-string, not including the null terminator
IntToCstringProc:

	mov edi, [esp + 8] # [esp + 8] stores an ADDRESS pointing to the start of local arr, so we MOV, NOT LEA
	mov eax, [esp + 4] # int (product)
	mov ebx, 10 # divisor
	mov ecx, 0 # keeps track of digit count
	mov edx, 0 # prepares for start of division

	
	mov esi, 2

	extractDigit: #stores all digits on stack
	cmp eax, 0
	je exitExtract
	div ebx # divides eax by 10, storing digit we removed in eax
	add dl, '0' #converts int to char
	push edx # the digit we extracted (never exceeds 1 byte even when adding '0')
	mov edx, 0 # reminder that remainder gets stored in edx
	inc ecx
	jmp extractDigit
	exitExtract:

	mov edx, 0 # edx will now become the counter for efficiency sake (1 less operation)
	
	popDigits:
	cmp edx, ecx
	je exitPop 
	pop ebx # ebx stores the digit we want to add
	mov BYTE PTR[edi + edx], bl
	inc edx
	jmp popDigits #IGJRIERJGE IGLOOOOK ATTTT
	exitPop:

	mov BYTE PTR[edi + ecx], 0 # null terminator insertion at the end

	mov eax, ecx # of characters put in the c string

	mov esi, 4
	ret 

# Procedure Name: OutputIntStdoutProc
# Description: Write an int to stdout
# Parameters: The int being written
# Local variables: A 12-character long array of characters
# Returns: Nothing
OutputIntStdoutProc:
	push ebp
	mov ebp, esp
	sub esp, 12 # local arr instantiation

	lea ebx, [ebp - 12] # array
	mov eax, [ebp + 8] # eax is an int (the product)
	
	cmp eax, 0 # if product is 0, we can just manually output answer, I have to do this as intToCString ends when eax = 0, but since its already 0, it stops immediately
	jnz skipZeroCase # case for most operations, skips the manual input for when product = 0 as anything in this jmp is product != 0
	mov BYTE PTR[ebx], '0' # manual insertion for product = 0
	mov BYTE PTR[ebx + 1], 0 
	jmp zeroCase
	skipZeroCase:
	
	push ebx 
	push eax # int
	call IntToCstringProc
	add esp, 8 # we keep ebx as we need it for below procedure

	zeroCase:
	lea ebx, [ebp - 12] #array
	push ebx
	
	call CstringToStdoutProc
	add esp, 16  # ISSUE HAS TO DO WITH HERE

	pop ebp
	ret


# Procedure Name: CstringToIntProc
# Description: Convert a C-string to an integer
# Parameters: The address of a C-string to be converted from
# Local variables: Nothing
# Returns: The integer interpreted from the C-string
CstringToIntProc:
	lea eax, [esp + 4] # Eax is set to start of local array Do we need to always do this? The InputIntStdinProc already has eax set to the proper value IERGOERJRJGOIEGJIROG
	#because we want to allow the user to pass any param, yes?
	mov ecx, 0
	
    charToIntDigits:
    cmp BYTE PTR[eax + ecx], 0 #null terminator is 0x0 NOTE: different from '0'
    je exitCharToIntDigits 
    sub BYTE PTR[eax + ecx], '0' 
    inc ecx
    jmp charToIntDigits
    exitCharToIntDigits:

	mov edx, 0 # holds the answer (which will then be stored in eax)
	mov edi, 0 # edi becomes the new counter srthitsjohjreiohjrothjhi, ecx is the end case

	mov esi, 9

	intDigitsToInt: 
    movzx ebx, BYTE PTR[eax + edi] # we will use ebx as a placeholder (no need to clear as movzx clears all)
    add edx, ebx #adds digit

	inc edi
	cmp edi, ecx
	je exitIntDigitsToInt
	
    imul edx, 10 #Makes room for the next digit, while bringing every currently added digit up one digit which is why the ones digit is outside of the for loop
    
    jmp intDigitsToInt
 
    exitIntDigitsToInt:
	mov eax, edx # stores answer in eax
	ret

# Procedure Name: StdinToCstringProc
# Description: Read from user input up to a newline character or the max capacity
#	and turn the result into a C-string
# Parameters: The address of an array which will hold the C-string and the
#	maximum number of characters in said C-string
# Local variables: None
# Returns: The number of characters read, not including the null terminator
StdinToCstringProc: # TEST READING FROM NON STDIN SO WE CAN SEE IF IT ALLOWS 11 CHARS FOR THAT INPUT (AS STDIN ADDS +1 CHAR OF THE ENTER KEY)
	mov eax, 3
	mov ebx, 0
	lea ecx, [esp + 8] # location of address for start of array
	mov edx, [esp + 4] # Amount of chars we are reading (INCLUDING ENTER, so can only enter [exp+4] - 1 characters)
	int 0x80

	mov BYTE PTR[ecx + eax - 1], 0 # adds null terminator to end Note: cannot use '\0' in our version of assembly
	ret

# Procedure Name: InputIntStdinProc
# Description: Read an int from stdin
# Parameters: None
# Local variables: A 12-character long array of characters
# Returns: The integer read from stdin
InputIntStdinProc: # STARTS HERE!!!!
	sub esp, 12 # making room for local array of size 12 (11 char max, last one will be null terminator)
	lea eax, [esp] # eax now acts as c-string (with no input currently) (YAY!)
	
	push [eax]
	push 12 # we also have to push max count
	call StdinToCstringProc # reads input + adds null terminator
	add esp, 4 # remove params from previous function call THAT ARENT USED IN THE NEXT ONE (we preserve eax as we use it again for this function)

	# param is eax, the local array, the same as StdinToCStringProc so not need to push here
	call CstringToIntProc # stores int form of c-string in eax!
	add esp, 16 # clears parameter + local array 
	ret

 
def main():
    numbers = [1,2,3,4,5]
    for number in numbers:
        print("|%d|" % number, end =" ") # very cool! print has an optional param of end which can be used to replace what the ending character is (normally a newline)
    print() 

    for x in range(0,2): #note that it STOPS when it reaches the right term, so you must do + 1 to get inclusive range printing
        print("|%d|" % numbers[x], end =" ")
    print()

    for x in range(0,5,2): # third param is step, increment or decrement
        print("|%d|" % numbers[x], end =" ")
    print()

    inc = 0
    while inc < 5:
        print("|%d|" % numbers[inc], end =" ")
        inc+=1
    print()

    inc = 0
    while inc < 100:
        print("|%d|" % numbers[inc], end =" ")
        inc+=1
        if inc == 5: # break skips exits the loop immediately (skips all iterations)
            break #handy for case where we want to look for someting untill a condition is met (keep reading till we hit a triple digit number)
    print()

    for x in range(0,5): # continue skips one iteration
        if(x == 1): continue
        print("|%d|" % numbers[x], end =" ")
    print()
    
    for number in numbers:
        print("|%d|" % number, end =" ") # very cool! print has an optional param of end which can be used to replace what the ending character is (normally a newline)
    else:
        print("WOAH THIS IS CRAZY!") #note that break will cause the else to be skipped, but continue doesn't
    print() 


if __name__ == "__main__":
    main()

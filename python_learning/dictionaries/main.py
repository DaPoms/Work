
def main():
    dict = {}
    dict["Red"] = "Blue" #python doesn't have explicit type specifying so you can do cool things like this!
    dict[3] = "test"
    print(dict["Red"], dict[3])

    #initialization syntax
    dict = {
        "Red" : "Blue",
        3 : "test"
    }
    print(dict["Red"], dict[3], "\n\n")

    for left, right in dict.items():
        print(left, right)
   
    for key in dict: # equivalent to the above statement, though the above is more readable
        print(key, dict[key])
    print('\n')

    for value in dict.values(): # .values() and .items() both return whats called view objects, sort of like a list of pointers 
        print(value)
    print('\n')

    del dict[3]
    # equivalence is dict.pop(3)
    
    for value in dict.values(): # .values() and .items() both return whats called view objects, sort of like a list of pointers 
        print(value)
    
if __name__ == "__main__":
    main()

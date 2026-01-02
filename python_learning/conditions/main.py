
def main():
    print(3 == 2)
    print(3 == 3 and 4 == 4)
    print(3 == 2 or 3 == 3)
    pool = ['a','b','c','d']
    if "b" in pool: #this is very neat compared to c++, where you'd manually make a for loop to hunt down the letter (or use a function from a library for .contains())
        print("Wowie!")
    boolean = True
    if boolean:
        print("this works!")
    x = [1,2,3]
    y = x
    z = [1,2,3]
    print(x is y) #is returns true when the left term is a reference of the right one.
    print(x is z)
    print(not 3 == 2)

    emptyArr = []
    #this statement evaluates to true when the list is empty
    if not emptyArr: # in python you do not have to state if emptyArr.size() == 0, python appears to uniquely evaluate empty lists == false
        print("woah!")
    
    
if __name__ == "__main__":
    main() 

def concatList():
    list1 = [1,2,3]
    list2 = [4,5,6]
    combined = list1 + list2
    print(combined) #adding two lists concatenates them together

def stringChainList():
    list = []
    list.append("hello" * 4) #multiplying strings makes them repeat for n times, with n being the int. Same can be done with everything else essentially
    print(list)

def listInList():
    test = [1] * 4 #note that this pushes 4 elements of 1 into test
    test.append([2] * 4) #while this stores one element in test which is a list of [2,2,2,2]
    print(test)
def main(): #main allows it to be tested in other files (by calling this file's main)
    listInList()
    #concatList()
    #stringChainList()


if __name__ == "__main__": 
    main() #learned of the practice of specifying main, any code put in this statement will only run if this file is the file being run first (top-level) EX: If the makefile has this file at the top, then it will run this
     

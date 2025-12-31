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
    list = []
    list.append([1] * 4) #multiplying strings makes them repeat for n times, with n being the int. Same can be done with everything else essentially
    #note the [1] brackets are necessary to treat it as its own list (so it makes n copies of that list)
    print(list)
def main(): #main allows it to be tested in other files (by calling this file's main)
    
    listInList()
    #concatList()
    #stringChainList()

if __name__ == "__main__": main()#learned of the practice of specifying main, any code put in this statement will only run if this file is the file being run first (top-level) EX: If the makefile has this file at the top, then it will run this
     

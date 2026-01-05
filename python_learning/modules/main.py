import sys # sys is required to add new paths for module searching (useful for user defined modules, but makes compatibility harder for other users)
isHello = 0

#sys.path.append("C:/Users/Pomer/projects/python_learning/modules/hiding_module")

if(isHello == 1): # here we've implimented a way for the programmer to change which mode they are on when 2 modules contain the same function name
    import test as WhateverWeWantToCallIt #to reference a local file just import with the name
elif(isHello == 2):
    import test2 as WhateverWeWantToCallIt
else:
    import hiding_module.test3 as WhateverWeWantToCallIt # this approach worse due to test.3 being a package of hiding_module. Packages are just directories with a __init__.py file in them and what we want to include can be the whole directory OR the specified module via directoryName.moduleName
    # from hiding_module import test3 as WhateverWeWantToCallIt # this is another syntax for the above other than with import it prevents having to use . to access functions
    # import test3 as WhateverWeWantToCallIt # this approach works with sys.path

# from test import printHello # this allows you to pull specific functions without needing to do file.functionname(), instead you can do functionname() for a call
# from test import * this imports all from the module, which is mainly a bad practice for big files (due to possible name conflicts). Reminds me of doing using namespace std; in c++
# import 

def main():
    WhateverWeWantToCallIt.printHello() # similar to SQL, we can use "as" to give nicknames, particularly for importing modules. This also means we can make conditional imports
    print(WhateverWeWantToCallIt.specialNum)
    help(sys.intern) # doing help(module function) just outputs a simple description that could be found in documentation

if __name__ == "__main__":
    main()

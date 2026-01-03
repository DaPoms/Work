class Dog: # note to self to also go over subclasses/inheritance syntax
    name = "a"
    breed = "b"
    # note that optional params are defined by providing a defualt value, like c++
    def __init__(self, name, breed = ""): # Python's constructor (I like C++ syntax of dog() more)
        #I also just learned that you do not need to use the word "self" but rather anything works, its just the 1st param will always recieve the object
        self.name = name # the usage of self reminds me of this->name or *this.name in c++, but python forces "self" unlike "this" in c++, and also "this" is a pointer whereas it appears "self" is the actual object itself
        self.breed = breed
    def print(self):
        print(self.name + " the " + self.breed)



def main():
    myDog = Dog("Chowder", "Maltese")
    myDog.print()
    myDog.breed = "Golden retriever"
    myDog.name = "Steve"
    myDog.print()
if __name__ == "__main__":
    main()

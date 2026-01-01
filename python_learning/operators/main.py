def main():
    print("2 and 3:\n   Added:", 2 + 3)
    print("   Subtracted:", 2 - 3)
    print("   Divided:", 2 / 3) # note because of non-type specifications, this doesn't round down like it does in c++
    print("   Floored divide:", int(2 / 3)) # You can do type casting to maintain flooring an equation
    print("   Mod:", 2 % 3)
    print("   Power:", 2 ** 3) #power operator **
    leftList = [1,1,1,1]
    rightList = [2,2,2,2]
    print(leftList + rightList)
    print(leftList * 3)
if __name__ == "__main__":
    main()

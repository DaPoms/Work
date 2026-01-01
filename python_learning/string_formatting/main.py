def main():
    name = "bob"
    earnings = 253
    print("Hello there, Mr/Mrs %s. You've earned $%d" % (name, earnings) )
    tax = 9.52
    print("Total tax: %f paid." % tax)
    print("Total tax: %.2f paid." % tax) #for %f, doing %.#f has the number be the precision/sig figs
    hexInt = 10
    print("This is in hexidecimal: %x" % hexInt)
if __name__ == "__main__":
    main()

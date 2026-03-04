

public class Test {
    
}

class Name 
{
    private String fName;
    private String lName;


    public Name(String fName, String lName)
    {
        this.fName = fName;
        this.lName = lName;
    }
    public Name()
    {
        this("John","Doe");
    }
}


class Person 
{
    private int age;
    private Name name;


    public Person(int age, Name name) // This is an aggreagate class, with class name being the aggregated. This is because the Name objects must be intantiated externally
    {
        this.name = name;
        this.age = age;
    }
    public Person()
    {
        this(0, new Name());
    }
}

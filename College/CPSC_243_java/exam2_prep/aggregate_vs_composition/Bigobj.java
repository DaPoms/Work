public class Bigobj
{
    private history stateHist;
    private Currentstats stateStats;
 
    Bigobj(history hist, int GDP, int age)
    {
        stateHist = hist;
        stateStats = new Currentstats(GDP, age);
    }
    @Override 
    public String toString()
    {
        return stateHist.toString() + "\n" + stateStats.toString();
    }

    public static void main(String args[])
    {
        history hist = new history("North Bobsen", "1/2/2121");
        Bigobj b = new Bigobj(hist, 100000000, 9999);
        System.out.println(b);
    }
}

class history // Aggregation (aggregate)
{
    String location;
    String dateOfCreation;

    history(){this("Nowhere","0/0/0");}

    history(String location, String dateOfCreation)
    {
        this.location = location;
        this.dateOfCreation = dateOfCreation;
    }
    @Override 
    public String toString()
    {
        return "Located at " + location + "\nFounded on " + dateOfCreation;
    }
}

class Currentstats // Composition (Composite)
{
    int GDP;
    int age;
    Currentstats(){this(0,0);}

    Currentstats(int GDP, int age)
    {
        this.GDP = GDP;
        this.age = age;
    }

     @Override 
    public String toString()
    {
        return "Current GDP: " + GDP + "\nat " + age + " years old."; 
    }
}

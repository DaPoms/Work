import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Random;
import java.lang.StringBuilder;
public class Account 
{
    private static int numAccs = 0;
    private static final double ANNUALIR = 0.03; //in percent, static under the asumption that everyone gets the same value
    private long id;
    private String name;
    private LocalDate dateCreated;
    private double balance;



    public long getID(){return id;}
    public String getName(){return name;}
    public LocalDate getDateCreated(){return dateCreated;}
    public double getBalance(){return balance;}
    public static double getAnnualIR(){return ANNUALIR;}
    public static int getNumAccs(){return numAccs;}

    public void setName(String name){this.name = name;}
    
    public void withdraw(double amount)
    {
        if(amount < balance && amount > 0)
            balance -= amount;
    }
    public void deposit(double amount)
    {
        if(amount > 0)
            balance += amount;
    }
    
    Account()
    {
        name = "Anonymous";
        balance = 0.0;
        Random rand = new Random(System.currentTimeMillis());
        id = rand.nextLong(); // generate
        dateCreated = LocalDate.now();
        numAccs++;
    }
    Account(String name, double balance)
    {
        this.name = name;
        this.balance = balance; 
        Random rand = new Random(System.currentTimeMillis());
        id = rand.nextLong();
        dateCreated = LocalDate.now();
        numAccs++;
    }

    public static double getMonthlyIR()
    {
        return ANNUALIR / 12;
    }

    public double getMonthlyInterest()
    {
        return balance * (getMonthlyIR() / 100);
    }

    public boolean isBroke()
    {
        if(balance < 100) 
            return true;
        return false;
    }

    public String toString() //If using strings within class, always use string builder
    {
        DateTimeFormatter format = DateTimeFormatter.ofPattern("MM-dd-YYYY");
        StringBuilder str = new StringBuilder();
        str.append("Account Name: ").append(name).append('\n');
        str.append("Account ID: ").append(id).append('\n');
        str.append("Date Created: ").append(dateCreated.format(format)).append('\n');
        str.append("Balance: ").append(String.format("%.2f",balance) ).append('\n');
        return str.toString();
    }
    public static void main()
    {
        Account myAcc = new Account("Bob", 300);
        System.out.println("My account name: " + myAcc.name);
        System.out.println("My account ID: " + myAcc.id);
        System.out.println("My account creation date: " + myAcc.dateCreated);
        System.out.println("My account balance: " + myAcc.balance); // we can still do this as main is placed inside of Account class
        System.out.println(myAcc); // APPLIES toString() automatically as long as case sensitive name of "toString"
        System.out.println("Monthly interest: " + myAcc.getMonthlyInterest());
        System.out.println("Am I broke?: " + myAcc.isBroke());
        System.out.println("Number of accounts: " + Account.numAccs);
    }
}

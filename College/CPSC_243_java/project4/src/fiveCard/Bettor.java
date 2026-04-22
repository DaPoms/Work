package fiveCard;
import java.util.ArrayList;
public class Bettor <E extends Hand> {
    private String name; // Username
    private double startBal; //init balacnce
    private double currBal; // curr balance
    private double currWager; // current user wagered value
    private double entryPay; // Used for poker as the blind
    //ArrayList<Double> betHist;
    //int checkCount; // Used to determine what dealer wagers (as its based off of user's wagers)



    public Bettor() // used only as a formality
    {
        this("John doe", 0,25);
    }

    public Bettor(String name, double startBal, double entryPay)
    {
        this.name = name;
        this.startBal = startBal;
        currBal = startBal;
        this.entryPay = entryPay;
        currWager = entryPay;
        //betHist = new ArrayList<>(); // For betting history
    }

    public void placeBet(double betVal) throws PokerException // Ask what anyArgs entails for function on handout
    {
        if(betVal + currWager <= currBal) { currWager = betVal;}
        else
            throw new PokerException("Tried to wager more than the balance. total wager was " + (betVal + currWager) + " when total balance was " + currBal);
    }


    //TODO: ASK, ARE WINNINGS THE NET EARNINGS (TOTAL - WAGER) OR THE TOTAL POT RETUEN
    public String collectWinnings(Hand player, Hand dealer) // ASK: Do we need to use instanceof? as we are asked to use type Hand? Maybe we need to make a compareTo for Hand class?
    {
        int result;
            result  = (player).compareTo(dealer);
            switch(result)
            {
                case 1 ->  {
                    currBal += currWager; 
                    return  name + " earned $" + currWager; // NOTE MIGHT HAVE TO EDIT !!!!!!!!!!!!!!!!!!!!!!!!!!
                } // Because dealer wager matches player, reward is 2x the wager
                case 0 ->  {
                    
                    return name + " refunded wager of $" + currWager;
                }
                case -1 -> {
                    currBal -= currWager;
                    return name + " lost $" + currWager;
                }
            }
        return "ERROR"; // MAKE SURE TO UPDATE THIS!!!!!!!!!!!!!!!!
    }

    public void resetBet(){currWager = entryPay;}
    public double getBalance(){return currBal;}
    public double getWager(){return currWager;}
    public double getEntryPay(){return entryPay;}
    public void subtractByWager() throws PokerException //placebet sort of prevents this exception, but just in case
    {
        if(currWager > currBal) 
            throw new PokerException("Tried to withdraw more than balance has. Wager was " + (currWager) + " when total balance was " + currBal);
        currBal -= currWager;
        currWager = entryPay;
    }
    public double getTotalWinnings(){return currBal - startBal;}
    public double getRoundWinnings(){return currWager;}
 


}

// Note that a raise MUST be more than the blind
//Check = 0 dollars wager (FOR SECOND ROUND, NOT FIRST, requested as a CALL)
// raise = betting higher than call val
// Call = matching bet, user's call is = check (0 dollar wager) on round 2. on round 1, it will match the big blind ($50)

// User can call, raise, fold (call does big blind, rasise allow anything past big blind, fold will end, you lose $25)

//Round 1's and 2's goal is for user and dealer to have the SAME BET value

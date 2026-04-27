/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  April 21, 2026                           */
/* Due Date:       April 24, 2026                           */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #4                                       */
/* Filename:       Bettor.java                              */
/* Purpose:        Implements betting functionality         */
/************************************************************/

package fiveCard;

/**
 * Implements betting functionality. Note that Bettor is mainly built for 1 player vs 1 dealer
 * fiveCard.Bettor.java
 * CPSC243 Spring 2026
 * @author Daniel Tripoli
 */
public class Bettor <E extends Hand> {
    private String name; // Username
    private double startBal; //init balance
    private double currBal; // curr balance
    private double currWager; // current user wagered value
    private double entryPay; // Used for poker as the blind


    /**                                                   
    *     Empty constructor for the Bettor object.
    */
    public Bettor() // used only as a formality
    {
        this("John doe", 0,25);
    }

    /**                                                   
    *     Parameterized Constructor for the bettor object.
    *     @param name The name of the bettor 
    *     @param startBal The starting balance
    *     @param entryPay The price that must be payed to start the bet
    */
    public Bettor(String name, double startBal, double entryPay)
    {
        this.name = name;
        this.startBal = startBal;
        currBal = startBal;
        this.entryPay = entryPay;
        currWager = entryPay;
        //betHist = new ArrayList<>(); // For betting history
    }

    /**                                                   
    *     Raises bet up to the given number
    *     @param betVal The value the bet will be raised to
    *     @throws PokerException If trying to wager more than the current balance or a negative number
    */
    public void placeBet(double betVal) throws PokerException // Ask what anyArgs entails for function on handout
    {
        if(betVal > 0 && betVal <= currBal) { currWager = betVal;}
        else if(betVal > currBal) // I limited the exception handling here as we don't know how betting behaviors might deviate from poker (like raise must be >= current bet), so my PokerCasinoGame implements it instead
            throw new PokerException("Tried to wager more than the balance. Wager was " + (betVal) + " when total balance was " + currBal);
        else 
            throw new PokerException("Tried to wager a negative value. Wager was " + betVal);
        }

     /**                                                   
    *     Carries out a bet based on the result of if the player wins or loses
    *     @param player The hand of the player that is compared to the dealer
    *     @param dealer The hand of the dealer
    *     @return String representation of how much the player won or lost
    */
    public String collectWinnings(Hand player, Hand dealer) // ASK: Do we need to use instanceof? as we are asked to use type Hand? Maybe we need to make a compareTo for Hand class?
    {
        int result;
            result  = (player).compareTo(dealer);
            switch(result)
            {
                case 1 ->  {
                    currBal += currWager; 
                    return  name + " earned $" + currWager;
                } // Because dealer wager matches player, net reward is the wager
                case 0 ->  {
                    return name + " refunded wager of $" + currWager;
                }
                case -1 -> {
                    currBal -= currWager;
                    return name + " lost $" + currWager;
                }
            }
        return "ERROR: compareTo did not evaluate to any number from -1 to 1"; 
    }


     /**                                                   
    *     Resets wager value
    */
    public void resetBet(){currWager = entryPay;}

    /**                                                   
    *     Returns the player's current balance
    *     @return The current balance of the player
    */
    public double getBalance(){return currBal;}

    /**                                                   
    *     Gets the player's required minimum bet (in poker, this is the small blind)
    *     @return Price of entry for the betting game
    */
    public double getEntryPay(){return entryPay;}

    /**                                                   
    *     Withdraws the wager from the current balance
    *     @throws PokerException If wager is larger than the balance, thus withdrawing more than possible
    */
    public void subtractByWager() throws PokerException //placebet sort of prevents this exception, but just in case
    {
        if(currWager > currBal) 
            throw new PokerException("Tried to withdraw more than balance has. Wager was " + (currWager) + " when total balance was " + currBal);
        currBal -= currWager;
        currWager = entryPay;
    }

    /**                                                   
    *     Returns the net winnings of the bettor, in terms of the money they started with and what they have now
    *     @return The net winnings of the bettor
    */
    public double getTotalWinnings(){return currBal - startBal;}

    /**                                                   
    *     Returns the winnings the bettor/player would have if they won their bet
    *     @return The value of the current wager, which is what the round winnings are if the bettor (player) wins
    */
    public double getRoundWinnings(){return currWager;}

    /**                                                   
    *     Returns the name of the bettor
    *     @return The name of the bettor
    */
    public String getName(){return name;}
 


}

/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  April 21, 2026                           */
/* Due Date:       April 24, 2026                           */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #6                                       */
/* Filename:       PokerCasinoGame.java                     */
/* Purpose:        implements the entirety of the game of   */
/*                 poker through the fivecard package and   */
/*                 game specific functions declared in this */
/*                 file.                                    */
/************************************************************/


// HUGE TODO :           MUST REVAMP ALL THE JAVADOCS COMMENTS ON THIS FILE!


package fiveCard;
import java.util.Scanner;
import fiveCard.PokerHand.HandRank;
import fiveCard.PokerHand.HandResult;
import fiveCard.PokerHand.cardByCountAndRank;
import java.util.ArrayList;
import java.util.Comparator;

/**
 * implements the entirety of the game of poker through the fivecard package and   
 * game specific functions declared in this file. 
 * fiveCard.PokerCasinoGame.java
 * CPSC243 Spring 2026
 * @author (Provided starter code by) Griffin Nye
 * @author (Implemented by) Daniel Tripoli
 */
public class PokerCasinoGame extends CasinoCardGame {
    //private double startBal; // I decided to do this as its simpler than having a whole bettor 
                    //object in CasinoCardGame, and it gives more freedom for how a dev wants to manage balances (by making the subclass implement it)
    private PokerHand playerHand;
    private PokerHand dealerHand;
    private Bettor wager;
    private Deck gameDeck;
    private boolean didFirstDrawOnCommandLine; // TODO MIGHT REMOVE DPEENDING ON PROF ANSWER






        ///////////////////////////Project 6 code ///////////////////////////
        
        
        public PokerHand getPlayerHand() {return playerHand;}
        public PokerHand getDealerHand() {return dealerHand;}
        public String getBalanceAsString() {return Double.toString(wager.getBalance());}
        public Double getBalance() {return wager.getBalance();}
        public String getWagerAsString() {return Double.toString(wager.getRoundWinnings());} //Yes, round winnings returns the profit IF player wins, which is = the current wager
        public Double getWager() {return wager.getRoundWinnings();}
        public Bettor getWagerObject() {return wager;}
        public String getEntryPay() {return Double.toString(wager.getEntryPay());} // Just passes function up for easier access
        public void setupGame(double startBal, String... args) // Only for initial setup
        {
            int smallBlind = 25;
            playerHand = new PokerHand();
            dealerHand = new PokerHand();
            wager = new Bettor("", startBal, smallBlind); //Our frontend doesnt ask for a name, but I decided we'll just not use the name related functions rather than altering Bettor
            didFirstDrawOnCommandLine = false;       

            gameDeck = null; // This is required as try catch's are inferred to not succeed by compiler
            try{
                gameDeck = new Deck(-1); // -1 reshufflecount is just used to denote an unshuffled deck
                gameDeck.shuffle(rollReshuffleCount(11,44)); // sets the reshufflecount to a proper value, + shuffles deck
            } catch(PokerException e) 
            {
                e.printStackTrace();
                System.exit(1); // My general rule of thumb is all execption cases dealt with in main are meant to terminate the program
            }       

            if( args.length > 0 ) 
            {
                    CmdLineInput.parseArguments(args, playerHand, dealerHand);// Note we need a try catch here because parseArgs uses addCard, which does have 'throws' functionality
                    didFirstDrawOnCommandLine = true;
            }     
        }



        public void draw()
        {
            try { // Case of redrawing after hitting reshuffle in draw phase (guaranteed to not happen again, but catch is still required with my draw5() function)
                    drawPhase();
            } catch(PokerException e) {
                System.err.println("Shuffling did not reshuffle the deck, leading to a failed card deal."); // Should be impossible to happen (you never know! :) )
                e.printStackTrace();
                System.exit(1);
            }
        }

      /*   public void handleBet() TODO Done by BACKEND on button press (call, raise, fold. Dealer's bet also occurs at the same time, copying the user's move)
        {

        } */

    /**                                                                    
    *    The full behavior of the user's discard: both asks the user which cards to discard,
    *    carries out the discard, and draws cards for the cards removed.
    *    @param playerHand The hand that the discards are done on
    *    @param scan The input stream for user input
    *   @param deck - The deck that cards are dealt from
    *    @return Returns whether or not the deck needs to be shuffled after the discard
    *    @throws PokerException If removing an out of index card from hand
    *    
    */
    public boolean userDiscard(ArrayList<Integer> playerCardsToBeDiscarded) throws PokerException
    {
        boolean hasToReshuffledAfterDeal = false;
        if((playerCardsToBeDiscarded.size() != 1 || playerCardsToBeDiscarded.get(0) != -1)) // Ensures we do not discard when user enters -1
        {
            // Can throw case of removing nonexistent card (should've been prevented by askUserForDiscard function)
            for(int i = playerCardsToBeDiscarded.size() - 1; i >= 0; i--) // Reverse order of removal ensures easy deletion (shifted elements have no impact on deletion)
                playerHand.removeCard(playerCardsToBeDiscarded.get(i)); // We subtract 1 due to 0 indexed arrays (The user enters 1 for index 0)
            
            for(int i = 0; i < playerCardsToBeDiscarded.size(); i++) // Refills the hand with new cards
                try{
                    if(gameDeck.getTop() >=  gameDeck.getReshuffleCount()) // Checks for if we hit reshuffleCount mid-discard
                        hasToReshuffledAfterDeal = true;
                    playerHand.addCard((gameDeck.deal()));
                } catch(PokerException e)
                {
                    playerHand.addCard((gameDeck.dealIgnoringReshuffle())); // For discard, we are allowed to deal cards past rehufflecount
                } 
        }
        return hasToReshuffledAfterDeal;
    }

    /**
    *                                                                            
    *     The full behavior of the dealer's discard: follows rules to,
    *     carry out discards based on hand rank, and draws cards for the cards removed.
    *     @param dealerHand The hand that the discards are done on
    *     @param deck The deck that cards are dealt from
    *     @return Whether or not the deck needs to be shuffled after the discard
    *     @throws PokerException If trying to add null card, or remove/get a card out of bounds
    *    
    */
    public boolean dealerDiscard() throws PokerException // Dealer is the "AI"
    {
        int startingSize = dealerHand.getCardCount(); // used for both modularity and less verbose syntax 
        HandRank handRank = dealerHand.getHandRank(); 
        if(handRank.ordinal() > HandRank.THREE_OF_A_KIND.ordinal()) 
            return false; //Quick case of no discards
        if(handRank == HandRank.THREE_OF_A_KIND || handRank == HandRank.TWO_PAIR || handRank == HandRank.ONE_PAIR)
        {
            cardByCountAndRank[] top2Counts = dealerHand.top2PairCount(); //Holds the top 2 card occurences
            int pairCount = 1;
            if(handRank == HandRank.TWO_PAIR) 
                pairCount = 2;
            for(int i = startingSize - 1; i >= 0; i--)
                if(dealerHand.getCard(i).getValue() != top2Counts[0].getCardRankVal() && (pairCount == 1 || dealerHand.getCard(i).getValue()  != top2Counts[1].getCardRankVal()))
                    dealerHand.removeCard(i);
          
            //              V THIS IS COOL NEW SYNTAX I learned to use size methods WITHIN the for loop by calling it ONCE. discard size is the size of the hand after discarding
            for(int i = 0, discardSize = dealerHand.getCardCount(); i < startingSize - discardSize; i++) // I could've hardcoded the add on values (like 3 of a kind will rmeove 2 cards, two pair 1, and one pair 3) but I like more modular code for the possibility of reusing it later on (like if we wanted to implement a different card game later)
            { 
                try{
                dealerHand.addCard(gameDeck.deal());
                } catch(PokerException e)
                {
                    dealerHand.addCard(gameDeck.dealIgnoringReshuffle());
                }
            }
        }
        else // case of high card
        {
            for(int i = 0; i < startingSize - 1; i++) // size - 1 ensures we remove all but the last, and since I sort all hands automatically from least to greatest, the highest card is preserved
                dealerHand.removeCard(0);
            for(int i = 0; i < startingSize - 1; i++) //Replaces the cards we deleted
            {
                try{
                    dealerHand.addCard(gameDeck.deal());
                } catch(PokerException e)
                {
                    dealerHand.addCard(gameDeck.dealIgnoringReshuffle());
                }
            }
        }

        if(gameDeck.getTop() >=  gameDeck.getReshuffleCount()) // Checks for if we hit reshuffleCount mid-discard
            return true;

        return false; //returns that reshuffle is not needed
    }

    /**                                                          TODO MUST UPDATE
    *    Covers both the player and dealer's turn during the discard phase of poker. 
    *    Also accounts for if a reshuffle is needed after the discard phase
    *    @param playerHand Player's poker hand for their discard turn
    *    @param dealerHand Dealer's poker hand for their discard turn
    *    @param deck The deck that cards are dealt from
    *    @param scan - The input stream for user input
    *   @throws PokerException If drawing a null card to hand   
    */
    public void discard(ArrayList<Integer> playerCardsToBeDiscarded) throws PokerException
    {
        boolean hasToReshuffledAfterDealUser = userDiscard(playerCardsToBeDiscarded);
        boolean hasToReshuffledAfterDealDealer = dealerDiscard();
        if(hasToReshuffledAfterDealUser || hasToReshuffledAfterDealDealer) // Reshuffle case (happens AFTER the discard phase)
                gameDeck.shuffle(rollReshuffleCount(11, 44));
    }



    ///////////////////////////Project 4 code ///////////////////////////
    /**                                                   
    *     Constructor for the PokerCasinoGame object
    *     @param startBal The player's starting balance
    *     @throws PokerException If reshuffleCount is > 52
    */
    public PokerCasinoGame(double startBal, String... args) throws PokerException
    {
        super(new PokerHand(), new PokerHand()); // This is how we pass the hand type we want to the super class    
        int smallBlind = 25;
        playerHand = new PokerHand();
        dealerHand = new PokerHand();
        wager = new Bettor("", startBal, smallBlind); //Our frontend doesnt ask for a name, but I decided we'll just not use the name related functions rather than altering Bettor
        didFirstDrawOnCommandLine = false;       

        gameDeck = null; // This is required as try catch's are inferred to not succeed by compiler
        try{
            gameDeck = new Deck(-1); // -1 reshufflecount is just used to denote an unshuffled deck
            gameDeck.shuffle(rollReshuffleCount(11,44)); // sets the reshufflecount to a proper value, + shuffles deck
        } catch(PokerException e) 
        {
            e.printStackTrace();
            System.exit(1); // My general rule of thumb is all execption cases dealt with in main are meant to terminate the program
        }       

        if( args.length > 0 ) 
        {
                CmdLineInput.parseArguments(args, playerHand, dealerHand);// Note we need a try catch here because parseArgs uses addCard, which does have 'throws' functionality
                didFirstDrawOnCommandLine = true;
        }     
    }































    

    /**                                                   
    *     Runs the entire poker game, carrying out drawing, dealing, discarding, and betting.
    *     @param args Command line argument for the case of starting with a premade hand
    */

    /*  public void play(String... args) // chop up for use in front end event handling
    {
      
        setupGame(startBal, args);
        
        do  ///////////////////////////////// Actual game ////////////////////////////////////
        {   
            printBalance(wager);
            // DRAW PHASE //
            if(didFirstDrawOnCommandLine == true) //Very ugly system for allowing normal running after a command line turn (I did not want to just copy the entire code below into the command line case)
                didFirstDrawOnCommandLine = false; 
            else
            {
                try { // Case of redrawing after hitting reshuffle in draw phase (guaranteed to not happen again, but catch is still required with my draw5() function)
                    drawPhase(playerHand, dealerHand, gameDeck);
                } catch(PokerException e) {
                    System.err.println("Shuffling did not reshuffle the deck, leading to a failed card deal."); // Should be impossible to happen (you never know! :) )
                    e.printStackTrace();
                    System.exit(1);
                }
            }


/////////////////////

            boolean isFold = false;
             try{
                isFold = handleBet(wager, scan, true, playerHand, dealerHand);
            if(isFold) 
                continue;  
            } catch(PokerException e)
            {
                e.printStackTrace();
                System.exit(1);
            }

            // DISCARD PHASE //
            try {
            discardPhase(playerHand, dealerHand, gameDeck, scan);
            } catch(PokerException e)
            {
                e.printStackTrace();
                System.exit(1); //Note that the deal() error is caught INSIDE discardPhase, so this accounts for any error other than deal()'s (like the addCard(null) case )
            }

   
             try{
                isFold = handleBet(wager, scan, false, playerHand, dealerHand);
            if(isFold)
                continue;  
            } catch(PokerException e)
            {
                e.printStackTrace();
                System.exit(1);
            }



            // RESULTS PHASE //
            int playerComparator = -2; // 0 = same, -1 = less, 1 = greater 
            HandRank playerRank = playerHand.getHandRank();
            HandRank dealerRank =  dealerHand.getHandRank();
            try { // Did this to ensure separation of I/O from "backend"
                playerComparator = playerHand.compareTo(dealerHand);                    
            } catch(Exception e) // This is needed for getKickerArr()'s usage of getCard()
            {
                e.printStackTrace(); // printStackTrace also displays the message of exception
                System.exit(1);
            }                

            
            printResults(playerHand, dealerHand, playerRank, dealerRank, PokerHand.comparatorIntToHandResult(playerComparator));
            System.out.println(wager.collectWinnings(playerHand, dealerHand));

            //resets hands for next round 
            playerHand.clear();
            dealerHand.clear();
            System.out.println();
            wager.resetBet();
            printTotalWinnings(wager);
        } while ((wager.getBalance() >= wager.getEntryPay() * 2)); // * 2 is just the assumption that small blind is 1/2 the value of the big blind, and the player MUST bet at LEAST the big blind to get past discard phase
        System.out.println("Ending balance: $" + wager.getBalance());
    } */





   /*  public void play(String... args) // chop up for use in front end event handling
    {
        int smallBlind = 25;
        Scanner scan = new Scanner(System.in);
        String name = getName(scan);
        greetToPoker(name);
        PokerHand playerHand = new PokerHand();
        PokerHand dealerHand = new PokerHand();
        Bettor wager = new Bettor(name, startBal, smallBlind); 
        boolean didFirstDrawOnCommandLine = false;    

        // Deck initialization
        Deck gameDeck = null; // This is required as try catch's are inferred to not succeed by compiler
        try{
            gameDeck = new Deck(-1); // -1 reshufflecount is just used to denote an unshuffled deck
            gameDeck.shuffle(rollReshuffleCount(11,44)); // sets the reshufflecount to a proper value, + shuffles deck
        } catch(PokerException e) 
        {
            e.printStackTrace();
            System.exit(1); // My general rule of thumb is all execption cases dealt with in main are meant to terminate the program
        }       

        if( args.length > 0 ) 
        {
                CmdLineInput.parseArguments(args, playerHand, dealerHand);// Note we need a try catch here because parseArgs uses addCard, which does have 'throws' functionality
                didFirstDrawOnCommandLine = true;
        }     
        
        do  ///////////////////////////////// Actual game ////////////////////////////////////
        {   
            printBalance(wager);
            // DRAW PHASE //
            if(didFirstDrawOnCommandLine == true) //Very ugly system for allowing normal running after a command line turn (I did not want to just copy the entire code below into the command line case)
                didFirstDrawOnCommandLine = false; 
            else
            {
                try { // Case of redrawing after hitting reshuffle in draw phase (guaranteed to not happen again, but catch is still required with my draw5() function)
                    drawPhase(playerHand, dealerHand, gameDeck);
                } catch(PokerException e) {
                    System.err.println("Shuffling did not reshuffle the deck, leading to a failed card deal."); // Should be impossible to happen (you never know! :) )
                    e.printStackTrace();
                    System.exit(1);
                }
            }


            boolean isFold = false;
             try{
                isFold = handleBet(wager, scan, true, playerHand, dealerHand);
            if(isFold) 
                continue;  
            } catch(PokerException e)
            {
                e.printStackTrace();
                System.exit(1);
            }

            // DISCARD PHASE //
            try {
            discardPhase(playerHand, dealerHand, gameDeck, scan);
            } catch(PokerException e)
            {
                e.printStackTrace();
                System.exit(1); //Note that the deal() error is caught INSIDE discardPhase, so this accounts for any error other than deal()'s (like the addCard(null) case )
            }

             // TODO: NEED TO MAKE MODULAR (PUT IN CLASS!!!!)
             try{
                isFold = handleBet(wager, scan, false, playerHand, dealerHand);
            if(isFold)
                continue;  
            } catch(PokerException e)
            {
                e.printStackTrace();
                System.exit(1);
            }



            // RESULTS PHASE //
            int playerComparator = -2; // 0 = same, -1 = less, 1 = greater 
            HandRank playerRank = playerHand.getHandRank();
            HandRank dealerRank =  dealerHand.getHandRank();
            try { // Did this to ensure separation of I/O from "backend"
                playerComparator = playerHand.compareTo(dealerHand);                    
            } catch(Exception e) // This is needed for getKickerArr()'s usage of getCard()
            {
                e.printStackTrace(); // printStackTrace also displays the message of exception
                System.exit(1);
            }                

            
            printResults(playerHand, dealerHand, playerRank, dealerRank, PokerHand.comparatorIntToHandResult(playerComparator));
            System.out.println(wager.collectWinnings(playerHand, dealerHand));

            //resets hands for next round 
            playerHand.clear();
            dealerHand.clear();
            System.out.println();
            wager.resetBet();
            printTotalWinnings(wager);
        } while ((wager.getBalance() >= wager.getEntryPay() * 2) && askIfContinue(scan)); // * 2 is just the assumption that small blind is 1/2 the value of the big blind, and the player MUST bet at LEAST the big blind to get past discard phase
        System.out.println("Ending balance: $" + wager.getBalance());
    } */

    /**                                                   
    *     Carries out the bet phase, but with handling for when a fold occurs (except it does not skip a round on its own, only prepares the round for being skipped)
    *     @param wager The object that keeps track of the player/dealer wagering
    *     @param scan Collects user input
    *     @param isFirstBet Changes behavior based on bet round (there are 2 bet rounds). Round 1 calls match the big blind, Round 2 calls skip the bet
    *     @param playerHand The player's hand to be displayed for making betting judgements 
    *     @param dealerHand The dealer's hand that is only used for the case of a fold (which initiates a round reset)
    *     @throws PokerException If withdrawing or betting more money than balance 
    *     @return True if fold occurs, false otherwise. This is to notify the caller that the round needs to be reset
    */
/*     public boolean handleBet(Bettor wager, Double bet, boolean isFirstBet, PokerHand playerHand, PokerHand dealerHand) throws PokerException
    {
            boolean isFold = betPhase(wager, scan, isFirstBet, playerHand);
            printPotVal(wager);
            //System.out.println();    /// NOTE : DEBUGGING CODE
            if(isFold) // STILL MIGHT ME AN ISSUE, NEED TO RESET HAND
            {
                playerHand.clear();
                dealerHand.clear();
                System.out.println(wager.getName() + " folded and lost $" + wager.getRoundWinnings());
                wager.subtractByWager();    
                printTotalWinnings(wager);
                wager.resetBet();
                System.out.println();
            }
            return isFold;
    } */


    /**                                                   
    *     Prints the balance of the player
    *     @param wager the object that keeps track of the player's wagering + balance
    */
 /*    public static void printBalance(Bettor wager)
    {
        System.out.println("Current balance: $" + wager.getBalance());
    } */

    /**                                                   
    *     Returns if string is an accepted betting comamand for poker
    *     @param s - The string being validated for being a command 
    *     @return True if string is an accepted poker command, false otherwise
    */
/*     public static boolean isValidBetCommand(String s)
    {
        switch(s)
        {
            case "C","c","R","r","F","f" -> {return true;}
            default -> {return false;}
        }
    } */

    /**                                                   
    *     Asks and collects input for making a betting decision
    *     @param scan Used to collect user input
    *     @return User's inputted bet instruction, in lowercase form
    */
 /*    public static String getBetInstruction(Scanner scan)
    {
        String s;
        do{
            System.out.print("Enter your bet action: C = Call, R = Raise, F = fold: ");
            s = scan.nextLine();
        } while(!isValidBetCommand(s));

        return s.toLowerCase();
    } */

    /**                                                   
    *     Validates if the passed raise value is an acceptable raise based on the current wager and balance 
    *     @param wager The object that keeps track of the player's wager
    *     @param raiseVal The proposed new raise value
    *     @return True if raise is valid, false otherwise
    */
/*      public static boolean isValidRaise(Bettor wager, double raiseVal) // Decided to implement this as it allows more custom "error" messages than if I did it in Bettor
    { // All raises must be > current bet, ALSO, > big blind
        double currBal = wager.getBalance();
        if(raiseVal < 0)
        {
            System.out.println("Raise of $" + raiseVal + " was negative."); //TODO: If doing raise, force more than curr bet?
            return false;
        }
        if(raiseVal > currBal)
        {
            System.out.println("Raise was higher than the current balance of $" + currBal); //TODO: If doing raise, force more than curr bet?
            return false;
        }
        else if(raiseVal < wager.getEntryPay() * 2)
        {
            System.out.println("Raise must be at least the value of the big blind, raise of " + raiseVal + " < " + (wager.getEntryPay() * 2) );
            return false;
        }
         else if(raiseVal < wager.getRoundWinnings()) //getRoundWinnings is to access the currWager
        {
            System.out.println("Raise must be at least the value of the your current bet, raise of " + raiseVal + " < " + (wager.getRoundWinnings()) );
            return false;
        }
        return true;
    } */

    /**                                                   
    *     Collects user/player's raise value with validation checking to ensure an acceptable value is given.
    *     @param wager  The object that keeps track of the player's wager
    *     @param scan Collects user's raise input
    *     @return The user's entered raise value
    */
    /*public static Double getUserRaise(Bettor wager, Scanner scan)
    {
        while(true) // Doesnt finish till proper input is recieved
        {

            System.out.print("What do you want to raise your wager to?: "); 
            Scanner stringScanner = new Scanner(scan.nextLine());
            if(stringScanner.hasNextDouble() )
            {
                Double ans = stringScanner.nextDouble();
                if(isValidRaise(wager, ans))
                {
                    stringScanner.close();
                    return ans;
                }
            }
            System.out.println("Input not accepted. Try again.");
            stringScanner.close();
        }          
    }
 */

//TODO BREAK EACH INTO SEPARATE FUNCTIONS

public void call(boolean isFirstBet) throws PokerException
{
    if(isFirstBet) // Case of matching big blind (first round)
        wager.placeBet(wager.getRoundWinnings() + wager.getEntryPay());
}

public void raise(double bet) throws PokerException
{
    wager.placeBet(bet);
}

public void nextRound()
{
    playerHand.clear();
    dealerHand.clear();
    wager.resetBet();
    draw();
}

public void fold() throws PokerException
{
    wager.subtractByWager();    
    wager.resetBet();
}

//Fold is just to do nothing, will move on to next phase

/* 
    public static boolean betPhase(Bettor wager, Scanner scan, boolean isFirstBet, PokerHand playerHand) throws PokerException
    { // Returns true if fold occurs

        String choice = getBetInstruction(scan);

        switch(choice)
        {
            case "c" -> 
            {
                if(isFirstBet) // Case of matching big blind (first round)
                    wager.placeBet(wager.getRoundWinnings() + wager.getEntryPay());
                //else is case of round 2, where call = check (bet of $0)
                // Case of check (does nothing)
                
            } // call                   
            case "r" -> 
            {
                wager.placeBet(getUserRaise(wager, scan)
            );} // raise
            //case "f" -> {} // fold is automatically done
            case "f" -> {return true;}
        }
        return false;
    } */

    /**                                                   
    *     Displays the total value being betting between dealer and player combined. Winner recieves this pot
    *     @param wager The object that simulates player/dealer wagering
    */
    public String getPotVal()
    {
        return Double.toString(wager.getRoundWinnings() * 2);
    }

    
    /**                                                   
    *     Displays the net winnings of the player in poker through @see fiveCard.Bettor#getTotalWinnings() getTotalWinnings
    *     @param wager The players wager object, keeps track of betting history
    */
  /*   public static void printTotalWinnings(Bettor wager)
    {
        double playerEarnings = wager.getTotalWinnings();
        if(playerEarnings > 0)
             System.out.println( "Your total earnings is $" + playerEarnings );
        else if(playerEarnings < 0)
            System.out.println( "Your total loss is  $" + playerEarnings );
        else
            System.out.println("You've currently broke even, get out while you can!");
    } */


 



    /////////////////////////////////////////////////////////////////////

    /**                                                   
    *     Adds 5 cards to the passed hand using the passed deck
    *     @param hand The player's hand, represented by the Hand object
    *     @param deck The dealer's hand, represented by the Hand object
    *     @throws PokerException When drawing past reshuffleCount
    */
    //Decided to implement draw 5 in here rather than deck as it is exclusive to the game of POKER
    static void draw5(PokerHand hand, Deck deck) throws PokerException
    {
        for(int i = 0; i < 5; i++)
            hand.addCard(deck.deal());
    }

    /**                                                                 
    *    Generates a value between the 2 parameters inclusively, to be used for deck's constructor to enter when
    *    the deck needs to be reshuffled (I made it here as I view reshuffleCount being randomized as a poker exclusive thing)
    *    @param min The min value that can be retured
    *    @param max The max value that can be returned
    *    @return The random number that was generated between min and max inclusive 
    */
    // Decided to implment reshuffleCount value here to make Deck.java more generalized (as this shufflecount aspect is unique to poker), even though theres still some poker specific aspects to Deck.java
    static int rollReshuffleCount(int min, int max) // 11-44 as i = 43 is the 44th element in an array. 43 is the last amount to allow shuffling issues to not occur
    {
        return (int) (Math.random() * (max - min + 1) + min);  //Referenced (I dislike Math.random(), but didn't want to have to import the Random library) from https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math/random (yes this is a JS source, not java)
    }

    /**                                                     
    *    Fills dealer and player hands with 5 cards each (hands should be empty before calling this).
    *    Also accounts for reshuffling, in which reshuffle will restart the draw if the reshuffle value is reached
    *    @param playerHand Player's poker hand for drawing 5 cards
    *    @param dealerHand Dealer's poker hand for drawing 5 cards
    *    @param deck The deck that cards are dealt from
    */
    public void drawPhase() throws PokerException
    {
         //Any case after the first command line OR if there never was a command line hand
        
            try
            {
                draw5(playerHand, gameDeck);
                draw5(dealerHand, gameDeck);
            } catch(PokerException e) // Deck.deal case, this allows us to draw 10 cards even if there is an out of bounds error, in which we know to reshuffle
            { // If we hit the rehsufflecount of draw phase, we should undo the draw, reshuffle, and draw again!
                gameDeck.shuffle(rollReshuffleCount(11, 44)); // We reshuffle if we hit the reshufflecount after the draw phase
                playerHand.clear(); // resets draws
                dealerHand.clear();
                    // Case of redrawing after hitting reshuffle in draw phase (guaranteed to not happen again, but catch is still required with my draw5() function)
                    draw5(playerHand, gameDeck);
                    draw5(dealerHand, gameDeck);
            }
    }

    @Override
    public void play(String... args) {
    // There is no use for this in our final project, but due to abstract classes, this must be implemented
    }

}


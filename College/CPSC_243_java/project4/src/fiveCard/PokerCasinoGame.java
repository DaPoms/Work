/**
 * implements the entirety of the game of poker through the fivecard package and   
 * game specific functions declared in this file. 
 * fiveCard.PokerCasinoGame.java
 * CPSC243 Spring 2026
 * @author Griffin Nye
 * @author (Modified By) Daniel Tripoli
 */

/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  April 21, 2026                           */
/* Due Date:       April 24, 2026                           */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #4                                       */
/* Filename:       PokerCasinoGame.java                     */
/* Purpose:        implements the entirety of the game of   */
/*                 poker through the fivecard package and   */
/*                 game specific functions declared in this */
/*                 file.                                    */
/************************************************************/

package fiveCard;

//import java.util.Arrays;
import java.util.Scanner;
import fiveCard.PokerHand.HandRank;
import fiveCard.PokerHand.HandResult;
import fiveCard.PokerHand.cardByCountAndRank;
import java.util.ArrayList;
import java.util.Comparator;

public class PokerCasinoGame extends CasinoCardGame {
    double startBal; // I decided to do this as its simpler than having a whole bettor 
                    //object in CasinoCardGame, and it gives more freedom for how a dev wants to manage balances (by making the subclass implement it)

    ///////////////////////////Project 4 code ///////////////////////////
    /**                                                   
    *     Constructor for the PokerCasinoGame object
    *     @param startBal The player's starting balance
    *     @throws PokerException If reshuffleCount is > 52
    */
    public PokerCasinoGame(double startBal) throws PokerException
    {
        Hand player = new PokerHand();
        Hand dealer = new PokerHand();
        super(player, dealer); // This is how we pass the hand type we want to the super class
        this.startBal = startBal;
    }

    /**                                                   
    *     Runs the entire poker game, carrying out drawing, dealing, discarding, and betting.
    *     @param args Command line argument for the case of starting with a premade hand
    */
    public void play(String... args)
    {
        int smallBlind = 25;
        Scanner scan = new Scanner(System.in);
        String name = getName(scan);
        greetToPoker(name);
        PokerHand playerHand = new PokerHand();
        PokerHand dealerHand = new PokerHand();
        Bettor<PokerHand> wager = new Bettor<>(name, startBal, smallBlind); 
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
    }

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
    public boolean handleBet(Bettor<PokerHand> wager, Scanner scan, boolean isFirstBet, PokerHand playerHand, PokerHand dealerHand) throws PokerException
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
    }


    /**                                                   
    *     Prints the balance of the player
    *     @param wager the object that keeps track of the player's wagering + balance
    */
    public static void printBalance(Bettor<PokerHand> wager)
    {
        System.out.println("Current balance: $" + wager.getBalance());
    }

    /**                                                   
    *     Returns if string is an accepted betting comamand for poker
    *     @param s - The string being validated for being a command 
    *     @return True if string is an accepted poker command, false otherwise
    */
    public static boolean isValidBetCommand(String s)
    {
        switch(s)
        {
            case "C","c","R","r","F","f" -> {return true;}
            default -> {return false;}
        }
    }

    /**                                                   
    *     Asks and collects input for making a betting decision
    *     @param scan Used to collect user input
    *     @return User's inputted bet instruction, in lowercase form
    */
    public static String getBetInstruction(Scanner scan)
    {
        String s;
        do{
            System.out.print("Enter your bet action: C = Call, R = Raise, F = fold: ");
            s = scan.nextLine();
        } while(!isValidBetCommand(s));

        return s.toLowerCase();
    }

    /**                                                   
    *     Validates if the passed raise value is an acceptable raise based on the current wager and balance 
    *     @param wager The object that keeps track of the player's wager
    *     @param raiseVal The proposed new raise value
    *     @return True if raise is valid, false otherwise
    */
    public static boolean isValidRaise(Bettor<PokerHand> wager, double raiseVal) // Decided to implement this as it allows more custom "error" messages than if I did it in Bettor
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
    }

    /**                                                   
    *     Collects user/player's raise value with validation checking to ensure an acceptable value is given.
    *     @param wager  The object that keeps track of the player's wager
    *     @param scan Collects user's raise input
    *     @return The user's entered raise value
    */
    public static Double getUserRaise(Bettor<PokerHand> wager, Scanner scan)
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


    /**                                                   
    *     Asks for bet and applies bet to a round of poker
    *     @param wager The object that keeps track of the player/dealer wagering
    *     @param scan Collects user input
    *     @param isFirstBet Changes behavior based on bet round (there are 2 bet rounds). Round 1 calls match the big blind, Round 2 calls skip the bet
    *     @param playerHand The player's hand to be displayed for making betting judgements 
    *     @throws PokerException If wagering more than balance (total money)
    *     @return True if fold occurs, false otherwise
    */
    public static boolean betPhase(Bettor<PokerHand> wager, Scanner scan, boolean isFirstBet, PokerHand playerHand) throws PokerException
    { // Returns true if fold occurs
        System.out.println("Betting phase:");
        System.out.println("Your hand: " + playerHand + "\nHand rank: " + playerHand.getHandRank());
        String choice = getBetInstruction(scan);

        switch(choice)
        {
            case "c" -> 
            {
                if(isFirstBet) // Case of matching big blind (first round)
                    wager.placeBet(wager.getRoundWinnings() + wager.getEntryPay());
                //else is case of round 2, where call = check (bet of $0)
                // Case of check (does nothing)
                
            } // call                         TODO: Ask if raise requires to be higher number than big blind
            case "r" -> 
            {
                wager.placeBet(getUserRaise(wager, scan)
            );} // raise
            //case "f" -> {} // fold is automatically done
            case "f" -> {return true;}
        }
        return false;
    }

    /**                                                   
    *     Displays the total value being betting between dealer and player combined. Winner recieves this pot
    *     @param wager The object that simulates player/dealer wagering
    */
    public static void printPotVal(Bettor<PokerHand> wager)
    {
        double playerBet = wager.getRoundWinnings();
        System.out.println("The pot has $" + playerBet * 2 + ". You bet $" + playerBet);
    }

    
    /**                                                   
    *     Displays the net winnings of the player in poker through @see fiveCard.Bettor#getTotalWinnings() getTotalWinnings
    *     @param wager The players wager object, keeps track of betting history
    */
    public static void printTotalWinnings(Bettor<PokerHand> wager)
    {
        double playerEarnings = wager.getTotalWinnings();
        if(playerEarnings > 0)
             System.out.println( "Your total earnings is $" + playerEarnings );
        else if(playerEarnings < 0)
            System.out.println( "Your total loss is  $" + playerEarnings );
        else
            System.out.println("You've currently broke even, get out while you can!");
    }


 



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
    * collects input and returns result as a string
    * @param cin The scanner we use to read input
    * @return The string representation of the user input
    */
    static String getName(Scanner cin) // Not very useful but it just lets us add context
    {
        System.out.print("What is your name?: ");
        return cin.nextLine();
    }

        ////////////////////// Project 3 code //////////////////////
    /**                                                                       
    *    Returns whether or not the integer array passed follows the expected values for a discard prompt in our poker game.
    *                     Main rules: must be numbers from 1-5, only 1 of each number, or -1 on its own. This function will report to the terminal what the
    *                     issue with the request was
    *    @param toBeDiscarded The Integer array that is to be validated
    *    @return True if the arraylist is of an acceptable discard prompt format, false otherwise.
    */
    static boolean isValidDiscardRequest(ArrayList<Integer> toBeDiscarded)
    {
        if(toBeDiscarded.size() > 5) 
        {
            System.err.println("Invalid input. The max amount of discards is 5, you entered " + toBeDiscarded.size()); // Am I FORCED to make these catch statements?
            return false; // If user deletes more cards that possible or duplicates, it is invalid
        }
        for (int i = 0; i < toBeDiscarded.size() - 1; i++)
        {
            int elem = toBeDiscarded.get(i);
            if(elem == toBeDiscarded.get(i+1))
            {
                System.err.println("Invalid input, referenced card " + elem + " more than once, only 1 allowed (for each card).");
                return false;  
            }
            if (elem < 1 || elem > 5) 
            {
                System.err.println("Invalid input, make sure the numbers entered are between 1-5 inclusive, \nor -1 on its own to skip discard. (" + elem + " was not accepted)");
                return false;
            }
        }

        if(toBeDiscarded.size() == 0)
        {
            System.err.println("Invalid input, nothing was entered.\nmake sure to enter numbers between 1-5 inclusive for picking cards to be discarded, \nor -1 on its own to skip discard");
            return false;
        }

        // Below is very ugly syntax, but it prevents us from having to do an additional for 0 to n loop
        if (toBeDiscarded.get(toBeDiscarded.size() - 1) < 1 || toBeDiscarded.get(toBeDiscarded.size() - 1) > 5) 
            {
                System.err.println("Invalid input, make sure the numbers entered are between 1-5 inclusive,  \nor -1 on its own to skip discard. (" + toBeDiscarded.get(toBeDiscarded.size() - 1) + " was not accepted)");
                return false;
            }
        return true; // It passed all the improper format cases, meaninng its a valid request!
    }

    /**                                                           
    * Asks the user for which cards they want to discard from the passed hand, ensuring that the user's answer is properly formatted.
    * @param playerHand - The hand that cards will be discarded from
    * @param scan Input stream for the user to give input
    * @return The Integer representation of the user's request, contains all the cards to be discarded. Will be empty if user skips the discard (with -1)
    */
    static ArrayList<Integer> askUserForDiscard(PokerHand playerHand, Scanner scan)
    {
        ArrayList<Integer> toBeDiscarded = new ArrayList<>();
        Scanner stringScanner;
        boolean isNotDoneInput = true;
        do // This due is for ensuring proper int format (no duplicates, 1-5 and -1 allowed only, but -1 must be on its OWN)
        {
            toBeDiscarded.clear(); // WE use array list to allow us to remove backwards, which makes card removal MUCH simpler   
            do{ // This do is for ensuring int only input
                System.out.println("-----------------------------\nYour turn\n-----------------------------\n" + "Hand: " + playerHand + "\nHand rank: " + playerHand.getHandRank() + "\nWhich cards do you want to remove?: \n[Use 1-5 with spaces between, 1 = first, 5 = last card in hand.\nEnter -1 ON ITS OWN to SKIP discard]"); 
                stringScanner = new Scanner(scan.nextLine());
                try{
                    while(stringScanner.hasNext())
                        toBeDiscarded.add(stringScanner.nextInt());
                    isNotDoneInput = false; // Input request is only reached here if the above function does not throw an exception, meaning the input only had ints
                } catch(Exception e)
                {
                    System.err.println("Invalid symbol of \"" + stringScanner.next() + "\" in input. Only numbers 1-5 and -1 on its own are accepted");
                }
            } while(isNotDoneInput);
            isNotDoneInput = true; // resets for second wave of validation, this is int validation (must be 1-5, or -1. No duplicates allowed)
            
            toBeDiscarded.sort(Comparator.naturalOrder()); // This is required for my isValidDiscardRequest, which checks for valid user input
            // Left of || accounts for skipping discard, right case counts for properely formatting a discard request for when to stop asking for input
            if( (toBeDiscarded.size() == 1 && toBeDiscarded.get(0) == -1) || (isValidDiscardRequest(toBeDiscarded)) ) // if we have more leftover, it means that something stopped the scanner prematurely (a non int/whitespace).
                isNotDoneInput = false;
        } while(isNotDoneInput);
        stringScanner.close();
        return toBeDiscarded;
    }

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
    static boolean userDiscard(PokerHand playerHand, Scanner scan, Deck deck) throws PokerException
    {
        boolean hasToReshuffledAfterDeal = false;
        ArrayList<Integer> playerCardsToBeDiscarded = askUserForDiscard(playerHand, scan);
        if((playerCardsToBeDiscarded.size() != 1 || playerCardsToBeDiscarded.get(0) != -1)) // Ensures we do not discard when user enters -1
        {
            // Can throw case of removing nonexistent card (should've been prevented by askUserForDiscard function)
            for(int i = playerCardsToBeDiscarded.size() - 1; i >= 0; i--) // Reverse order of removal ensures easy deletion (shifted elements have no impact on deletion)
                playerHand.removeCard(playerCardsToBeDiscarded.get(i) - 1); // We subtract 1 due to 0 indexed arrays (The user enters 1 for index 0)
            
            for(int i = 0; i < playerCardsToBeDiscarded.size(); i++) // Refills the hand with new cards
                try{
                    if(deck.getTop() >=  deck.getReshuffleCount()) // Checks for if we hit reshuffleCount mid-discard
                        hasToReshuffledAfterDeal = true;
                    playerHand.addCard((deck.deal()));
                } catch(PokerException e)
                {
                    playerHand.addCard((deck.dealIgnoringReshuffle())); // For discard, we are allowed to deal cards past rehufflecount
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
    static boolean dealerDiscard(PokerHand dealerHand, Deck deck) throws PokerException // Dealer is the "AI"
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
                dealerHand.addCard(deck.deal());
                } catch(PokerException e)
                {
                    dealerHand.addCard(deck.dealIgnoringReshuffle());
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
                    dealerHand.addCard(deck.deal());
                } catch(PokerException e)
                {
                    dealerHand.addCard(deck.dealIgnoringReshuffle());
                }
            }
        }

        if(deck.getTop() >=  deck.getReshuffleCount()) // Checks for if we hit reshuffleCount mid-discard
            return true;

        return false; //returns that reshuffle is not needed
    }

    /**                                                          
    *    Covers both the player and dealer's turn during the discard phase of poker. 
    *    Also accounts for if a reshuffle is needed after the discard phase
    *    @param playerHand Player's poker hand for their discard turn
    *    @param dealerHand Dealer's poker hand for their discard turn
    *    @param deck The deck that cards are dealt from
    *    @param scan - The input stream for user input
    *   @throws PokerException If drawing a null card to hand   
    */
    static void discardPhase(PokerHand playerHand, PokerHand dealerHand, Deck deck, Scanner scan) throws PokerException
    {
        System.out.println("-----------------------------\nDiscard phase:"); 
        boolean hasToReshuffledAfterDealUser = userDiscard(playerHand, scan, deck);
        boolean hasToReshuffledAfterDealDealer = dealerDiscard(dealerHand, deck);
        if(hasToReshuffledAfterDealUser || hasToReshuffledAfterDealDealer) // Reshuffle case (happens AFTER the discard phase)
            {
                deck.shuffle(rollReshuffleCount(11, 44));
        }
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
    static void drawPhase(PokerHand playerHand, PokerHand dealerHand, Deck gameDeck) throws PokerException
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

    /**
    *    Keeps on asking the user if they want to continue poker till they answer y for yes or n for no (not case sensitive)
    *    @param scan The input stream for user input
    *    @return Returns true if response designates user wants to continue ("y"), false for "n"    
    */
    static boolean askIfContinue(Scanner cin)
    {
        do
        {
            System.out.print("Do you want to play another game of Poker? (enter 'Y' for yes, or 'N' for no): ");
            switch (cin.nextLine())
            {
                case "Y", "y" -> {return true;}
                case "N", "n" -> {return false;}
            };
        }
        while (true);
    }

    /**
    *    Asks for the user's name and greets them to poker
    *    @param scan The input stream for user input    
    */
    static void greetToPoker(String name)
    {
        System.out.println("Welcome to poker " + name + "!");
    }

    /**
    *                                                                            
    *    Prints the results of the game of poker from the perspective of the user
    *    @param playerHand Player's final poker hand to be displayed
    *    @param dealerHand Dealer's final poker hand to be displayed
    *    @param playerRank The rank of the player's hand
    *    @param dealerRank The rank of the dealer's hand
    *    @param isPlayerWinner Whether the player won or not     
    */
    // I think this is allowed? (for the "separation of IO")
    static void printResults(PokerHand playerHand, PokerHand dealerHand, HandRank playerRank, HandRank dealerRank, HandResult isPlayerWinner)
    {
        System.out.println("-----------------------------\nYour results:\nHand: " + playerHand + "\nHand Rank: " + playerRank + "\n-----------------------------");
        System.out.println(                               "Dealer's results:\nHand: " + dealerHand + "\nHand Rank: " + dealerRank + "\n-----------------------------");
        System.out.println("Result: you " + isPlayerWinner.getStringResults() + "!");  
    }

    public static void main(String[] args) 
    {
        PokerCasinoGame pokerGame = null;
        try{
            pokerGame = new PokerCasinoGame(1000);
        } catch (PokerException e)
        {
            e.printStackTrace();
            System.exit(1);
        }
        pokerGame.play(args); //play deals with most exceptions
    }//end main
}//end Game



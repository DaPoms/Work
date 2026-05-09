/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  April 21, 2026                           */
/* Due Date:       May 16th, 2026                           */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #6                                       */
/* Filename:       PokerCasinoGame.java                     */
/* Purpose:        implements the entirety of the game of   */
/*                 poker through the fivecard package and   */
/*                 game specific functions declared in this */
/*                 file.                                    */
/************************************************************/
package fiveCard;
import fiveCard.PokerHand.HandRank;
import fiveCard.PokerHand.cardByCountAndRank;
import java.util.ArrayList;

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

        ///////////////////////////Project 6 code ///////////////////////////
        /**                 
        *    Returns a reference to the player's hand
        *    @return A reference to the player's hand
        */
        public PokerHand getPlayerHand() {return playerHand;}

        /**                 
        *    Returns a reference to the dealer's hand
        *    @return A reference to the dealer's hand
        */
        public PokerHand getDealerHand() {return dealerHand;}

        /**                 
        *    Returns the current balance of the user
        *    @return The user's current balance
        */
        public Double getBalance() {return wager.getBalance();}

        /**                 
        *    Returns the user's current wager value 
        *    @return The current wager value of the user
        */
        public Double getWager() {return wager.getRoundWinnings();}

        /**                 
        *    Returns a reference to the wager object
        *    @return A reference to the wager object
        */
        public Bettor getWagerObject() {return wager;}

        /**                 
        *    Returns the cost required to reach the big blind
        *    @return The cost required to reach the big blind from the user's perspective
        */
        public double getEntryPay() {return wager.getEntryPay();} // Just passes function up for easier access

        /**                 
        *    Fills both the player and dealer hand with cards
        */
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

    /**                                                                    
    *    The full behavior of the user's discard: both asks the user which cards to discard,
    *    carries out the discard, and draws cards for the cards removed.
    *    @param playerHand The hand that the discards are done on
    *    @param scan The input stream for user input
    *    @param deck - The deck that cards are dealt from
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

    /**                                                      
    *   Covers both the player and dealer's turn during the discard phase of poker. 
    *   Also accounts for if a reshuffle is needed after the discard phase
    *   @param playerCardsToBeDiscarded The indexes in the player's hand that will be discarded
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
            CmdLineInput.parseArguments(args, playerHand, dealerHand);// Note we need a try catch here because parseArgs uses addCard, which does have 'throws' functionality
           
    }

    /**                 
    *    Raises the user's bet to the big blind (or does nothing in the case of the 2nd betting round, so long as isFirstBet is properly set)                                    
    *    @param isFirstBet True if on the 1st bet, false otherwise. Only the 1st bet affects a user's wager
    *    @throws PokerException If the call requires more money than the current balance or the blind is negative 
    */
    public void call(boolean isFirstBet) throws PokerException
    {
        if(isFirstBet) // Case of matching big blind (first round)
            wager.placeBet(wager.getRoundWinnings() + wager.getEntryPay());
    }

    /**                 
    *    Raises the user's bet by the passed value                                     
    *    @param bet The value of the bet
    *    @throws PokerException If trying to wager more than the current balance or a negative number 
    */
    public void raise(double bet) throws PokerException
    {
        wager.placeBet(bet);
    }

    /**                                                     
    *    Resets both the dealer and player's hands and draws new hands
    */
    public void nextRound()
    {
        playerHand.clear();
        dealerHand.clear();
        wager.resetBet();
        draw();
    }

    /**                                                     
    *   Implements the wager behaviors of folding. User loses their bet money and their bet gets reset for the next round
    *   @throws PokerException If more money is taken from the user's balance than they have
    */
    public void foldWager() throws PokerException
    {
        wager.subtractByWager();    
        wager.resetBet();
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
    */
    public void drawPhase() throws PokerException
    {        
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
}


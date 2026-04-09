/**
 * fiveCard.PokerGame.java
 * CPSC243 Spring 2026
 * @author Griffin Nye
 */

/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  Match 30, 2026                           */
/* Due Date:       April 6, 2026                            */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #3                                       */
/* Filename:       PokerGame.java                           */
/* Purpose:        implements the entirety of the game of   */
/*                 poker through the fivecard package and   */
/*                 game specific functions declared in this */
/*                 file.                                    */
/************************************************************/

package fiveCard;

//import java.util.Arrays;
import java.util.Scanner;
import fiveCard.Card.Rank;
import fiveCard.PokerHand.HandRank;
import fiveCard.PokerHand.cardByCountAndRank;
import java.util.ArrayList;
import java.util.Comparator;

/**
 * Generate and play a hand of Poker
 */
public class PokerGame {
    //representation of a poker game's result
    private enum GameResult 
    {
        WIN("win"),
        LOSE("lose"),
        PUSH("push");
        final String resultName;
        GameResult(String resultName){ this.resultName = resultName;}

    /*************************************************************************/
    /*                                                                        
    /* Function name:   getStringResults  
    /* Description:     Evaluates the result of a poker game in a string representation so that it can be printed
    /* Parameters:      none
    /* Return Value:    String - The string representation of the game result (do note that enum GameResult does have a string representation through .resultName, but it is not in the desired format)
    /*
    /*************************************************************************/
        String getStringResults()
        {
            switch (this)
            {
                case WIN, LOSE -> {return "You " + resultName + "!";}
                default -> {return resultName;} //case of push
            }
        }
    }



    /*************************************************************************/
    /*                                                                        
    /* Function name:   breakTie
    /* Description:     Breaks a tie for the case of pair based hand rankings (non kicker cards) and returns the result of this tie break
    /* Parameters:      cardByCountAndRank[] playerTop2Cards - The player's array of their top 2 cards by card rank count (like pairs, three of a kind, etc..)
                        cardByCountAndRank[] dealerTop2Cards - The dealer's array of their top 2 cards by card rank count (like pairs, three of a kind, etc..)
                        int handRankVal - The int representation of hand rank (only used to check one edge case)
    /* Return Value:    GameResult - The result of the break tie. Win and lose entail the entire hand was won or lost, but push means that the non kicker cards all tied and the kickers must then be considered
    /*
    /*************************************************************************/
    static GameResult breakTie(cardByCountAndRank[] playerTop2Cards, cardByCountAndRank[] dealerTop2Cards, int handRankVal)
    {
        if(handRankVal == HandRank.TWO_PAIR.ordinal())
        {
            sortTop2CardArrayByRank(playerTop2Cards); // we do this to re-sort the hand by rank, as top2PairCount originally sorts by COUNT. This is really ony luseful for two pair
            sortTop2CardArrayByRank(dealerTop2Cards);
        }

        for(int i = 0; i < playerTop2Cards.length; i++) // Actually checking the kickers to break up the tie
        {
            int playerVSDealerScoreDiff = playerTop2Cards[i].getCardRankVal() - dealerTop2Cards[i].getCardRankVal();
            if(playerVSDealerScoreDiff < 0) //If player score was smaller than dealer, than this val is negative
                return GameResult.LOSE;
            else if (playerVSDealerScoreDiff > 0)
                return GameResult.WIN;
        }
        return GameResult.PUSH; // if after all of these checks, all cards are seen as identical in rank, then a push has resulted
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   breakTie
    /* Description:     Breaks a tie by comparing the entirety of the hands passed through by card ranks 
    /* Parameters:      int[] intPlayerHand - The player's int representation of their hand, with the ints attributed to rank value
    /*                  int[] intDealerHand - The dealer's int representation of their hand, with the ints attributed to rank value
    /* Return Value:    GameResult - The result of the tie break. Win and lose entail the entire hand was won or lost, push guarantees that a complete tie occured
    /*
    /*************************************************************************/
    static GameResult breakTie(int[] intPlayerHand, int[] intDealerHand) 
    {  
        for(int i = intPlayerHand.length - 1; i >= 0; i--) // Actually checking the kickers to break up the tie
        {
            int playerVSDealerScoreDiff = intPlayerHand[i] - intDealerHand[i];
            if(playerVSDealerScoreDiff < 0) //If player score was smaller than dealer, than this val is negative
                return GameResult.LOSE;
            else if (playerVSDealerScoreDiff > 0)
                return GameResult.WIN; 
        }
        return GameResult.PUSH; // if after all of these checks, all cards are seen as identical in rank, then a push has resulted
    }


    /*************************************************************************/
    /*                                                                        
    /* Function name:   getKickerArr
    /* Description:     This function is solely for when the hand type is one that has nonkicker cards. It creates an array that is of only the kicker cards.
    /* Parameters:      Hand hand - The hand containing all of the cards
    /*                  cardByCountAndRank[] top2Cards - Contains that cards that are considered non kicker cards (the ones avoid in the array that's returned)
    /*                  int nonKickerCardCount - Used to declare the size of the array, the amount of nonkicker cards the hand has. (alternative would've been to use an arraylist) 
    /* Return Value:    int[] - The int representation of the passed hand, with the non kicker cards not included.
    /*
    /*************************************************************************/
    static int[] getKickerArr(Hand hand, cardByCountAndRank[] top2Cards, int nonKickerCardCount) throws PokerException
    {
        int[] kickerArr = new int[hand.getCardCount() - nonKickerCardCount];
        int addI = 0;
        for(int i = 0; i < hand.getCardCount(); i++) // this initializes the kicker array, it effectively just removed cards that contributed to the hand ranking from the 
        {
            int cardVal = hand.getCard(i).getValue();
             if(cardVal != top2Cards[0].getCardRankVal() && (top2Cards[1].getCardCount() == 1 || cardVal != top2Cards[1].getCardRankVal() ) )
                kickerArr[addI++] = cardVal;
        }
        return kickerArr;
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   kickerBreakTie
    /* Description:     Determines the kickers of both hands and breaks the tie on the kicker cards, returning the game result.
    /* Parameters:      Hand player - The poker hand of the player
                        Hand dealer - The poker hand of the dealer
    /*                  cardByCountAndRank[] playerTop2Cards - The player's array of their top 2 cards by card rank count (like pairs, three of a kind, etc..). Used to isolate nonkicker cards
                        cardByCountAndRank[] dealerTop2Cards - The dealer's array of their top 2 cards by card rank count (like pairs, three of a kind, etc..). Used to isolate nonkicker cards    
    /* Return Value:    GameResult - The result of the tie break. Win and lose entail the entire hand was won or lost, push guarantees that a complete tie occured
    /*
    /*************************************************************************/
    static GameResult kickerBreakTie(Hand player, Hand dealer, cardByCountAndRank[] playerTop2Cards, cardByCountAndRank[] dealerTop2Cards) throws PokerException
    {
        int mainHandCardCount = 0;
        for(cardByCountAndRank card : playerTop2Cards)
            if(card.getCardCount() > 1)
                mainHandCardCount += card.getCardCount();

        int[] playerKickers = getKickerArr(player, playerTop2Cards, mainHandCardCount); // I could've done a plethora of things for this, but found this to be the simplest way to exclude the cards already compared that contributed to the hand rank 
        int[] dealerKickers =  getKickerArr(dealer, dealerTop2Cards, mainHandCardCount); // we need to subtract by the count of each main card Count
    
        return breakTie(playerKickers, dealerKickers);
    }    

    /*************************************************************************/
    /*                                                                        
    /* Function name:   sortTop2CardArrayByRank
    /* Description:     Makes the passed array's first to elements sorted from greatest to least by card rank
    /* Parameters:      cardByCountAndRank[] arr - The array of 2 elements that we want to sort
    /* Return Value:    void
    /*
    /*************************************************************************/
    static void sortTop2CardArrayByRank(cardByCountAndRank[] arr)
    {
        cardByCountAndRank placeholder;
        if(arr[0].getCardRankVal() < arr[1].getCardRankVal()) //resorts the array by card rank rather than count (its sorted by count by default, but for ties, we only care about rank)
        {
            placeholder = arr[0];
            arr[0] = arr[1];
            arr[1] = placeholder;
        }

    }
    /*************************************************************************/
    /*                                                                        
    /* Function name:   insertAceToFront
    /* Description:     Inserts an ace to the front of the hand at the lowest possible card value in place (as in doesn't return a separate array).
    /* Parameters:      int[] hand - the hand we insert the ace into
    /* Return Value:    void
    /*
    /*************************************************************************/
    static void insertAceToFront(int[] hand)
    {
         for(int i = hand.length - 1; i > 0; i--)
            hand[i] = hand[i - 1];
        hand[0] = -1; // a low value ace is represented by a value of -1 instead of 12
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   hasAceAsLowest
    /* Description:     Evaluates if hand has an ace and if the ace is treated as lowest card in the hand or not
    /* Parameters:      int[] hand - the hand we insert the ace into
    /*                  HandRank rankType - The hand rank of the hand we pass through
    /* Return Value:    boolean - Returns true if ace is treated as the lowest card for the given hand, false otherwise
    /*
    /*************************************************************************/
    static boolean hasAceAsLowest(int[] hand, HandRank rankType)
    {
        if(rankType == HandRank.STRAIGHT || rankType == HandRank.STRAIGHT_FLUSH) // these are the cases where we have to check is Ace exists, and then if ace should be treated as low or high value  
        {
            if(hand[0] < Rank.TEN.ordinal() && hand[hand.length - 1] == Rank.ACE.ordinal()) // since we know straight / straight flush is in ascending order,  if you have an ace and the lowest valued card at < 10, then it must be A 2 3 4 5 in order for it to be ascending
                return true;
        }
        return false;
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   adjustAceValueIfNeeded
    /* Description:     When hand contains an ace, checks if hand uses ace as lowest value and sets it to be the lowest value if so.
    /* Parameters:      int[] hand - the hand we search
    /*                  HandRank rankType - The hand rank of the hand we pass through
    /* Return Value:    void
    /*
    /*************************************************************************/
    static void adjustAceValueIfNeeded(int[] hand, HandRank rankType)
    {
            if(hasAceAsLowest(hand, rankType)) //since we   
                insertAceToFront(hand);
    }
    /*************************************************************************/
    /*                                                                        
    /* Function name:   isPlayerWinnerForTie
    /* Description:     Contains all the functionality for determining the winner of a tie.
    /* Parameters:      HandRank rankType - The hand rank of the hand we pass through
    /*                  Hand player - An object that is the player's poker hand
    /*                  Hand dealer - An object that is the dealer's poker hand
    /* Return Value:    GameResult - Returns WIN if the player wins, LOSE if they lose, and PUSH if theres a complete tie
    /*
    /*************************************************************************/
     static GameResult isPlayerWinnerForTie(HandRank rankType, PokerHand player, PokerHand dealer) throws PokerException //has to account properly for ties. rankType is passed just to take advantage of isPlayerWinner already using getHandRank()
    {
        int handRankVal = rankType.ordinal();

        // rank types where the full hand is not included in the hand ranking
        if(hasKickers(rankType) && rankType != HandRank.HIGH_CARD)
        { // we are guaranteed to do one pair check for anything that enters here
            cardByCountAndRank[] playerTop2Cards = player.top2PairCount();
            cardByCountAndRank[] dealerTop2Cards = dealer.top2PairCount();

            GameResult nonKickerResult = breakTie(playerTop2Cards, dealerTop2Cards, handRankVal); 
            if (nonKickerResult != GameResult.PUSH)
                return nonKickerResult; //if we break the tie without using kickers, then we've determined the game result
            else //if a push occurs for the non kicker cards, then we must explore the kicker cards to break the tie (or determine if it's truly a push)
                return kickerBreakTie(player, dealer, playerTop2Cards, dealerTop2Cards);            
        }
        //case of every other poker hand (you just search from highest to lowest ranking)

        int[] intPlayerHand = player.getRankArray();
        int[] intDealerHand = dealer.getRankArray();
        adjustAceValueIfNeeded(intPlayerHand, rankType); // checks for case where ace can be treated as a value lower than 2 and assigns it with a lower value than 2 if it means the lower value ace condition
        adjustAceValueIfNeeded(intDealerHand, rankType);
        
        return breakTie(intPlayerHand, intDealerHand);
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   hasKickers 
    /* Description:     Determines if the handRank has kickers or not, based on poker definitions for hand ranks.
    /* Parameters:      HandRank handRank - The rank we check for kickers
    /* Return Value:    boolean - true if it does have kickers, false otherwise
    /*
    /*************************************************************************/
    static boolean hasKickers(HandRank handRank) 
    {
        switch(handRank)
        {
            case HIGH_CARD, ONE_PAIR, TWO_PAIR, THREE_OF_A_KIND, FOUR_OF_A_KIND -> {return true;}
            default -> {return false;}
        }
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   isPlayerWinner 
    /* Description:     Contains all the functionality for determining the winner of a single poker game
    /* Parameters:      Hand player - The player's hand, represented by the Hand object
    /*                  Hand dealer - The dealer's hand, represented by the Hand object
    /* Return Value:    GameResult - Returns WIN if the player wins, LOSE if they lose, and PUSH if theres a complete tie
    /*
    /*************************************************************************/
    static GameResult isPlayerWinner(PokerHand player, PokerHand dealer) throws PokerException
    {
        
        HandRank playerRanking = player.getHandRank();
        HandRank dealerRanking = dealer.getHandRank();
        if( playerRanking.ordinal() > dealerRanking.ordinal() )
            return GameResult.WIN;
        else if( playerRanking.ordinal() < dealerRanking.ordinal() )
            return GameResult.LOSE;
        else // case of tie (hand types are equal)
            return isPlayerWinnerForTie(playerRanking, player, dealer); //doesnt matter if first param is player or dealer ranking since they are the same by this else statement
            // anything with a GameResult of push here will need to have the non kicker's REMOVED
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   draw5
    /* Description:     Adds 5 cards to the passed hand using the passed deck
    /* Parameters:      Hand player - The player's hand, represented by the Hand object
    /*                  Hand dealer - The dealer's hand, represented by the Hand object
    /* Return Value:    void
    /*
    /*************************************************************************/
    //Decided to implement draw 5 in here rather than deck as it is exclusive to the game of POKER
    static void draw5(PokerHand hand, Deck deck) throws PokerException
    {
        for(int i = 0; i < 5; i++)
            hand.addCard(deck.deal());
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   getName
    /* Description:     colleccts input and returns result as a string
    /* Parameters:      Scanner cin - The scanner we use to read input
    /* Return Value:    String - The string representation of the user input
    /*
    /*************************************************************************/
    static String getName(Scanner cin) // Not very useful but it just lets us add context
    {
        return cin.nextLine();
    }

    ////////////////////// Project 3 code //////////////////////
    /*************************************************************************/
    /*                                                                        
    /* Function name:   isValidDiscardRequest
    /* Description:     Returns whether or not the integer array passed follows the expected values for a discard prompt in our poker game.
    /*                  Main rules: must be numbers from 1-5, only 1 of each number, or -1 on its own. This function will report to the terminal what the
    /*                  issue with the request was
    /* Parameters:      ArrayList<Integer> toBeDiscarded - The Integer array that is to be validated
    /* Return Value:    boolean - True if the arraylist is of an acceptable discard prompt format, false otherwise.
    /*
    /*************************************************************************/
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

    /*************************************************************************/
    /*                                                                        
    /* Function name:   askUserForDiscard
    /* Description:     Asks the user for which cards they want to discard from the passed hand, ensuring that the user's answer is properly formatted.
    /* Parameters:      PokerHand playerHand - The hand that cards will be discarded from
    /*                  Scanner scan - Input stream for the user to give input
    /* Return Value:    ArrayList<Integer> - The Integer representation of the user's request, contains all the cards to be discarded.
    /*                                       Will be empty if user skips the discard (with -1)
    /*
    /*************************************************************************/
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

    /*************************************************************************/
    /*                                                                        
    /* Function name:   userDiscard
    /* Description:     The full behavior of the user's discard: both asks the user which cards to discard,
    /*                  carries out the discard, and draws cards for the cards removed.
    /* Parameters:      PokerHand playerHand - The hand that the discards are done on
    /*                  Scanner scan - The input stream for user input
    /*                  Deck deck - The deck that cards are dealt from
    /* Return Value:    boolean - Returns whether or not the deck needs to be shuffled after the discard
    /*
    /*************************************************************************/
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

    /*************************************************************************/
    /*                                                                        
    /* Function name:   dealerDiscard
    /* Description:     The full behavior of the dealer's discard: follows rules to,
    /*                  carry out discards based on hand rank, and draws cards for the cards removed.
    /* Parameters:      PokerHand dealerHand - The hand that the discards are done on
    /*                  Deck deck - The deck that cards are dealt from
    /* Return Value:    boolean - Returns whether or not the deck needs to be shuffled after the discard
    /*
    /*************************************************************************/
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

    /*************************************************************************/
    /*                                                                        
    /* Function name:   discardPhase
    /* Description:     Covers both the player and dealer's turn during the discard phase of poker. 
    /*                  Also accounts for if a reshuffle is needed after the discard phase
    /* Parameters:      PokerHand playerHand - player's poker hand for their discard turn
    /*                  PokerHand dealerHand - dealer's poker hand for their discard turn
    /*                  Deck deck - The deck that cards are dealt from
    /*                  Scanner scan - The input stream for user input
    /* Return Value:    none
    /*
    /*************************************************************************/
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
    
    /*************************************************************************/
    /*                                                                        
    /* Function name:   rollReshuffleCount
    /* Description:     Generates a value between the 2 parameters inclusively, to be used for deck's constructor to enter when
    /*                  the deck needs to be reshuffled (I made it here as I view reshuffleCount being randomized as a poker exclusive thing)
    /* Parameters:      int min - The min value that can be retured
    /*                  int max - The max value taht can be returned
    /* Return Value:    int - The random number that was generated between min and max inclusive
    /*
    /*************************************************************************/
    // Decided to implment reshuffleCount value here to make Deck.java more generalized (as this shufflecount aspect is unique to poker), even though theres still some poker specific aspects to Deck.java
    static int rollReshuffleCount(int min, int max) // 11-44 as i = 43 is the 44th element in an array. 43 is the last amount to allow shuffling issues to not occur
    {
        return (int) (Math.random() * (max - min + 1) + min);  //Referenced (I dislike Math.random(), but didn't want to have to import the Random library) from https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math/random (yes this is a JS source, not java)
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   drawPhase
    /* Description:     Fills dealer and player hands with 5 cards each (hands should be empty before calling this).
    /*                  Also accounts for reshuffling, in which reshuffle will restart the draw if the reshuffle value is reached
    /* Parameters:      PokerHand playerHand - player's poker hand for drawing 5 cards
    /*                  PokerHand dealerHand - dealer's poker hand for drawing 5 cards
    /*                  Deck deck - The deck that cards are dealt from
    /* Return Value:    void
    /*
    /*************************************************************************/
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

    /*************************************************************************/
    /*                                                                        
    /* Function name:   askIfContinue
    /* Description:     Keeps on asking the user if they want to continue poker till they answer y for yes or n for no (not case sensitive)
    /* Parameters:      Scanner scan - The input stream for user input
    /* Return Value:    boolean - Returns true if response designates user wants to continue ("y"), false for "n"
    /*
    /*************************************************************************/
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

    /*************************************************************************/
    /*                                                                        
    /* Function name:   greetToPoker
    /* Description:     Asks for the user's name and greets them to poker
    /* Parameters:      Scanner scan - The input stream for user input
    /* Return Value:    none
    /*
    /*************************************************************************/
    static void greetToPoker(Scanner scan)
    {
        System.out.print("What is your name?: ");
        System.out.println("Welcome to poker " + getName(scan) + "!");
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   printResults
    /* Description:     Prints the results of the game of poker from the perspective of the user
    /* Parameters:      PokerHand playerHand - player's final poker hand to be displayed
    /*                  PokerHand dealerHand - dealer's final poker hand to be displayed
    /*                  HandRank playerRank - The rank of the player's hand
    /*                  HandRank dealerRank - The rank of the dealer's hand
    /*                  GameResult isPlayerWinner - Whether the player won or not 
    /* Return Value:    none
    /*
    /*************************************************************************/
    // I think this is allowed? (for the "separation of IO")
    static void printResults(PokerHand playerHand, PokerHand dealerHand, HandRank playerRank, HandRank dealerRank, GameResult isPlayerWinner)
    {
        System.out.println("-----------------------------\nYour results:\nHand: " + playerHand + "\nHand Rank: " + playerRank + "\n-----------------------------");
        System.out.println(                               "Dealer's results:\nHand: " + dealerHand + "\nHand Rank: " + dealerRank + "\n-----------------------------");
        System.out.println("Result: " + isPlayerWinner.getStringResults());  
    }



    public static void main(String[] args) 
    {
        Scanner scan = new Scanner(System.in);
        greetToPoker(scan);
        PokerHand playerHand = new PokerHand();
        PokerHand dealerHand = new PokerHand();
        boolean didFirstDrawOnCommandLine = false;    

        // Deck initialization
        Deck gameDeck = null; // This is required as try catch's are inferred to not succeed by compiler
        try{
        //JUST FOLLOWING ORDERS:  The instructions said that Deck must have reshufflecount as a parameter, but you can see here,
        //  this just wastes the reshufflecount value (as my deck needs to be shuffled after this, and shuffling resets the reshufflecount)
            gameDeck = new Deck(-1); // -1 reshufflecount is just used to denote an unshuffled deck
            gameDeck.shuffle(rollReshuffleCount(11,44)); // sets the reshufflecount to a proper value, + shuffles deck
        } catch(PokerException e) // Case of out of bounds reshuffleCount (I did if > 52 as thats the size of the deck)
        {
            e.printStackTrace();
            System.exit(1); // My general rule of thumb is all execption cases dealt with in main are meant to terminate the program
        }

        // Command line input (of first poker game only)
        if( args.length > 0 ) 
        {
            try
            {
                CmdLineInput.parseArguments(args, playerHand, dealerHand);// Note we need a try catch here because parseArgs uses addCard, which does have 'throws' functionality
                didFirstDrawOnCommandLine = true;
            }
            catch(PokerException e) 
            {
                e.printStackTrace();
                System.exit(1);
            }
        }             
        
        do
        {   
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

            // DISCARD PHASE //
            try {
            discardPhase(playerHand, dealerHand, gameDeck, scan);
            } catch(PokerException e)
            {
                e.printStackTrace();
                System.exit(1); //Note that the deal() error is caught INSIDE discardPhase, so this accounts for any error other than deal()'s (like the addCard(null) case )
            }

            // RESULTS PHASE //
            GameResult isPlayerWinner = null;
            HandRank playerRank = playerHand.getHandRank();
            HandRank dealerRank =  dealerHand.getHandRank();
            try { // Did this to ensure separation of I/O from "backend"
                isPlayerWinner = isPlayerWinner(playerHand, dealerHand);                    
            } catch(PokerException e) // This is needed for getKickerArr()'s usage of getCard()
            {
                e.printStackTrace(); // printStackTrace also displays the message of exception
                System.exit(1);
            }                
            printResults(playerHand, dealerHand, playerRank, dealerRank, isPlayerWinner);

            //resets hands for next round 
            playerHand.clear();
            dealerHand.clear();
        } while (askIfContinue(scan));
    
    }//end main

}//end Game



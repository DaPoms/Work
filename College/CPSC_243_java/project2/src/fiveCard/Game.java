/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  February 26, 2026                        */
/* Due Date:       Match 13, 2026                           */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #2                                       */
/* Filename:       Game.java                                */
/* Purpose:        Impliments the entirety of the game of   */
/*                 poker through the fivecard package and   */
/*                 game specific functions declared in this */
/*                 file.                                    */
/************************************************************/

/**
 * fiveCard.Game.java
 * CPSC243 Spring 2026
 * @author Griffin Nye
 */

// cd "/c/Users/Daniel Worktop/VsProjects/Work/CPSC_243_java/project2/"
// cd /c/Users/Pomer/projects/CPSC_243_java/project2


package fiveCard;

import java.util.Arrays;
import java.util.Scanner;

import fiveCard.Card.Rank;
import fiveCard.Hand.HandRank;
import fiveCard.Hand.cardByCountAndRank;






/**
 * Generate and play a hand of Poker
 */
class Game {
    //representation of a poker game's result
    private enum GameResult 
    {
        WIN("win"),
        LOSE("lose"),
        PUSH("push");
        final String resultName;
        GameResult(String resultName){ this.resultName = resultName;}
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
    static int[] getKickerArr(Hand hand, cardByCountAndRank[] top2Cards, int nonKickerCardCount)
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
    static GameResult kickerBreakTie(Hand player, Hand dealer, cardByCountAndRank[] playerTop2Cards, cardByCountAndRank[] dealerTop2Cards)
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
     static GameResult isPlayerWinnerForTie(HandRank rankType, Hand player, Hand dealer) //has to account properly for ties. rankType is passed just to take advantage of isPlayerWinner already using getHandRank()
    { //check for tie in hand ranking portion, we NEED TO IMPLIMENT RETURNING WHAT KICKERS ARE (CARDS THAT ARE NOT PART OF THE HAND RANK (TWO_PAIR ETC...))
        int handRankVal = rankType.ordinal();

        // rank types where the full hand is not included in the hand ranking
        if(hasKickers(rankType) && rankType != HandRank.HIGH_CARD)
        { // we are guaranteed to do one pair check for anything that enters here
            cardByCountAndRank[] playerTop2Cards = player.top2PairCount();
            cardByCountAndRank[] dealerTop2Cards = player.top2PairCount();

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
    static GameResult isPlayerWinner(Hand player, Hand dealer)
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
    //Decided to impliment draw 5 in here rather than deck as it is exclusive to the game of POKER
    static void draw5(Hand hand, Deck deck)
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


    /*************************************************************************/
    /*                                                                        
    /* Function name:   getStringResults  
    /* Description:     Evaluates the result of a poker game in a string representation so that it can be printed
    /* Parameters:      GameResult result - The result of the poker game that we want to represent as a String
    /* Return Value:    String - The string representation of the game result (do note that enum GameResult does have a string representation through .resultName, but it is not in the desired format)
    /*
    /*************************************************************************/
    static String getStringResults(GameResult result)
    {
        switch (result)
        {
            case WIN, LOSE -> {return "You " + result.resultName + "!";}
            default -> {return result.resultName;} //case of push
        }
    }
    public static void main(String[] args) 
    {
        Scanner cin = new Scanner(System.in);
        
        System.out.print("What is your name?: ");
        System.out.println("Welcome to poker " + getName(cin) + "!");

        Hand playerHand = new Hand();
        Hand dealerHand = new Hand();
        Deck gameDeck = new Deck();
            if( args.length > 0 ) {
        CmdLineInput.parseArguments(args, playerHand, dealerHand);//STUDENT: Enter Hands here
        } else {
        //STUDENT: Deal cards normally
        
        gameDeck.shuffle(); // Should all decks be preshuffled when constructed or can I call like this?
        draw5(playerHand, gameDeck);
        draw5(dealerHand, gameDeck);
        }//end if

        System.out.println("-----------------------------\nYour results:\nHand: " + playerHand + "\nHand Rank: " + playerHand.getHandRank() + "\n-----------------------------\n");
        System.out.println("Dealer's results:\nHand: " + dealerHand + "\nHand Rank: " + dealerHand.getHandRank() + "\n-----------------------------");
        System.out.println("Result: " + getStringResults(isPlayerWinner(playerHand, dealerHand)));

  }//end main

}//end Game

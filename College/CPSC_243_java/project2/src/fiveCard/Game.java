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

import fiveCard.Hand.HandRank;
import fiveCard.Hand.cardByCountAndRank;



// error case one :  3C 7D 7S 10C QH


// ROIJREOREGJIEEOIJRGOIJA  ARE YOU OK WITH DOING Hand.HandRank or should we import import fiveCard.Hand.HandRank;
/**
 * Generate and play a hand of Poker
 */
class Game {
    enum GameResult
    {
        WIN("win"),
        LOSE("lose"),
        PUSH("push");
        final String winType;
        GameResult(String winName){ winType = winName;}
    }

   /*  static boolean isCardCountBasedHandRank(Hand.HandRank rankType) //returns true if hand rank is based off of there being pairs of cards (including 3 and 4 of the same type)
    {
        int handRankVal = rankType.ordinal();
        if(handRankVal >= Hand.HandRank.ONE_PAIR.ordinal() && handRankVal <= Hand.HandRank)
        {}

    } */

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
    //Functions in here are Poker game specific functions
    static GameResult isPlayerWinnerForTie(Hand.HandRank rankType, Hand player, Hand dealer) //has to account properly for ties. rankType is passed just to take advantage of isPlayerWinner already using getHandRank()
    { //check for tie in hand ranking portion, we NEED TO IMPLIMENT RETURNING WHAT KICKERS ARE (CARDS THAT ARE NOT PART OF THE HAND RANK (TWO_PAIR ETC...))
        int handRankVal = rankType.ordinal();

        // rank tyoe where we need to consider the top2Pair/the amount of each card rank in our hand 
        if((handRankVal >= Hand.HandRank.ONE_PAIR.ordinal() && handRankVal <= Hand.HandRank.THREE_OF_A_KIND.ordinal()) || rankType == Hand.HandRank.FULL_HOUSE || rankType == Hand.HandRank.FOUR_OF_A_KIND )
        {
            cardByCountAndRank[] playerTop2Cards = player.top2PairCount();
            cardByCountAndRank[] dealerTop2Cards = player.top2PairCount();
            sortTop2CardArrayByRank(playerTop2Cards);
            sortTop2CardArrayByRank(dealerTop2Cards);

            int playerVSDealerScoreDiff = playerTop2Cards[0].getCardRankVal() - dealerTop2Cards[0].getCardRankVal(); //DO NOTE THAT FOR WHEN WE DO THE OTHER CASES, ACE WILL BE TREATED AS LOWER 4jgoigjreoigjeieoigjaigj'soirj;oijisjijjeaiaoiregjoiare
            if(playerVSDealerScoreDiff < 0) //If player score was smaller than dealer, than this val is negative
                return GameResult.LOSE;
            else if (playerVSDealerScoreDiff > 0)
                return GameResult.WIN;
            else if(rankType == Hand.HandRank.TWO_PAIR || rankType == Hand.HandRank.FULL_HOUSE) // case where we consider the 2nd value in the case of a tie
            {

            }
            else // THis is that case for one pair, three of a kind, or four of a kind where a tie occurs, as there is only 1 candidate for ties in these
                return GameResult.PUSH; 
            
        }


        return null; //error case
    }


    static GameResult isPlayerWinner(Hand player, Hand dealer)
    {
        Hand.HandRank playerRanking = player.getHandRank();
        Hand.HandRank dealerRanking = dealer.getHandRank();
        if( playerRanking.ordinal() > dealerRanking.ordinal() )
            return GameResult.WIN;
        else if( playerRanking.ordinal() < dealerRanking.ordinal() )
            return GameResult.LOSE;
        else // case of tie (hand types are equal)
            return isPlayerWinnerForTie(playerRanking, player, dealer); //doesnt matter if first param is player or dealer ranking since they are the same by this else statement
    }
    //Decided to impliment draw 5 in here rather than deck as it is exclusive to the game of POKER
    static void draw5(Hand hand, Deck deck)
    {
        for(int i = 0; i < 5; i++)
            hand.addCard(deck.deal());
    }

    public static void main(String[] args) 
    {
        Hand playerHand = new Hand();
        Hand dealerHand = new Hand();
            if( args.length > 0 ) {
        CmdLineInput.parseArguments(args, playerHand, dealerHand);//STUDENT: Enter Hands here
        } else {
        //STUDENT: Deal cards normally
        Deck gameDeck = new Deck();
        gameDeck.shuffle(); // Should all decks be preshuffled when constructed or can I call like this?
        draw5(playerHand, gameDeck);
        draw5(dealerHand, gameDeck);
        }//end if

        // debug code (remove when done)
        //System.out.println("Player hand: " + playerHand + "\nIs ascending?: " + playerHand.isHandAscending()  + "\nDealer hand: " + dealerHand + "\nIs ascending?: " + dealerHand.isHandAscending());
        System.out.println("\nPlayer is same suit?: " + playerHand.isSameSuit()  + "\nDealer is same suit?: " + dealerHand.isSameSuit());
        System.out.println("Pair count: " + Arrays.toString(playerHand.top2PairCount())  + "\nPair count: " + Arrays.toString(dealerHand.top2PairCount()));
        System.out.println("Player hand rank: " + (playerHand.getHandRank())  + "\nDealer hand rank: " + (dealerHand.getHandRank()) + "\nPlayer hand: " + playerHand  + "\nDealer hand: " + dealerHand);

  }//end main

}//end Game

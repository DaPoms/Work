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

    static GameResult breakTie(cardByCountAndRank[] playerTop2Cards, cardByCountAndRank[] dealerTop2Cards, int handRankVal)
    {
        if(handRankVal == Hand.HandRank.TWO_PAIR.ordinal())
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

     static GameResult isPlayerWinnerForTie(Hand.HandRank rankType, Hand player, Hand dealer) //has to account properly for ties. rankType is passed just to take advantage of isPlayerWinner already using getHandRank()
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
        return breakTie(intPlayerHand, intDealerHand);

    }


    static boolean hasKickers(Hand.HandRank handRank) 
    {
        switch(handRank)
        {
            case HIGH_CARD, ONE_PAIR, TWO_PAIR, THREE_OF_A_KIND, FOUR_OF_A_KIND -> {return true;}
            default -> {return false;}
        }
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
            // anything with a GameResult of push here will need to have the non kicker's REMOVED
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

        System.out.println("\n\n\n\n");
        System.out.println("Did the player win?: " + isPlayerWinner(playerHand, dealerHand));
  }//end main

}//end Game

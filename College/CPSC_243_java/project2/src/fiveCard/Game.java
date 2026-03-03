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


// error case one :  3C 7D 7S 10C QH
/**
 * Generate and play a hand of Poker
 */
class Game {
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
        gameDeck.shuffle(); // Should all decks be preshuffled?
        draw5(playerHand, gameDeck);
        draw5(dealerHand, gameDeck);
        }//end if

        // debug code (remove when done)
        //System.out.println("Player hand: " + playerHand + "\nIs ascending?: " + playerHand.isHandAscending()  + "\nDealer hand: " + dealerHand + "\nIs ascending?: " + dealerHand.isHandAscending());
        System.out.println("\nPlayer is same suit?: " + playerHand.isSameSuit()  + "\nDealer is same suit?: " + dealerHand.isSameSuit());
        System.out.println("Pair count: " + Arrays.toString(playerHand.top2PairCount())  + "\nPair count: " + Arrays.toString(dealerHand.top2PairCount()));
        System.out.println("Player hand rank: " + (playerHand.getHandRank())  + "\nDealer hand rank: " + (dealerHand.getHandRank()) + "\nPlayer hand: " + playerHand  + "\nDealer hand: " + dealerHand);
    /*    System.out.println("Hand size of: " + myHand.getCardCount() + "\n" + myHand);
        System.out.println("I'm out of bounds!: " + myHand.getCard(5000));
        */
  }//end main

}//end Game

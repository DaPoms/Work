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
import fiveCard.Card.Suit;

/**
 * Generate and play a hand of Poker
 */
class Game {

  public static void main(String[] args) {
    Hand playerHand = new Hand();
    Hand dealerHand = new Hand();
		if( args.length > 0 ) {
      CmdLineInput.parseArguments(args, playerHand, dealerHand);//STUDENT: Enter Hands here
    } else {
      //STUDENT: Deal cards normally
    }//end if
    Card test = new Card(Rank.ACE,Suit.HEARTS);

 
    System.out.println("Player hand: " + playerHand + "\nIs ascending?: " + playerHand.isHandAscending()  + "\nDealer hand: " + dealerHand + "\nIs ascending?: " + dealerHand.isHandAscending());


 /*    System.out.println("Hand size of: " + myHand.getCardCount() + "\n" + myHand);
    System.out.println("I'm out of bounds!: " + myHand.getCard(5000));
     */
  }//end main

}//end Game

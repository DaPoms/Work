/**
 * fiveCard.Game.java
 * CPSC243 Spring 2026
 * @author Griffin Nye
 */

// cd "/c/Users/Daniel Worktop/VsProjects/Work/CPSC_243_java/project2/"


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
    System.out.println("test");
		if( args.length > 0 ) {
      //CmdLineInput.parseArguments(args, /*PLAYER HAND*/, /*DEALER HAND*/);//STUDENT: Enter Hands here
    } else {
      //STUDENT: Deal cards normally
    }//end if
    Card test = new Card(Rank.ACE,Suit.HEARTS);

    Hand myHand = new Hand();
    myHand.addCard(new Card(Rank.ACE,Suit.HEARTS));
    myHand.addCard(new Card(Rank.TWO,Suit.HEARTS));
    myHand.addCard(new Card(Rank.TEN,Suit.HEARTS));
    myHand.addCard(new Card(Rank.FOUR,Suit.HEARTS));
    myHand.sortHand();
    System.out.println("Card representation: " + test + "\nCard score: " + test.getValue());
    System.out.println("Hand size of: " + myHand.getCardCount() + "\n" + myHand);
    System.out.println("I'm out of bounds!: " + myHand.getCard(5000));
    
  }//end main

}//end Game

/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  February 26, 2026                        */
/* Due Date:       Match 13, 2026                           */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #2                                       */
/* Filename:       Card.java                                */
/* Purpose:        Impliments the card functionality used in */
/*                 poker                                    */
/*                                                          */
/*                                                          */
/************************************************************/

/** 
 * fiveCard.Card.java
 * CPSC243 Spring 2026
 * @author Griffin Nye
 */

package fiveCard; 

/**
 * This Card class represents all data and related operations for a single playing
 * card in a standard deck of playing cards.
 */


public class Card {
    enum Rank  
    { 
        TWO("2"), //0
        THREE("3"),  //1
        FOUR("4"), //2
        FIVE("5"), //3
        SIX("6"),  //4
        SEVEN("7"), //5
        EIGHT("8"), //6
        NINE("9"), //7
        TEN("10"), //8
        JACK("J"), //9
        QUEEN("Q"), //10
        KING("K"), //11
        ACE("A"); //12
        public final String stringifiedRank;
        Rank(String passedRankString)
        {
            stringifiedRank = passedRankString;
        }
    }
    enum Suit 
    { 
        CLUBS("C"), 
        DIAMONDS("D"), 
        HEARTS("H"), 
        SPADES("S");
        public final String stringifiedSuit;
        Suit(String passedSuitString)
        {
            stringifiedSuit = passedSuitString;
        }
    }
    
    private Rank rank;
    private Suit suit;
  Card(Rank passedRank, Suit passedSuit) 
  {
    rank = passedRank;
    suit = passedSuit;
  }

  Suit getSuit(){return suit;}
  int getValue() // we do not need to specify scope due to package-private being the exact scope we need
  { 
    return rank.ordinal();
  }

  public String toString()
  {
    return rank.stringifiedRank + suit.stringifiedSuit;
  }
  
  

  public static void main(String[] args) {
    Card myCard = new Card(Rank.TEN, Suit.CLUBS);

    System.out.println("Visual representation: " + myCard + "\nCard value: " + myCard.getValue());
  }

  
}//end Card

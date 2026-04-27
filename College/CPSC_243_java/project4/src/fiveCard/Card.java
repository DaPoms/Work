/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  April 21, 2026                           */
/* Due Date:       April 24, 2026                           */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #4                                       */
/* Filename:       Card.java                                */
/* Purpose:        Implements the behavior of cards in a    */
/*                 card Game                                */
/************************************************************/

package fiveCard; 

/**
 * This Card class represents all data and related operations for a single playing
 * card in a standard deck of playing cards.
 */

/**
 * Implements the behavior of cards in a card Game
 * fiveCard.Card.java
 * CPSC243 Spring 2026
 * @author Daniel Tripoli
 */
public class Card {
    /**
    * Enum that represents card rank
    */
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
        /**
         * Sets a rank to its string representation
         * @param passedRankString The string representation of the rank enum
         */
        Rank(String passedRankString)
        {
            stringifiedRank = passedRankString;
        }
    }

    /**
     * Enum that represents a card's suit
     */
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


///////////////////////////Project 4 code ///////////////////////////
  /**                                                   
  *     Constructor for the card class
  *     @param passedRank The rank that the card will be assigned to
  *     @param passedSuit The suit that the card will be assigned to
  */
  Card(Rank passedRank, Suit passedSuit) 
  {
    rank = passedRank;
    suit = passedSuit;
  }


  /**                                                   
  *     Returns the suit of the card
  *     @return The suit of the card object
  */
  Suit getSuit(){return suit;}


  /**                                                   
  *     Returns the value of the card based on the card's rank
  *     @return The score of the card
  */
  int getValue() // we do not need to specify scope due to package-private being the exact scope we need
  { 
      return rank.ordinal();
  }

  /**                                                   
  *     Constructs a string representation of the card, with the first 1-2 chars of the string being the rank, 
  *     and the last char being the rank
  *     @return The string representation of the card
  */
  public String toString()
  {
    return rank.stringifiedRank + suit.stringifiedSuit;
  }
  
}//end Card

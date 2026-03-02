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
        TWO("2"), 
        THREE("3"), 
        FOUR("4"), 
        FIVE("5"), 
        SIX("6"), 
        SEVEN("7"), 
        EIGHT("8"), 
        NINE("9"), 
        TEN("10"), 
        JACK("J"), 
        QUEEN("Q"), 
        KING("K"), 
        ACE("A");
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
  { // UHHHHHHHHHHHHHHHHHHHH IS THIS THE NORMAL INT VALUE OR JUST THE SCORE IT WOULD GIVE IN A HAND (THE CARD RANK)EGREGREGRGGGGGGGGGGGGGGGGGGGGGRGRGRGRGRGRGRGRRGRGRGRGRG
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

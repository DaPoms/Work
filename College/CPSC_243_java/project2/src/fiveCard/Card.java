/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  February 26, 2026                        */
/* Due Date:       Match 13, 2026                           */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #2                                       */
/* Filename:       Card.java                                */
/* Purpose:        Impliments the card functionality used in*/
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
    //enum that represent card rank
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
    //enum that represents a card's suit
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
   /*************************************************************************/
    /*                                                                        
    /* Function name:   Card
    /* Description:     Constructor for the card class.
    /* Parameters:      Rank passedRank - The rank that the card will be assigned to
    /*                  Suit passedSuit - The suit that the card will be assigned to
    /* Return Value:    N/A
    /*
    /*************************************************************************/
  Card(Rank passedRank, Suit passedSuit) 
  {
    rank = passedRank;
    suit = passedSuit;
  }

   /*************************************************************************/
    /*                                                                        
    /* Function name:   getSuit
    /* Description:     Returns the suit of the card (allows us to make card's data fields private)
    /* Parameters:      none
    /* Return Value:    Suit - The suit of the card 
    /*
    /*************************************************************************/
    /*************************************************************************/
    /*                                                                        
    /* Function name:   getSuit
    /* Description:     Returns the suit of the card
    /* Parameters:      none
    /* Return Value:    Suit passedSuit - The suit of the card
    /*
    /*************************************************************************/
    Suit getSuit(){return suit;}

   /*************************************************************************/
    /*                                                                        
    /* Function name:   getValue
    /* Description:     Returns the integer value of the card, using it's rank
    /* Parameters:      none
    /* Return Value:    int - The int value of the card
    /*
    /*************************************************************************/

    /*************************************************************************/
    /*                                                                        
    /* Function name:   getvalue
    /* Description:     Returns the value of the card based on the card's rank
    /* Parameters:      none
    /* Return Value:    int - score of the card
    /*
    /*************************************************************************/
    int getValue() // we do not need to specify scope due to package-private being the exact scope we need
    { 
        return rank.ordinal();
    }

   /*************************************************************************/
    /*                                                                        
    /* Function name:   toString
    /* Description:     Constructs a string representation of the card, with the first 1-2 chars of the string being the rank, and the last char being the rank
    /* Parameters:      none
    /* Return Value:    String - The string representation of the card
    /*
    /*************************************************************************/
  public String toString()
  {
    return rank.stringifiedRank + suit.stringifiedSuit;
  }
    
    /*************************************************************************/
    /*                                                                        
    /* Function name:   toString
    /* Description:     Represents the card object in a string representation and returns it. Includes the suit and rank of the card
    /* Parameters:      none
    /* Return Value:    String - The string representation of the card
    /*
    /*************************************************************************/
    public String toString()
    {
        return rank.stringifiedRank + suit.stringifiedSuit;
    }
  
}//end Card

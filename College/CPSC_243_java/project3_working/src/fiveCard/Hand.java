/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  February 26, 2026                        */
/* Due Date:       Match 13, 2026                           */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #2                                       */
/* Filename:       Hand.java                                */
/* Purpose:        Impliment the hand functionality used in */
/*                 poker                                    */
/*                                                          */
/************************************************************/

// TODO: Exceptions for getCard + addCard


/**
 * fiveCard.Hand.java
 * CPSC243 Spring 2026
 * @author Griffin Nye
 */

package fiveCard;
import java.util.ArrayList;

/// 
/**
 * This class represents all data and related operations for a hand of playing cards
 * for use in various card games. Implemented in this package for the game Poker.
*/
public class Hand {

    /**
    * Dynamic Array structure for storing Cards in the hand
    */
    protected ArrayList<Card> hand; // DOUBLE CHECK IF THIS SHOULD BE PROTECTED, AS WE HAVE A PACKAGE, BUT 


    /*************************************************************************/
    /*                                                                        
    /* Function name:   Hand 
    /* Description:     Default constructor for hand object
    /* Parameters:      none
    /* Return Value:    N/A
    /*
    /*************************************************************************/
     public Hand() { hand = new ArrayList<>(); }//end constructor 

    /*************************************************************************/
    /*                                                                        
    /* Function name:   getCard 
    /* Description:     Returns the card object at the ith index of the hand array
    /* Parameters:      int pos - the index that we want to retrieve a card at
    /* Return Value:    Card - the card we retrieved at the index pos, or null if the user enters an index that is outside of the hand array
    /*
    /*************************************************************************/
    Card getCard(int pos) throws PokerException
    {
        if(pos > hand.size() - 1 || pos < 0) 
            throw new PokerException("Hand does not contain index " + pos + ". Hand is of size " + hand.size() ) ;
        return hand.get(pos);
    }

     // TODO: Add exception handling
        /*************************************************************************/
    /*                                                                        
    /* Function name:   addCard 
    /* Description:     adds a card to the hand, inserting it with an insertion sort by card value to ensure 
    /*                  hands are sorted
    /* Parameters:      Card c - the card that is added to the hand
    /* Return Value:    void
    /*
    /*************************************************************************/
    void addCard(Card c) throws PokerException //ensures adding is done in a sorted manner (with insertion sort)
    {
        if (c == null)
            throw new PokerException("Attempted to add a NULL card"); // No reason for try catch
        hand.add(c);
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   getCardCount
    /* Description:     Returns how many cards there is in the hand object
    /* Parameters:      none
    /* Return Value:    int - the number of cards the hand object's hand array contains
    /*
    /*************************************************************************/
    int getCardCount()
    {
        return hand.size();
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   clear
    /* Description:     removes all cards from the hand array, leaving the hand empty
    /* Parameters:      none
    /* Return Value:    void
    /*
    /*************************************************************************/
    void clear() // not really used yet...
    {
        hand.clear();
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   toString
    /* Description:     Represents the hand array of the hand object in a string representation and returns it
    /* Parameters:      none
    /* Return Value:    String - The string representation of the hand array
    /*
    /*************************************************************************/
    public String toString()
    {
        String ans = "";
        for(Card cardInHand : hand)
            ans += cardInHand + " ";
        return ans;
    }
  
   

}//end Hand








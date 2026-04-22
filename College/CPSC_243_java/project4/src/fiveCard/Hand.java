/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  Match 30, 2026                           */
/* Due Date:       April 6, 2026                            */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #3                                       */
/* Filename:       Hand.java                                */
/* Purpose:        Impliment the general functionality of   */
/*                 hands in card games                      */
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
public class Hand implements Comparable<Hand>{

    /**
    * Dynamic Array structure for storing Cards in the hand
    */
    protected ArrayList<Card> hand; // With professor permission, we are allowed to make hand protected for use by pokerHand

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
            throw new PokerException("Tried to remove card at invalid index of " + pos + ". Hand is of size " + hand.size() ) ;
        return hand.get(pos);
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   addCard 
    /* Description:     adds a card to the hand, inserting it with an insertion sort by card value to ensure 
    /*                  hands are sorted
    /* Parameters:      Card c - the card that is added to the hand
    /* Return Value:    void
    /*
    /*************************************************************************/
    // Is it normal to throw our custom poker exceptions with our generalized hand class?? Shouldn't this be a pokerHand exclusive (or just throw a general out of bounds exception? (But your instructions specify this as a requirement)
    void addCard(Card c) throws PokerException//ensures adding is done in a sorted manner (with insertion sort)
    {
        if (c == null)
            throw new PokerException("Attempted to add a NULL card");
        int i = 0;
        for(Card cardInHand : hand)
            if(c.getValue() > cardInHand.getValue())
                i++;
        hand.add(i, c);
    }


    /*************************************************************************/
    /*                                                                        
    /* Function name:   removeCard
    /* Description:     Removes a card from the hand, accounting that the requested index is within bounds
    /* Parameters:      int i - Index in hand of the card that is removedd
    /* Return Value:    void
    /*
    /*************************************************************************/
    void removeCard(int i) throws PokerException
    {
        if(i > hand.size() - 1 || i < 0) 
            throw new PokerException("Tried to remove card at invalid index of " + i + ". Hand is of size " + hand.size() ) ;
        hand.remove(i); 
    }// Deletes the i-th element from the hand
    

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
  
   
   
    public int compareTo(Hand otherHand) // I added this to allow .compareTo in bettor with better syntax 
    {
        if (otherHand.hand.size() != hand.size()) 
            return -2; //error case

        int handSum = 0;
        int otherSum = 0;
        for(int i = 0; i < hand.size(); i++)
        {
            handSum += hand.get(i).getValue();
            otherSum += otherHand.hand.get(i).getValue();
        }

        if (handSum > otherSum)
            return 1;
        if (handSum < otherSum)
            return -1;
        return 0;
    }


}//end Hand








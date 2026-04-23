/**
 * Implements the behavior of card hands in a card Game
 * fiveCard.Hand.java
 * CPSC243 Spring 2026
 * @author Daniel Tripoli
 */

/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  April 21, 2026                           */
/* Due Date:       April 24, 2026                           */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #4                                       */
/* Filename:       Hand.java                                */
/* Purpose:        Implements the behavior of card hands in */
/*                 a card Game                              */
/************************************************************/

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


    /**                                                   
    *      Default constructor for hand class
    */
     public Hand() { hand = new ArrayList<>(); }//end constructor 

    /**                                                   
    *     Returns the card at a given position
    *     @param pos The index of the card in hand that it returned
    *     @return The card retrieved at the passed index
    *     @throws PokerException If trying to retrieve a card out of bounds
    */
    Card getCard(int pos) throws PokerException
    {
        if(pos > hand.size() - 1 || pos < 0) 
            throw new PokerException("Tried to remove card at invalid index of " + pos + ". Hand is of size " + hand.size() ) ;
        return hand.get(pos);
    }

    /**                                                   
    *      adds a card to the hand, inserting it with an insertion sort by card value to ensure hands are sorted
    *      @param c The card that is added to the hand
    *      @throws PokerException If adding a null card
    */
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

    /**                                                   
    *      Removes a card from the hand, accounting that the requested index is within bounds
    *      @param i Index in hand of the card that is removedd
    *      @throws PokerException If removing out of bounds
    */
    void removeCard(int i) throws PokerException
    {
        if(i > hand.size() - 1 || i < 0) 
            throw new PokerException("Tried to remove card at invalid index of " + i + ". Hand is of size " + hand.size() ) ;
        hand.remove(i); 
    }// Deletes the i-th element from the hand
    

    /**                                                   
    *      Returns how many cards there is in the hand object
    *      @return The amount of cards in the hand
    */
    int getCardCount()
    {
        return hand.size();
    }

    
    /**                                                   
    *      Removes all cards from the hand array, leaving the hand empty
    */
    void clear()
    {
        hand.clear();
    }

    /**                                                   
    *      Represents the hand array of the hand object in a string representation and returns it
    *      @return String representation of hand
    */
    public String toString()
    {
        String ans = "";
        for(Card cardInHand : hand)
            ans += cardInHand + " ";
        return ans;
    }
  
   
   
    /**                                                   
    *      A generalized comparison between hands based on the total value of the cards in a hand
    *      @return The result of the comparison: -1 = Less than, 0 = equal to, 1 = greater than the otherHand
    */
   @Override
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








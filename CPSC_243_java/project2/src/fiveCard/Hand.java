/**
 * fiveCard.Hand.java
 * CPSC243 Spring 2026
 * @author Griffin Nye
 */

package fiveCard;

import java.util.ArrayList;
import java.util.Comparator;


/// 
/**
 * This class represents all data and related operations for a hand of playing cards
 * for use in various card games. Implemented in this package for the game Poker.
*/
public class Hand {

  /**
   * Dynamic Array structure for storing Cards in the hand
   */
    private ArrayList<Card> hand;

    public Hand() {
        hand = new ArrayList<>();
    }//end constructor

    Card getCard(int pos)
    {
        if(pos > hand.size() - 1) return null;
        return hand.get(pos);
    }

    private enum HandRank 
    {
        HIGH_CARD, //0 (this is the assigned .ordinal() value of the enum)
        ONE_PAIR, //1
        TWO_PAIR, //2
        THREE_OF_A_KIND, //3
        STRAIGHT, //4
        FLUSH, //5
        FULL_HOUSE, //6
        FOUR_OF_A_KIND, //7
        STRAIGHT_FLUSH, //8
        ROYAL_FLUSH //9
    }

    int getCardCount()
    {
        return hand.size();
    }

    private void sortHand()
    {
        hand.sort(Comparator.comparing(Card::getValue));
    }


    private int containsCardRank(Rank targetRank)
    {
        //if(hand.get(hand.size() - 1).getValue() == Rank.ACE.ordinal())

        for(int i = 0; i < hand.size(); i++)
        {
            if(hand.get(i).getValue() == targetRank.ordinal())
                return i;
        }
        return -1;
    }

    
// DOES HAND CLASS NEED TO BE DYNAMIC OR BUILT FOR 5 CARD HANDS?
// "BASED ON 5 CARD RULES"
    public boolean isHandAscending() //determines if hand is ascending based off of 
    {
        int hasAce = containsCardRank(Rank.ACE); // -1 = no ace, otherwise, gives index of location
        int endI = hand.size();
        sortHand();

        if(hasAce != -1 && containsCardRank(Rank.TWO) != -1) // I use containsCardRank() intead of hand.get(0).getValue() == Rank.Two.ordinal() for the sole reason of better error handling and modularity (WE can't assume that the hand has any cards in it)
            --endI; // endI effectively states that when we have A 2 3 4 5, we only need to check for 2 3 4 5 to be ascending (as ACE in this version is treated as highest value, so we need to explicitly support lowest value)

        for(int i = 0; i < endI - 1; i++) // we have to do - 1 as we are doing forward comparisons (always checking one forward)
            if(hand.get(i).getValue() + 1 != hand.get(i+1).getValue()) 
                return false;
        return true;
    }
    
    
/*     
    HandRank getHandRank()
    {

    }
 */
    void addCard(Card c)
    {
        hand.add(c);
    }

    void clear()
    {
        hand.clear();
    }

    public String toString()
    {
        String ans = "";
        for(Card cardInHand : hand)
            ans += cardInHand + " ";
        return ans;
    }
  
}//end Hand

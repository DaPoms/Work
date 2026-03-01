/**
 * fiveCard.Hand.java
 * CPSC243 Spring 2026
 * @author Griffin Nye
 */

package fiveCard;

import java.util.ArrayList;
import java.util.Comparator;

// IS THIS ILLEGAL EIWJGOIERIJOJJOIEGJEEJGEJOGIERJGOERJGEOIRJGOERIJGEORGJEORIGJEORIJEORJEROIREJGOERIJOERGJOIREJ I added an import
import fiveCard.Card.Rank;
import fiveCard.Card.Suit;
////////////////////////////
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

    void sortHand()
    {
        hand.sort(Comparator.comparing(Card::getValue));
    }


 /*    int containsCardRank(Rank targetRank)
    {
        for(Card cardInHand : hand)
        {
            if(cardInHand. == target)
        }
    }
 */

/* 
    public boolean isHandAscending() //determines if hand is ascending based off of 
    {
        if(rankOccurences[0] != 0 && rankOccurences[1] == 0) //if an ace exists but it isnt ascending in terms of ace being the minimum, we treat ace as a maximum value instead
        {
            for(int i = rankOccurences.length - 4; i < rankOccurences.length; i++) // if ace is the max, then ascending is only considered when the cards are 10 J Q K A. This checks for 10 J Q K
                if(rankOccurences[i] == 0) 
                    return false;
        }
        else
        {
        int i = 0;
        while(rankOccurences[i] == 0) i++; //sets up to the first card we have from our hand 
        int endpoint = i + 5; // endpoint is 4 spaces from where the lowest rank card is
        if(endpoint > rankOccurences.length) return false; //edge case where if the 1st card in ascending order is a 10, then it cannot be strictly ascending order
        for(; i < endpoint ; i++)
            if(rankOccurences[i] == 0) 
                return false;
        }
    return true;
    }
     */
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

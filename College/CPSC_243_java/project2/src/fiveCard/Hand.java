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
    void addCard(Card c) //ensures adding is done in a sorted manner (with insertion sort)
    {
        int i = 0;
        for(Card cardInHand : hand)
        {
            if(c.getValue() > cardInHand.getValue())
                i++;
        }
        hand.add(i, c);
    }

    enum HandRank 
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

    int[] getRankArray()
    {
        int[] arr = new int[hand.size()];
        for(int i = 0; i < hand.size(); i++)
            arr[i] = hand.get(i).getValue();
        return arr;
    }
    int getCardCount()
    {
        return hand.size();
    }

  /*   private void sortHand()
    {
        hand.sort(Comparator.comparing(Card::getValue));
    } */





    public boolean isSameSuit() // I'm trying to build my functions as modular so that they could technically be used in other Poker-like games (so not assuming 5 card hands)
    {
        Card.Suit currSuit = null;
        if(hand.size() != 0) // just for error handling (of empty hand)
            currSuit = hand.get(0).getSuit();

        for(int i = 1; i < hand.size() ; i++)
            if(hand.get(i).getSuit() != currSuit) return false;
        return true;       
    }
    private int containsCardRank(Card.Rank targetRank)
    {
        //if(hand.get(hand.size() - 1).getValue() == Rank.ACE.ordinal())

        for(int i = 0; i < hand.size(); i++)
        {
            if(hand.get(i).getValue() == targetRank.ordinal())
                return i;
        }
        return -1;
    }

    private boolean isHandAscending() //determines if hand is ascending based off of 
    {
        int hasAce = containsCardRank(Card.Rank.ACE); // -1 = no ace, otherwise, gives index of location
        int endI = hand.size();
        //sortHand();

        if(hasAce != -1 && containsCardRank(Card.Rank.TWO) != -1) // I use containsCardRank() intead of hand.get(0).getValue() == Rank.Two.ordinal() for the sole reason of better error handling and modularity (WE can't assume that the hand has any cards in it)
            --endI; // endI effectively states that when we have A 2 3 4 5, we only need to check for 2 3 4 5 to be ascending (as ACE in this version is treated as highest value, so we need to explicitly support lowest value)

        for(int i = 0; i < endI - 1; i++) // we have to do - 1 as we are doing forward comparisons (always checking one forward)
            if(hand.get(i).getValue() + 1 != hand.get(i+1).getValue()) 
                return false;
        return true;
    }


    class cardByCountAndRank 
    {
        private int cardRankVal;
        private int cardCount;
        cardByCountAndRank()
        {
            cardRankVal = 0;
            cardCount = 0;
        }

        public int getCardRankVal(){return cardRankVal;}
        public int getCardCount(){return cardCount;}
        public String toString()
        {
            return "{" + cardRankVal + ", " + cardCount + "}";
        }
        
    }

    cardByCountAndRank[] top2PairCount() //assumes that hand is of size 5 
    {
        ArrayList<Integer> handRanks = new ArrayList<>();
        ArrayList<Integer> rankCount = new ArrayList<>(); // too lazy to do map, so this is a parallel array with handRanks
        for(Card c : hand) //gets count of all cards in hand
        {
            int cardVal = c.getValue();
            int i = handRanks.indexOf(cardVal);
            if(i == -1) // case of card not being found in hand yet
            {
                handRanks.add(cardVal);
                rankCount.add(1);
            }
            else
                rankCount.set(i, rankCount.get(i) + 1);
        }

        
        cardByCountAndRank[] top2byCount = {new cardByCountAndRank(), new cardByCountAndRank()};
        
        for(int i = 0; i < rankCount.size(); i++)
        {
            int currCount = rankCount.get(i);
            if(currCount > top2byCount[0].cardCount && top2byCount[1].cardCount != 0) 
            {
                top2byCount[0].cardRankVal = handRanks.get(i);
                top2byCount[0].cardCount = rankCount.get(i); 
            }
            else if(currCount > top2byCount[1].cardCount) 
            {
                top2byCount[1].cardRankVal = handRanks.get(i);
                top2byCount[1].cardCount = rankCount.get(i);
            }
        }

        //just a measure to ensure left most term is the higher count item
        cardByCountAndRank placeholder;
        if(top2byCount[1].cardCount > top2byCount[0].cardCount)
        {
           placeholder = top2byCount[1];
           top2byCount[1] = top2byCount[0];
           top2byCount[0] = placeholder;
        }
        
        return top2byCount;
    }
    
    HandRank getHandRank()
    {
        //Aquires all the elements required to determine ranking
        boolean isAscending = isHandAscending();
        boolean isSameSuit = isSameSuit();
        cardByCountAndRank[] top2CardCounts = top2PairCount();
        
        if(isAscending) // this block counts for straight flush and royal flush ()
        { 
            if(isSameSuit) 
            {
                if(containsCardRank(Card.Rank.TEN) != -1 && containsCardRank(Card.Rank.ACE) != -1) 
                    return HandRank.ROYAL_FLUSH;
                return HandRank.STRAIGHT_FLUSH;
            }
        }

        if(top2CardCounts[0].cardCount == 4) // 4 of a kind case
            return HandRank.FOUR_OF_A_KIND;

        if(top2CardCounts[0].cardCount == 3 && top2CardCounts[1].cardCount == 2)//Full house case
            return HandRank.FULL_HOUSE;

        if(isSameSuit) //Flush case
            return HandRank.FLUSH; 

        if(isAscending) //Straight case
            return HandRank.STRAIGHT;

        if(top2CardCounts[0].cardCount >= 2) //for 3 of a kind, two pair, and one pair all together
        {
            if(top2CardCounts[0].cardCount == 3) // case for three of a kind
                return HandRank.THREE_OF_A_KIND;
            if(top2CardCounts[1].cardCount == 2) //case for two pair
                return HandRank.TWO_PAIR;
            return HandRank.ONE_PAIR; // implicit case for one pair (if there exists a >=2 grouping that <3 and does not have an additional 2 grouping, then its a one pair)
        }

    return HandRank.HIGH_CARD;
    
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

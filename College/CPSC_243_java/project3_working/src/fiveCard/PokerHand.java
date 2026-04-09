/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  Match 30, 2026                           */
/* Due Date:       April 6, 2026                            */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #3                                       */
/* Filename:       PokerHand.java                           */
/* Purpose:        Impliments the card functionality used in*/
/*                 poker                                    */
/*                                                          */
/*                                                          */
/************************************************************/


package fiveCard;

import java.util.ArrayList; // TEST IF WE REALLY NEED THIS OR NOT

class PokerHand extends Hand // Can only be package private within the SAME FILE
{

   /*  private ArrayList<Card> hand; // UHHHH THIS OR CAN I USE PROTECTED? */
    
   /*  public PokerHand() {hand = new ArrayList<Card>();}//end constructor  */
     //enum for the rank of the hand
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

    /*************************************************************************/
    /*                                                                        
    /* Function name:   getRankArray 
    /* Description:     Returns an int representation of the hand object, done by each card's value (rank value in particular)
    /* Parameters:      none
    /* Return Value:    int[] - the int representation of the hand object, following the same order as the original hand array
    /*
    /*************************************************************************/
    int[] getRankArray()
    {
        int[] arr = new int[hand.size()];
        for(int i = 0; i < hand.size(); i++)
            arr[i] = hand.get(i).getValue();
        return arr;
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   getHandRank
    /* Description:     Determines and returns the rank of the hand based on 5 card poker rankings
    /* Parameters:      none
    /* Return Value:    HandRank - An enum that represents the determined hand rank
    /*
    /*************************************************************************/
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

    /*************************************************************************/
    /*                                                                        
    /* Function name:   isSameSuit 
    /* Description:     Returns true if the hand object's hand array has all of its cards in the same suit, false otherwise
    /* Parameters:      none
    /* Return Value:    boolean - true if all cards in hand array are of the same suit, false otherwise
    /*
    /*************************************************************************/
    //made private but I'll make this (and the 2 below functions) package-private if needed for future projects
    private boolean isSameSuit() // I'm trying to build my functions as modular so that they could technically be used in other Poker-like games (so not assuming 5 card hands)
    {
        Card.Suit currSuit = null;
        if(hand.size() != 0) // just for error handling (of empty hand)
            currSuit = hand.get(0).getSuit();

        for(int i = 1; i < hand.size() ; i++)
            if(hand.get(i).getSuit() != currSuit) return false;
        return true;       
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   containsCardRank 
    /* Description:     Returns true if the hand array of the hand object contains the card rank, and returns the index of it's location in the hand.
    /* Parameters:      Card.Rank - the rank of the card that is searched for
    /* Return Value:    int - The index of the first card that is of the target rank
    /*
    /*************************************************************************/
    private int containsCardRank(Card.Rank targetRank)
    {
        for(int i = 0; i < hand.size(); i++)
        {
            if(hand.get(i).getValue() == targetRank.ordinal())
                return i; // I decided to return the index for sole future use, my current use for this function does not really use the index
        }
        return -1;
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   isHandAscending 
    /* Description:     Returns whether or not the hand array of the hand object is ascending in terms of card rank
    /* Parameters:      none
    /* Return Value:    boolean - True if the hand is ascending, false otherwise
    /*
    /*************************************************************************/
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


    class cardByCountAndRank  // class for destructuring a card by its count and rank. Card itself doesn't use this class so I decided not to impliment it there
    {
        private int cardRankVal;
        private int cardCount;
        cardByCountAndRank()
        {
            cardRankVal = 0;
            cardCount = 0;
        }

        int getCardRankVal(){return cardRankVal;}
        int getCardCount(){return cardCount;}
        public String toString()
        {
            return "{" + cardRankVal + ", " + cardCount + "}";
        }
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   top2PairCount 
    /* Description:     Returns an array of the 2 cards in the hand array that in terms of rank have the highest frequency. Sorted with the 1st term being the one of highest frequency
    /* Parameters:      none
    /* Return Value:    cardByCountAndRank[] - An array of the top 2 cards in terms of frequency, sorted from highest to lowest card count
    /*                  (but theres only 2 cards in this array, so essentially left item is highest count, right item is 2nd highest count)
    /*************************************************************************/
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



}


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

import fiveCard.Card.Rank;

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

    public enum HandResult 
     {
        WIN(1),
        LOSE(-1),
        PUSH(0);
        final int comparatorVal;
        HandResult(int comparatorVal){ this.comparatorVal = comparatorVal;}

    /*************************************************************************/
    /*                                                                        
    /* Function name:   getStringResults  
    /* Description:     Evaluates the result of a poker game in a string representation so that it can be printed
    /* Parameters:      none
    /* Return Value:    String - The string representation of the game result (do note that enum GameResult does have a string representation through .resultName, but it is not in the desired format)
    /*
    /*************************************************************************/
        String getStringResults()
        {
            switch (this)
            {
                case WIN ->  {return "won";}
                case LOSE -> {return "lost";}
                default -> {return "pushed";} //case of push
            }
        }
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

     /*************************************************************************/
    /*                                                                        
    /* Function name:   getKickerArr
    /* Description:     This function is solely for when the hand type is one that has nonkicker cards. It creates an array that is of only the kicker cards.
    /* Parameters:      Hand hand - The hand containing all of the cards
    /*                  cardByCountAndRank[] top2Cards - Contains that cards that are considered non kicker cards (the ones avoid in the array that's returned)
    /*                  int nonKickerCardCount - Used to declare the size of the array, the amount of nonkicker cards the hand has. (alternative would've been to use an arraylist) 
    /* Return Value:    int[] - The int representation of the passed hand, with the non kicker cards not included.
    /*
    /*************************************************************************/
    static int[] getKickerArr(Hand hand, cardByCountAndRank[] top2Cards, int nonKickerCardCount) throws PokerException
    {
        int[] kickerArr = new int[hand.getCardCount() - nonKickerCardCount];
        int addI = 0;
        for(int i = 0; i < hand.getCardCount(); i++) // this initializes the kicker array, it effectively just removed cards that contributed to the hand ranking from the 
        {
            int cardVal = hand.getCard(i).getValue();
             if(cardVal != top2Cards[0].getCardRankVal() && (top2Cards[1].getCardCount() == 1 || cardVal != top2Cards[1].getCardRankVal() ) )
                kickerArr[addI++] = cardVal;
        }
        return kickerArr;
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   sortTop2CardArrayByRank
    /* Description:     Makes the passed array's first to elements sorted from greatest to least by card rank
    /* Parameters:      cardByCountAndRank[] arr - The array of 2 elements that we want to sort
    /* Return Value:    void
    /*
    /*************************************************************************/
    static void sortTop2CardArrayByRank(cardByCountAndRank[] arr)
    {
        cardByCountAndRank placeholder;
        if(arr[0].getCardRankVal() < arr[1].getCardRankVal()) //resorts the array by card rank rather than count (its sorted by count by default, but for ties, we only care about rank)
        {
            placeholder = arr[0];
            arr[0] = arr[1];
            arr[1] = placeholder;
        }

    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   kickerBreakTie
    /* Description:     Determines the kickers of both hands and breaks the tie on the kicker cards, returning the game result.
    /* Parameters:      Hand caller - The poker hand of the caller
                        Hand dealer - The poker hand of the dealer
    /*                  cardByCountAndRank[] callerTop2Cards - The caller's array of their top 2 cards by card rank count (like pairs, three of a kind, etc..). Used to isolate nonkicker cards
                        cardByCountAndRank[] dealerTop2Cards - The dealer's array of their top 2 cards by card rank count (like pairs, three of a kind, etc..). Used to isolate nonkicker cards    
    /* Return Value:    HandResult - The result of the tie break. Win and lose entail the entire hand was won or lost, push guarantees that a complete tie occured
    /*
    /*************************************************************************/
    static HandResult kickerBreakTie(Hand caller, Hand dealer, cardByCountAndRank[] callerTop2Cards, cardByCountAndRank[] dealerTop2Cards) throws PokerException
    {
        int mainHandCardCount = 0;
        for(cardByCountAndRank card : callerTop2Cards)
            if(card.getCardCount() > 1)
                mainHandCardCount += card.getCardCount();

        int[] callerKickers = getKickerArr(caller, callerTop2Cards, mainHandCardCount); // I could've done a plethora of things for this, but found this to be the simplest way to exclude the cards already compared that contributed to the hand rank 
        int[] dealerKickers =  getKickerArr(dealer, dealerTop2Cards, mainHandCardCount); // we need to subtract by the count of each main card Count
    
        return breakTie(callerKickers, dealerKickers);
    }    

    /*************************************************************************/
    static HandResult breakTie(cardByCountAndRank[] callerTop2Cards, cardByCountAndRank[] dealerTop2Cards, int handRankVal)
    {
        if(handRankVal == HandRank.TWO_PAIR.ordinal())
        {
            sortTop2CardArrayByRank(callerTop2Cards); // we do this to re-sort the hand by rank, as top2PairCount originally sorts by COUNT. This is really ony luseful for two pair
            sortTop2CardArrayByRank(dealerTop2Cards);
        }

        for(int i = 0; i < callerTop2Cards.length; i++) // Actually checking the kickers to break up the tie
        {
            int callerVSDealerScoreDiff = callerTop2Cards[i].getCardRankVal() - dealerTop2Cards[i].getCardRankVal();
            if(callerVSDealerScoreDiff < 0) //If caller score was smaller than dealer, than this val is negative
                return HandResult.LOSE;
            else if (callerVSDealerScoreDiff > 0)
                return HandResult.WIN;
        }
        return HandResult.PUSH; // if after all of these checks, all cards are seen as identical in rank, then a push has resulted
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   breakTie
    /* Description:     Breaks a tie by comparing the entirety of the hands passed through by card ranks 
    /* Parameters:      int[] intCallerHand - The caller's int representation of their hand, with the ints attributed to rank value
    /*                  int[] intDealerHand - The dealer's int representation of their hand, with the ints attributed to rank value
    /* Return Value:    HandResult - The result of the tie break. Win and lose entail the entire hand was won or lost, push guarantees that a complete tie occured
    /*
    /*************************************************************************/
    static HandResult breakTie(int[] intCallerHand, int[] intDealerHand) 
    {  
        for(int i = intCallerHand.length - 1; i >= 0; i--) // Actually checking the kickers to break up the tie
        {
            int callerVSDealerScoreDiff = intCallerHand[i] - intDealerHand[i];
            if(callerVSDealerScoreDiff < 0) //If caller score was smaller than dealer, than this val is negative
                return HandResult.LOSE;
            else if (callerVSDealerScoreDiff > 0)
                return HandResult.WIN; 
        }
        return HandResult.PUSH; // if after all of these checks, all cards are seen as identical in rank, then a push has resulted
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   hasKickers 
    /* Description:     Determines if the handRank has kickers or not, based on poker definitions for hand ranks.
    /* Parameters:      HandRank handRank - The rank we check for kickers
    /* Return Value:    boolean - true if it does have kickers, false otherwise
    /*
    /*************************************************************************/
    static boolean hasKickers(HandRank handRank) 
    {
        switch(handRank)
        {
            case HIGH_CARD, ONE_PAIR, TWO_PAIR, THREE_OF_A_KIND, FOUR_OF_A_KIND -> {return true;}
            default -> {return false;}
        }
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   isCallerWinner 
    /* Description:     Contains all the functionality for determining the winner of a single poker game
    /* Parameters:      Hand caller - The caller's hand, represented by the Hand object
    /*                  Hand dealer - The dealer's hand, represented by the Hand object
    /* Return Value:    HandResult - Returns WIN if the caller wins, LOSE if they lose, and PUSH if theres a complete tie
    /*
    /*************************************************************************/
    static HandResult isCallerWinner(PokerHand caller, PokerHand dealer) throws PokerException
    {
        
        HandRank callerRanking = caller.getHandRank();
        HandRank dealerRanking = dealer.getHandRank();
        if( callerRanking.ordinal() > dealerRanking.ordinal() )
            return HandResult.WIN;
        else if( callerRanking.ordinal() < dealerRanking.ordinal() )
            return HandResult.LOSE;
        else // case of tie (hand types are equal)
            return isCallerWinnerForTie(callerRanking, caller, dealer); //doesnt matter if first param is caller or dealer ranking since they are the same by this else statement
            // anything with a HandResult of push here will need to have the non kicker's REMOVED
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   hasAceAsLowest
    /* Description:     Evaluates if hand has an ace and if the ace is treated as lowest card in the hand or not
    /* Parameters:      int[] hand - the hand we insert the ace into
    /*                  HandRank rankType - The hand rank of the hand we pass through
    /* Return Value:    boolean - Returns true if ace is treated as the lowest card for the given hand, false otherwise
    /*
    /*************************************************************************/
    static boolean hasAceAsLowest(int[] hand, HandRank rankType)
    {
        if(rankType == HandRank.STRAIGHT || rankType == HandRank.STRAIGHT_FLUSH) // these are the cases where we have to check is Ace exists, and then if ace should be treated as low or high value  
        {
            if(hand[0] < Rank.TEN.ordinal() && hand[hand.length - 1] == Rank.ACE.ordinal()) // since we know straight / straight flush is in ascending order,  if you have an ace and the lowest valued card at < 10, then it must be A 2 3 4 5 in order for it to be ascending
                return true;
        }
        return false;
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   insertAceToFront
    /* Description:     Inserts an ace to the front of the hand at the lowest possible card value in place (as in doesn't return a separate array).
    /* Parameters:      int[] hand - the hand we insert the ace into
    /* Return Value:    void
    /*
    /*************************************************************************/
    static void insertAceToFront(int[] hand)
    {
         for(int i = hand.length - 1; i > 0; i--)
            hand[i] = hand[i - 1];
        hand[0] = -1; // a low value ace is represented by a value of -1 instead of 12
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   adjustAceValueIfNeeded
    /* Description:     When hand contains an ace, checks if hand uses ace as lowest value and sets it to be the lowest value if so.
    /* Parameters:      int[] hand - the hand we search
    /*                  HandRank rankType - The hand rank of the hand we pass through
    /* Return Value:    void
    /*
    /*************************************************************************/
    static void adjustAceValueIfNeeded(int[] hand, HandRank rankType)
    {
            if(hasAceAsLowest(hand, rankType)) //since we   
                insertAceToFront(hand);
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   isCallerWinnerForTie
    /* Description:     Contains all the functionality for determining the winner of a tie.
    /* Parameters:      HandRank rankType - The hand rank of the hand we pass through
    /*                  Hand caller - An object that is the caller's poker hand
    /*                  Hand dealer - An object that is the dealer's poker hand
    /* Return Value:    HandResult - Returns WIN if the caller wins, LOSE if they lose, and PUSH if theres a complete tie
    /*
    /*************************************************************************/
     static HandResult isCallerWinnerForTie(HandRank rankType, PokerHand caller, PokerHand dealer) throws PokerException //has to account properly for ties. rankType is passed just to take advantage of isCallerWinner already using getHandRank()
    {
        int handRankVal = rankType.ordinal();

        // rank types where the full hand is not included in the hand ranking
        if(hasKickers(rankType) && rankType != HandRank.HIGH_CARD)
        { // we are guaranteed to do one pair check for anything that enters here
            cardByCountAndRank[] callerTop2Cards = caller.top2PairCount();
            cardByCountAndRank[] dealerTop2Cards = dealer.top2PairCount();

            HandResult nonKickerResult = breakTie(callerTop2Cards, dealerTop2Cards, handRankVal); 
            if (nonKickerResult != HandResult.PUSH)
                return nonKickerResult; //if we break the tie without using kickers, then we've determined the game result
            else //if a push occurs for the non kicker cards, then we must explore the kicker cards to break the tie (or determine if it's truly a push)
                return kickerBreakTie(caller, dealer, callerTop2Cards, dealerTop2Cards);            
        }
        //case of every other poker hand (you just search from highest to lowest ranking)

        int[] intCallerHand = caller.getRankArray();
        int[] intDealerHand = dealer.getRankArray();
        adjustAceValueIfNeeded(intCallerHand, rankType); // checks for case where ace can be treated as a value lower than 2 and assigns it with a lower value than 2 if it means the lower value ace condition
        adjustAceValueIfNeeded(intDealerHand, rankType);
        
        return breakTie(intCallerHand, intDealerHand);
    }


    @Override
    public int compareTo(Hand otherHand)  // Needed to use Hand input due to implementing compareTo in the Hand class too for a cleaner Bettor's getWinnings method
    {
        PokerHand otherPokerHand = null;
        if(otherHand instanceof PokerHand)
            otherPokerHand = (PokerHand) otherHand;
        else
        {
            System.out.println("Tried to compare a PokerHand to a non-PokerHand object.");
            System.exit(1);
        }
        HandResult callerResult = null;
        try{callerResult = isCallerWinner(this, otherPokerHand);}
        catch (PokerException e) {throw new RuntimeException("Get card error occured when trying to detmine hand winner in compareTo.", e);}  // I had to make this due to the override not allowing us to change the signature
        switch(callerResult)
        {
            case HandResult.WIN  -> {return 1;}
            case HandResult.LOSE -> {return -1;}
            default -> {return 0;}  // push case
        }
    }


    public static HandResult comparatorIntToHandResult(int n)
    {
        switch(n)
        {
            case 1  -> {return HandResult.WIN;}
            case 0  -> {return HandResult.PUSH;}
            case -1 -> {return HandResult.LOSE;}
        }
        return null;
    }


}


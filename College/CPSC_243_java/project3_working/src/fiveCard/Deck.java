/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  February 26, 2026                        */
/* Due Date:       Match 13, 2026                           */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #2                                       */
/* Filename:       Deck.java                                */
/* Purpose:        Impliments the deck functionality used in */
/*                 poker                                    */
/*                                                          */
/*                                                          */
/************************************************************/

/**
 * fiveCard.Deck.java
 * CPSC243 Spring 2026
 * @author Griffin Nye
 */

    package fiveCard;

/**
     * This class represents all data and operations for a deck 
     * of standard playing cards used in various casino 
     * games. Implemented in this package for the game fiveCardPoker.
     */
public class Deck 
{

    private Card[] deck; // Cards in the Deck
    private int top;     // Pointer/Index of top card in Shoe (next card to deal)
    private int reshuffleCount; // Reshufflecount specifies the ith card to stop at. so 43 means the card at i = 43

    /** 
     * Constructor
     */
    /*************************************************************************/
    /*                                                                        
    /* Function name:   Deck
    /* Description:     Constructor for a deck, Fills deck with 1 of each card type, based on the suit and rank enums.
    /*                  For poker, this will be 52 cards. Do note the hand is constructed in an ordered pattern, unshuffled
    /* Parameters:      none
    /* Return Value:    N/A (constructor)
    /*
    /*************************************************************************/
    public Deck(int reshuffleCount) throws PokerException
    {
        top = 0;
        // I liked the idea of an adaptive deck size (as in it changes size based on the user's card combos) for more code reusability (like to use for other card games)
        Card.Suit[] suits = Card.Suit.values();
        Card.Rank[] ranks = Card.Rank.values();
        int size = suits.length * ranks.length;
        deck = new Card[size]; //for poker, this is 52
        int i = 0;
        for(Card.Rank rank : Card.Rank.values())
        {   //it would be more efficient to create card here and then use a setter for the suit, but that would make us have to create a setter for suit, and I don't want that to be possible (no reason to change a card, should be immutable)
            for(Card.Suit suit : suits)
            {
                Card cardToBeAdded = new Card(rank, suit); 
                deck[i] = cardToBeAdded;
                ++i;
            }
        }
 // My reroll is 11-44 inclusive as the top references the top card that hasnt been dealt yet, and therefore there are only 8 numbers between 44-51 *inclusive* (44 45 46 47 48 49 50 51), 
 // which means you can't do all the discards if i >= 44
        this.reshuffleCount = reshuffleCount;
        if(this.reshuffleCount > 44)
            throw new PokerException("Deck has a reshuffle count that is higher than the allowed reshuffle count. Deck has a max shuffle count index of 44 when the passed reshuffle count was " + this.reshuffleCount);
		
    }//end constructor
  
    /*************************************************************************/
    /*                                                                        
    /* Function name:   cardsLeft
    /* Description:     Returns the amount of cards left in the deck that haven't been drawn already
    /* Parameters:      none
    /* Return Value:    int - The amount of cards left
    /*
    /*************************************************************************/
    int cardsLeft()
    {
        return deck.length - top; //note that if top = 52, it means deck is empty
    }

    /*************************************************************************/
    /*                                                                        
    /* Function name:   deal
    /* Description:     Retrieves that card at the top of the draw pile
    /* Parameters:      none
    /* Return Value:    Card - The card that is retrieved from the top of the deck pile
    /*
    /*************************************************************************/
    Card deal() throws PokerException// what is to be returned or to actually return?
    { // do we need error handling for when dealing a hand that is empty???
        if(top >= reshuffleCount) // This is why I made reshuffleCount's max val 44, as INDEX 44 would only allow 8 discards: 44 45 46 47 48 49 50 51
            throw new PokerException("Tried to withdraw card past the allowed reshuffle count, at index " + top + ". Index must be less than " + reshuffleCount);
        return deck[top++];
    }


    // 1, 3  max - min = 2


   /** (not adding my own comment block as this was made by professor)
   * Return all cards to the deck and shuffle
   * using the Fisher-Yates shuffling algorithm.
   */
    public void shuffle(int reshuffleCount) {
        top = 0;
        for(int i = deck.length - 1; i > top; i--) 
        {
            int rnd = (int) (Math.random() * (i + 1) );
            Card temp = deck[rnd];
            deck[rnd] = deck[i];
            deck[i] = temp;
        }//end for
    this.reshuffleCount = reshuffleCount;
    }//end shuffle
  
}//end Shoe

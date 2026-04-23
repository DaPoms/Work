/**
 * Implements the behavior of a card game deck
 * fiveCard.Deck.java
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
/* Filename:       Deck.java                                */
/* Purpose:        Implements the behavior of a card game   */
/*                 deck                                     */
/************************************************************/




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
    private int reshuffleCount; // To me, Reshufflecount specifies the ith card to stop at. so 43 means the card at i = 43

    /**                                                   
    *      Constructor for a deck, Fills deck with 1 of each card type, based on the suit and rank enums.
    *      For poker, this will be 52 cards. Do note the hand is constructed in an ordered pattern, unshuffled
    *      @param reshuffleCount The value describing when to reshuffle the deck
    *      @throws PokerException If reshuffleCoint is > 52
    */
    // The param is only here due to it being a required parameter in the instructions. I still have to reshuffle a deck after creating it, and reshuffling will reroll this value
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


 // Instructions say to only account for > 52, not negative. I did 52 not 44 as this is a non-poker exclusive class, so out of bounds is a better error rather than a discard one, which would be exclusive to poker
        
        if(reshuffleCount > 52) 
            throw new PokerException("Deck's reshuffle count index is greater than that of the deck's size. Last card in the deck is at " + (deck.length - 1) + ". The reshuffle count value was referencing index " + reshuffleCount);
		this.reshuffleCount = reshuffleCount;
    }//end constructor
  

    
    /**                                                   
    *      Getter for the top value, which references where  the top of the draw pile is
    *      @return The index of the current top of the deck
    */
    int getTop(){return top;} 


    /**                                                   
    *      Getter for the reshuffleCount, which denotes when the deck should be reshuffled
    *      @return The index where a reshuffle is required to occur
    */
    int getReshuffleCount(){return reshuffleCount;}


    /**                                                   
    *      Returns the amount of cards left in the deck that haven't been drawn already
    *      @return The number of undrawn carfds left in the deck
    */
    int cardsLeft()
    {
        return deck.length - top; //note that if top = 52, it means deck is empty
    }

    /**                                                   
    *       Retrieves the card at the top of the draw pile, only allows the deal if not drawing past the reshuffleCount value
    *      @return The card drawn from the current top of the deck
    *      @throws PokerException If drawing a card past the reshuffleCount
    */
    Card deal() throws PokerException
    {
        if(top >= reshuffleCount) // This is why I made reshuffleCount's max val 44, as INDEX 44 would only allow 8 discards: 44 45 46 47 48 49 50 51
            throw new PokerException("Tried to withdraw card past the allowed reshuffle count, at index " + top + ". Index must be less than " + reshuffleCount);
        return deck[top++];
    }

    /**                                                   
    *      Retrieves the card at the top of the draw pile, ignoring if we pass reshuffleCount
    *      @return The card drawn from the current top of the deck
    */
    Card dealIgnoringReshuffle()// what is to be returned or to actually return?
    { 
        return deck[top++];
    }

    // 1, 3  max - min = 2


    /**                                                   
    *      Shuffles the cards in a deck in a randomized fashion, and changes the reshuffleCount (which denotes when to reshuffle)
    *      @param reshuffleCount The new reshuffleCount, enforced here as it should change between shuffles
    */
    public void shuffle(int reshuffleCount) {
        top = 0; // I believe I added this part
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

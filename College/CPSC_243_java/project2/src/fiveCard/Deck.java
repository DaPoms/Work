/**
 * fiveCard.Deck.java
 * CPSC243 Spring 2026
 * @author Griffin Nye
 */

    package fiveCard;

import fiveCard.Card.Rank;
import fiveCard.Card.Suit;
import fiveCard.Card.Suit;

/**
     * This class represents all data and operations for a deck 
     * of standard playing cards used in various casino 
     * games. Implemented in this package for the game fiveCardPoker.
     */
public class Deck 
{

    private Card[] deck; //Cards in the Deck
    private int top;     //Pointer/Index of top card in Shoe (next card to deal)

    /** 
     * Constructor
     */
    public Deck() 
    {
        top = 0;

        Suit[] suits = Card.Suit.values();
        Rank[] ranks = Card.Rank.values();
        int size = suits.length * ranks.length;
        Card[] deck = new Card[size]; //for poker, this is 52
        
    for(Card.Rank rank : Card.Rank.values())
    {   //it would be more efficient to create card here and then use a setter for the suit, but that would make us have to create a setter for suit, and I don't want that to be possible (no reason to change a card, should be immutable)
        
        // I liked the idea of a dynamic deck size for more code reusable (like to use for other card games)
        int i = 0;
        for(Card.Suit suit : suits)
        {
            Card cardToBeAdded = new Card(rank, suit); 
          
        }
    }
		
    }//end constructor
  
   /** 
   * Return all cards to the deck and shuffle
   * using the Fisher-Yates shuffling algorithm.
   */
    public void shuffle() {
        top = 0;

        for(int i = deck.length - 1; i > top; i--) 
        {
            int rnd = (int) (Math.random() * (i + 1) );
            Card temp = deck[rnd];
            deck[rnd] = deck[i];
            deck[i] = temp;
        }//end for
    
    }//end shuffle
  
}//end Shoe

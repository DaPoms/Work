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

    private Card[] deck; //Cards in the Deck
    private int top;     //Pointer/Index of top card in Shoe (next card to deal)

    /** 
     * Constructor
     */
    public Deck() 
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
		
    }//end constructor
  
    int cardleft()
    {
        return deck.length - top; //note that if top = 52, it means deck is empty
    }

    Card deal() // what is to be returned or to actually return?
    { // do we need error handling for when dealing a hand that is empty???
        return deck[top++];
    }




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

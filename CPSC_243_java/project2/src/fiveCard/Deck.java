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
public class Deck {

  private Card[] deck; //Cards in the Deck
  private int top;     //Pointer/Index of top card in Shoe (next card to deal)

  /** 
   * Constructor
   */
  public Deck() {
		
  }//end constructor
  
  /** 
   * Return all cards to the deck and shuffle
   * using the Fisher-Yates shuffling algorithm.
   */
  public void shuffle() {
    top = 0;

    for(int i = deck.length - 1; i > top; i--) {
      int rnd = (int) (Math.random() * (i + 1) );
      Card temp = deck[rnd];
      deck[rnd] = deck[i];
      deck[i] = temp;
    }//end for
    
  }//end shuffle
  
}//end Shoe

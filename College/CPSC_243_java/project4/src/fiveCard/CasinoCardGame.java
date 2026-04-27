/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  April 21, 2026                           */
/* Due Date:       April 24, 2026                           */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #4                                       */
/* Filename:       CasinoCardGame.java                      */
/* Purpose:        Abstract class that enforces the         */
/*                 structure required of a casino card game */
/************************************************************/

package fiveCard;

/**
 *  Abstract class that enforces the structure required for a casino card game
 * fiveCard.CasinoCardGame.java
 * CPSC243 Spring 2026
 * @author Daniel Tripoli
 */
public abstract class CasinoCardGame  {
    protected Deck deck;
    protected Hand dealer;
    protected Hand player;


    /**                                                   
    *     Constructor for CasinoCardGame
    *     @param player The player's hand
    *     @param dealer The dealer's hand
    *     @throws PokerException If reshuffleCount for deck is > 52
    */
    public CasinoCardGame(Hand player, Hand dealer) throws PokerException
    {
        deck = new Deck(-1); //I decided to have the actual card game do the deck shuffling, so we don't shuffle at the start here
        this.dealer = dealer; // Dynamic binding is used to enable other hand classes for game
        this.player = player;
    };

    /**                                                   
    *     Abstract method for running the casino card game's logic
    *     @param args Command line arguements for manual test cases. Must follow a fixed format of -p followed by 5 cards, then -d followed by 5 cards.
	*      Cards are referenced via a one character representation for their value (except for 10, the symbols are 2,3,4,5,6,7,8,9,10,J,Q,K,A) followed by the first letter of the suit name (C,S,H,D)
    */
    public abstract void play(String...args); 
    
} 


// MAKE SURE THAT THIS IS ADEQUATE

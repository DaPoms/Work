/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  April 21, 2026                           */
/* Due Date:       May 16th, 2026                           */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #6                                       */
/* Filename:       CasinoCardGame.java                      */
/* Purpose:        Abstract class that enforces the         */
/*                 structure required of a casino card game */
/************************************************************/

package fiveCard;

/**
 *  Abstract class that enforces the structure required for a casino card game.
 * fiveCard.CasinoCardGame.java
 * CPSC243 Spring 2026
 * @author Daniel Tripoli
 */
public abstract class CasinoCardGame  {
    /**                                                   
    *   Acts as the deck the player and dealer use for the card game
    */
    protected Deck deck;

    /**                                                   
    *   Acts as the dealer who plays against the player in a casino card game
    */
    protected Hand dealer;

    /**                                                   
    *   Acts as the player who plays against the dealer in the casino card game
    */
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

} 


// MAKE SURE THAT THIS IS ADEQUATE

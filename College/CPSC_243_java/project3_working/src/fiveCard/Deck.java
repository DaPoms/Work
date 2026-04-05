/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  Match 30, 2026                           */
/* Due Date:       April 6, 2026                            */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #3                                       */
/* Filename:       Deck.java                                */
/* Purpose:        Impliments the deck functionality used in*/
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
 // which means you can't do all the discards if i >= 44. 
 // Instructions say to only account for > 52, not negative. I did 52 not 44 as this is a non-poker exclusive class, so out of bounds is a better error rather than a discard one, which would be exclusive to poker
        this.reshuffleCount = reshuffleCount;
        if(this.reshuffleCount >= 52) // I'm assuming this is supposed to be >= not > like the instructions state as deal() is set to >=
            throw new PokerException("Deck's reshuffle count index is greater than that of the deck's size. Last card in the deck is at " + (deck.length - 1) + ". The reshuffle count value was referencing index " + this.reshuffleCount);
		
    }//end constructor
  

    /*************************************************************************/
    /*                                                                        
    /* Function name:   getTop
    /* Description:     Getter for the top value, which references where  the top of the draw pile is
    /* Parameters:      none
    /* Return Value:    int - The value of top (location of the top of the deck, in index form)
    /*
    /*************************************************************************/
    int getTop(){return top;} 

    /*************************************************************************/
    /*                                                                        
    /* Function name:   getReshuffleCount
    /* Description:     Getter for the reshuffleCount, which denotes when the deck should be reshuffled
    /* Parameters:      none
    /* Return Value:    int - T reshuffleCount value
    /*
    /*************************************************************************/
    int getReshuffleCount(){return reshuffleCount;}

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
    /* Description:     Retrieves the card at the top of the draw pile, only allows the deal if not drawing past the reshuffleCount value
    /* Parameters:      none
    /* Return Value:    Card - The card that is retrieved from the top of the deck pile
    /*
    /*************************************************************************/
    Card deal() throws PokerException
    {
        if(top >= reshuffleCount) // This is why I made reshuffleCount's max val 44, as INDEX 44 would only allow 8 discards: 44 45 46 47 48 49 50 51
            throw new PokerException("Tried to withdraw card past the allowed reshuffle count, at index " + top + ". Index must be less than " + reshuffleCount);
        return deck[top++];
    }


    /*************************************************************************/
    /*                                                                        
    /* Function name:   dealIgnoringReshuffle
    /* Description:     Retrieves the card at the top of the draw pile, ignoring if we pass reshuffleCount
    /* Parameters:      none
    /* Return Value:    Card - The card that is retrieved from the top of the deck pile
    /*
    /*************************************************************************/
    Card dealIgnoringReshuffle()// what is to be returned or to actually return?
    { // do we need error handling for when dealing a hand that is empty???
        return deck[top++];
    }

    // 1, 3  max - min = 2


    /*************************************************************************/
    /*                                                                        
    /* Function name:   shuffle
    /* Description:     Shuffles the cards in a deck in a randomized fashion, and changes the reshuffleCount (which denotes when to reshuffle)
    /* Parameters:      int reshuffleCount - The new reshuffleCount, enforced here as it should change between shuffles
    /* Return Value:    void
    /*
    /*************************************************************************/
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

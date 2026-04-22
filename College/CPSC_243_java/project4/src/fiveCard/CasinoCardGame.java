package fiveCard;

public abstract class CasinoCardGame <E extends Hand> {
    protected Deck deck;
    protected E dealer;
    protected E player;


    public CasinoCardGame(E dealer, E player) throws PokerException
    {
        deck = new Deck(-1); //I decided to have the actual card game do the deck shuffling, so we don't shuffle at the start here
        this.dealer = dealer; // Using an aggregational relationship as its easy + even without a card game, the player + dealer should still exist
        this.player = player;
    };



    public abstract void play();
    
}


// MAKE SURE THAT THIS IS ADEQUATE

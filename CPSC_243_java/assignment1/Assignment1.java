/************************************************************/
/* Author: Daniel Tripoli                                   */
/* Major: Computer Science                                  */
/* Creation Date: February 13, 2026                         */
/* Due Date: February 20, 2026                              */
/* Course: CPSC 243 010                                     */
/* Professor Name: Griffin Nye                              */
/* Assignment: #1                                           */
/* Filename: assignment1.txt                                */
/* Purpose: Impliment hand system + win/lose hand mechanic  */
/*                    of poker                              */
/*                                                          */
/************************************************************/
import java.util.Scanner;
import java.util.HashSet;
import java.util.Arrays; 

public class Assignment1 {
    // ranked from lowest to highest value (EX: royal flush is better than high card)
    private enum Ranking 
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
    
    private static final String[] ranks = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    private static final String[] suits = {"C","D","H","S"};
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        int[] deck = new int[52];
        int[] player = new int[5];
        int[] dealer = new int[5];
        welcome(cin);
        populateDeck(deck);
        shuffle(deck);
        
        if(args.length > 0) {
            parseCmdLineArgs(args, player, dealer); //STUDENT: Insert player and dealer arrays in call here
        } else {
        //STUDENT: Insert method calls for populating the hands yourself using a shuffled deck here
            int deckI = dealHands(deck, player, dealer); // The current position in the deck is saved for usage in what I assume we'll have to do for future assignments
        }//end if

        Arrays.sort(player);
        Arrays.sort(dealer);    // I only do this as we were instructed to focus on one operation and a time, so dealHands() does not sort.

        int playerRanking = determineRanking(player);
        int dealerRanking = determineRanking(dealer);
         
        boolean isPlayerWinner = isPlayerWinner(playerRanking, player, dealerRanking, dealer);
        printResult(player, playerRanking, dealer, dealerRanking, isPlayerWinner);
        
    }//end main

/*************************************************************************/
/*                                                                        
/* Function name:   rankingScoreIntToString 
/* Description:     Converts the int value/score of a ranking to its String representation
/* Parameters:      int ranking - The int representation of a hand's ranking (can only be 0-9) 
/* Return Value:    String - The String representation of the passed ranking score
/*
/*************************************************************************/
public static String rankingScoreIntToString(int ranking)
{
    return switch(ranking)
    {
        case 0 -> "High Card"; 
        case 1 -> "One Pair";
        case 2 -> "Two Pair";
        case 3 -> "Three of a Kind";
        case 4 -> "Straight";
        case 5 -> "Flush";
        case 6 -> "Full House";
        case 7 -> "Four of a Kind";
        case 8 -> "Straight Flush";
        case 9 -> "Royal Flush";
        default -> "ERROR";
    };
}

/*************************************************************************/
/*                                                                        
/* Function name:   printResult 
/* Description:     Displays to the terminal a visual representation of the poker game's result, 
                    printing the dealer and player hands, what ranking each hand achieved, and who won.
/* Parameters:      int[] player - An array representing the player's poker hand, with each card represented through its unique ID (0-51)
                    int playerRanking - The value the player's hand contains, represented as an int (0 = lowest/worst ranking, 9 = highest/best)
                    int[] dealer - An array representing the dealer's poker hand, with each card represented through its unique ID (0-51)
                    int dealerRanking - The value the dealer's hand contains, represented as an int (0 = lowest/worst ranking, 9 = highest/best)
                    boolean isPlayerWinner - True when the player's hand is the winner (beats the dealer), false otherwise.
/* Return Value:    void 
/*
/*************************************************************************/
public static void printResult(int[] player, int playerRanking, int[] dealer, int dealerRanking, boolean isPlayerWinner)
{
    String[] stringPlayer = stringifyHand(player);
    String[] stringDealer = stringifyHand(dealer);
    String stringPlayerRank = rankingScoreIntToString(playerRanking);
    String stringDealerRank = rankingScoreIntToString(dealerRanking);
    displayStringifiedHand(stringPlayer, "Your hand:\nYou got a " + stringPlayerRank + ".");
    System.out.println("\n-----------------------------\n");
    displayStringifiedHand(stringDealer, "Dealer's hand:\nThe dealer got a " + stringDealerRank + ".");

    if(isPlayerWinner) System.out.println("You win!");
    else System.out.println("You lose! :C");
}


/*************************************************************************/
/*                                                                        
/* Function name:   determineHighestCard 
/* Description:     Determines and returns the highest card that played a role in the hand's ranking.
/* Parameters:      int ranking - The int representation of a hand's ranking (can only be 0-9) 
                    int[] hand - An array representing the passed poker hand (of size 5), with each card represented through its unique ID (0-51)
/* Return Value:    int - The value of the the highest card in the hand for the passed ranking
/*
/*************************************************************************/
public static int determineHighestCard(int ranking, int[] hand) // TEST A LOTTTTTTTTTTTTTTT
{ // For future (not current assignment): (what if its a two way tie? EX: P = 5 5 3 2 A  = 5 5 3 2 J) Also royal flush tie's are so rare theres no reason to program for it
    int[] rankOccurences = new int[ranks.length];
    extractHandAttributes(hand, rankOccurences); // I know the name is plural but it only extracts a singular attribute, but I wanted to do polymorphism :C
    if( (ranking > Ranking.HIGH_CARD.ordinal() && ranking < Ranking.STRAIGHT.ordinal()) || ranking == Ranking.FOUR_OF_A_KIND.ordinal()) // cases where the highest card needs to be considered only from the solution space. I call them the "pair" rankings (THIS IS CORRECT YES? the tie breaker is the card that contributed to rankingbodrfjierjbriotbjoerib jortiob jrtb jirtrtb jibjiortbjikort)
    {
        int arr[][] = top2RankDuplicates(rankOccurences); // we do all this work just to get the identity  of the pairs/cards used for the "kind" based rankings
        if(arr[0][0] == 0) return 13; // edge cases for aces (always treated as highest). arr[0][0] == 0 means if the 1st card of top 2 duplicates has the value 0 then it returns it (which is the value for ace)
        if(arr[1][0] == 0 && arr[1][1] > 1) return 13; //we need to account for one pair with the arr[1][1] > 1 as we must only consider the 1 pair for 1 pair (DUH!)
        return (arr[1][1] <= 1 || arr[0][0] > arr[1][0]) ? arr[0][0] : arr[1][0]; // arr[#][0] the 0 references the card's value, # references my artificial card struct. Returns the higher card out of the top 2 duplicates
    }   // in the above, arr[1][1] <= 1 states that if there is no additional pair (only 2 pair will have an additional pair case), then we automatically return the 1st pair instead
    
    // note that full house would also work if allowed in the above statement too. Its just less demanding over here
    if(rankOccurences[0] != 0) //if hand contains ace... note at this point we have high card, straight, flush, full house, straigth flush, and royal flush
    {
        if (( ranking != Ranking.STRAIGHT.ordinal() && ranking != Ranking.STRAIGHT_FLUSH.ordinal() ) || rankOccurences[12] != 0)//The straight treats ace as higher value if ace is placed at the top of an ascending order (cards from 10 - king must be present in hand in order for ace to be highest card)
            return 13; // I separated these two cases just to make my code more vertical
    }

    //Only case that this is used is if a case does not appear in our hand or the ace is used as the lowest value in the ascending order
    int i = rankOccurences.length - 1; // start at the end (the end is the highest card)
    while(rankOccurences[i] == 0) //returns the first highest value card in the hand
        --i; 

    return i; // note that value is determined by it's index in the rankOccurence array due to the lowest value card being at the end (sometimes ace) and the highest at the top (K)
}

/*************************************************************************/
/*                                                                        
/* Function name:   isPlayerWinner
/* Description:     Given the ranking between hands, returns if the player beat the dealer or not. Also deals with the case of a tie (having the same ranking)
/* Parameters:      int[] player - An array representing the player's poker hand, with each card represented through its unique ID (0-51)
                    int playerRanking - The value the player's hand contains, represented as an int (0 = lowest/worst ranking, 9 = highest/best)
                    int[] dealer - An array representing the dealer's poker hand, with each card represented through its unique ID (0-51)
                    int dealerRanking - The value the dealer's hand contains, represented as an int (0 = lowest/worst ranking, 9 = highest/best)
/* Return Value:    boolean - Returns true if the player beat the dealer in the game of poker, false other wise.
/*
/*************************************************************************/
public static boolean isPlayerWinner(int playerRanking, int[] player, int dealerRanking, int[] dealer)
{
    if(playerRanking < dealerRanking)
        return false;
    else if (playerRanking == dealerRanking) // case of a 'tie', highest card wins
    {
        int playerHighest = determineHighestCard(playerRanking, player);
        int dealerHighest = determineHighestCard(dealerRanking, dealer);
        if(playerHighest < dealerHighest) return false;
    }
    return true;
}

/*************************************************************************/
/*                                                                        
/* Function name:   top2RankDuplicates
/* Description:     Finds the top 2 cards in terms of their quantity in a hand and returns them in a 2d array.
/* Parameters:      int[] ranks - An array containing all the ranks a poker hand contains and their respective quantities (includes all ranks, but one's not included in the hand are set to 0). 
                    ranks is addressed from 0-12, with index 0 being ace and 12 being king.
/* Return Value:    int[][] - The representation of the top 2 cards in terms of quantity. the first [] is for the card, 
                    with [0] being the highest quantity and [1] being the second highest quantity. the second [] is for the actual quantity of that card, 
                    so [0][1] would return the quantity of the first card
/*
/*************************************************************************/
public static int[][] top2RankDuplicates(int[] ranks) //returns the 2 cards in hand with the most occurences of their rank (EX: 3 Aces and 1 Jack)
{
    int top2CardRanks[][] = new int[2][2]; // by "rank" I mean the value of the card. We are tracking the amount of pairs in this
    int i = 0;
    int topArrI = 0;
    while(topArrI < 2) // initializes top2CardRank array with the 1st two cards (the count of the lowest rank cards)
    {
        if(ranks[i] != 0) 
        {
            top2CardRanks[topArrI][0] = i;
            top2CardRanks[topArrI][1] = ranks[i];
            topArrI++;
        }
        i++;
    }

    for(; i < ranks.length; i++) // for remaining cards, we try to find cards in our hand that have a higher quantity than the current top values
    {
        for(int[] currHighestStruct: top2CardRanks)
            if(ranks[i] > currHighestStruct[1])
            {
                currHighestStruct[0] = i;
                currHighestStruct[1] = ranks[i];
                break; // we must break here to prevent writing the same solution twice
            }
    }

    //lazy ordering check at the end to ensure first row contains the highest pair card
    if(top2CardRanks[1][1] > top2CardRanks[0][1])
    {
        int[] placeholder = top2CardRanks[0];
        top2CardRanks[0] = top2CardRanks[1];
        top2CardRanks[1] = placeholder;
    }
    return top2CardRanks; //note the answer is ordered, so that the first row is the highest pair card and the 2nd is the 2nd highest pair card in the hand
}

/*************************************************************************/
/*                                                                        
/* Function name:   isSameSuit
/* Description:     Returns whether or not all the cards in a given poker hand are from the same suit
/* Parameters:      int[] suitOccurences - The array holding the suits and the occurences of each suit for a given hand. 
                    The array's index range is 0-3, with 0 being clubs, 1 being diamonds, 2 hearts, and 3 being spades
/* Return Value:    boolean - True if hand has cards of all the same suit, false otherwise
/*
/*************************************************************************/
public static boolean isSameSuit(int[] suitOccurences)
{
    for(int i : suitOccurences)
        if(i != 0 && i != 5) //if any cards are in a different suit (not = 5 cards/entire hand), then false.
            return false;
    return true;
}

/*************************************************************************/
/*                                                                        
/* Function name:   isAscending
/* Description:     Returns if a given hand is in ascending order
/* Parameters:      int[] rankOccurences-  An array containing all the ranks a poker hand contains and their respective quantities (includes all ranks, but one's not included in the hand are set to 0). 
                    ranks is addressed from 0-12, with index 0 being ace and 12 being king.
/* Return Value:    boolean - True if the passed rank representation of the poker hand is in ascending order
/*
/*************************************************************************/
public static boolean isAscending(int[] rankOccurences) //determines if hand is ascending based off of 
{
    
    if(rankOccurences[0] != 0 && rankOccurences[1] == 0) //if an ace exists but it isnt ascending in terms of ace being the minimum, we treat ace as a maximum value instead
    {
        for(int i = rankOccurences.length - 4; i < rankOccurences.length; i++) // if ace is the max, then ascending is only considered when the cards are 10 J Q K A. This checks for 10 J Q K
            if(rankOccurences[i] == 0) 
                return false;
    }
    else
    {
    int i = 0;
    while(rankOccurences[i] == 0) i++; //sets up to the first card we have from our hand 
    int endpoint = i + 5; // endpoint is 4 spaces from where the lowest rank card is
    if(endpoint > rankOccurences.length) return false; //edge case where if the 1st card in ascending order is a 10, then it cannot be strictly ascending order
    for(; i < endpoint ; i++)
        if(rankOccurences[i] == 0) 
            return false;
    }
  return true;
}

/*************************************************************************/
/*                                                                        
/* Function name:   extractHandAttributes
/* Description:     Aquires the quantity of each card type from a given poker hand and stores it in the passed rankOccurencesHolder array
/* Parameters:      int[] hand - An array representing the passed poker hand (of size 5), with each card represented through its unique ID (0-51)
                    int[] rankOccurencesHolder - The array that holds the quantity of each rank from the hand
/* Return Value:    void
/*
/*************************************************************************/
public static void extractHandAttributes(int[] hand, int[] rankOccurencesHolder) // I just wanted to use polymorphism (even though "attributes" doesn't make sense when theres only 1 attribute we extract)
{
    for(int cardID : hand)
    {
        int rank = cardID % 13; //int and rank are stored in their int form, so if you did ranks[rank] it would give the actual rank symbol, same with the suit.
        rankOccurencesHolder[rank]++;
    }
}

/*************************************************************************/
/*                                                                        
/* Function name:   extractHandAttributes
/* Description:     Aquires the quantity of each card type from a given poker hand and stores it in the passed
                    rankOccurencesHolder array and also gets the occurences of each suit from the hand to store in suitOccurencesHolder
/* Parameters:      int[] hand - An array representing the passed poker hand (of size 5), with each card represented through its unique ID (0-51)
                    int[] rankOccurencesHolder - The array that holds the quantity of each rank from the hand (answer is stored via parameters due to there being two arrays)
                    nt[] suitOccurencesHolder - The array that holds the suit count of each suit from the card in a poker hand
/* Return Value:    void (answer storage done via int[] parameters)
/*
/*************************************************************************/
public static void extractHandAttributes(int[] hand, int[] suitOccurencesHolder, int[] rankOccurencesHolder) // solution is stored in the holder parameters
{
    for(int cardID : hand)
    {
        int rank = cardID % 13; //int and rank are stored in their int form, so if you did ranks[rank] it would give the actual rank symbol, same with the suit.
        int suit = cardID / 13;
        rankOccurencesHolder[rank]++;
        suitOccurencesHolder[suit]++;
    }
}



/*************************************************************************/
/*                                                                        
/* Function name:   determineRanking
/* Description:     determines what ranking a given hand has (High card, two pair, etc...)
/* Parameters:      int[] hand - An array representing the passed poker hand (of size 5), with each card represented through its unique ID (0-51)
/* Return Value:    int - the score/value attributed to that ranking (I used enum's and converted them to ints to make the value comparing much more readable)
/*
/*************************************************************************/
//things to check for ranking:
// 1. Suit amounts
// 2. Rank types (check for pairs)
// 3. Ascending order (because we sort already), for now, ignore ace
public static int determineRanking(int[] hand) // determines the ranking of a given hand
{ // returns a score from low to high representing its ranking, with 0 being high card ranking and 9 being royal flush
    int[] suitOccurences = new int[suits.length]; // Keeps track of how many cards in each suit for the hand   // IS THIS ALLOWED IN JAVA?
    int[] rankOccurences = new int[ranks.length]; //keeps track of how many of each card rank
    extractHandAttributes(hand, suitOccurences, rankOccurences); 

    //The 3 determiners of what type of ranking the hand has
    boolean isSameSuit = isSameSuit(suitOccurences);
    boolean isAscending = isAscending(rankOccurences);
    int[][] top2CardCount = top2RankDuplicates(rankOccurences);


    //Determining the hand type
    //Must be done in order of highest to lowest ranking to make sure we don't give something like a royal flush something like a straight 

    if(isAscending) // this block counts for straight flush and royal flush ()
    { // TO DO: MAKE ACE BE CONSIDERED AS TOP FOR 10 J Q K A REIJGOIEJGJOREJOIDJIJOIJOIJSOIJOS
        if(isSameSuit) 
         {
            if(rankOccurences[9] != 0 && rankOccurences[0] != 0) return Ranking.ROYAL_FLUSH.ordinal();
            return Ranking.STRAIGHT_FLUSH.ordinal();
        }
    }

    if(top2CardCount[0][1] == 4) // 4 of a kind case
        return Ranking.FOUR_OF_A_KIND.ordinal();
    
    if(top2CardCount[0][1] == 3 && top2CardCount[1][1] == 2)//Full house case
        return Ranking.FULL_HOUSE.ordinal();

    if(isSameSuit) //Flush case
        return Ranking.FLUSH.ordinal(); 

    if(isAscending) //Straight case
        return Ranking.STRAIGHT.ordinal();

    if(top2CardCount[0][1] >= 2) //for 3 of a kind, two pair, and one pair all together
    {
        if(top2CardCount[0][1] == 3) // case for three of a kind
            return Ranking.THREE_OF_A_KIND.ordinal();
        if(top2CardCount[1][1] == 2) //case for two pair
            return Ranking.TWO_PAIR.ordinal();
        return Ranking.ONE_PAIR.ordinal(); // implicit case for one pair (if there exists a >=2 grouping that <3 and does not have an additional 2 grouping, then its a one pair)
    }

    return Ranking.HIGH_CARD.ordinal();

}

/*************************************************************************/
/*                                                                        
/* Function name:   displayStringifiedHand
/* Description:     prints a hand that has already been converted into a string, introducing it with whatever title is passed
/* Parameters:      String[] hand - An array representing the poker hand (of size 5), with each card represented through 2-3 chars.
                    the first 1-2 chars are for the name (A,2,3,4,5,6,7,8,9,10,J,Q,K) and the last char is for the suit (C,D,H,S == club, diamond, heart, spade)
                    String title - the additional message we want to introduce printing the hand with (will be printed above the hand display)
/* Return Value:    void
/*
/*************************************************************************/
public static void displayStringifiedHand(String[] hand, String title)
{
  System.out.println(title);
  for(String card : hand) // decided to use for each loop to have more formatting and less memory usage than that of Arrays.toString()
    System.out.print(card + " ");
  // insert rank here (flush, high card, etc...)
  System.out.println();
}

/*************************************************************************/
/*                                                                        
/* Function name:   stringifyHand
/* Description:     Turns the integer representation of a poker hand's cards into a string form
/* Parameters:      int[] hand - An array representing the passed poker hand (of size 5), with each card represented through its unique ID (0-51)
/* Return Value:    String[] - the string representation of the passed poker hand (each index leads to another card in the hand, 5 total)
/*
/*************************************************************************/
public static String[] stringifyHand(int[] hand)
{
    String[] stringifiedHand = new String[hand.length]; //each card is held as 1 string in the string array
    for(int i = 0; i < hand.length; i++)
    {
        stringifiedHand[i] = ranks[hand[i] % 13];
        stringifiedHand[i] += suits[hand[i] / 13]; // could use StringBuilder, but this is not a lot of appending
    }
    return stringifiedHand;
}

/*************************************************************************/
/*                                                                        
/* Function name:   SortHands
/* Description:     Very basic function that just sorts the player and dealer's hand by each card's id value
/* Parameters:      int[] player - the int representation of the player's poker hand
                    int[] delaer - the int representatio nof the dealer's poker hand
/* Return Value:    void
/*
/*************************************************************************/
public static void sortHands(int[] player, int[] dealer)
{
    Arrays.sort(player);
    Arrays.sort(dealer);
}

/*************************************************************************/
/*                                                                        
/* Function name:   dealHands
/* Description:     Provides both the player and dealer in a game of poker with their poker hands, stored in int[] form
/* Parameters:      int[] deck - The deck of cards used in the poker game, with there being 52 cards total numbered from 0-51.
                    Cards should be shuffled prior to using dealHands() for the first time through
                    int[] player - The player's empty hand where their dealt hand will be stored
                    int[] dealer - The dealer's empty hand where their dealt hand will be stored
/* Return Value:    int - the index to the face of the draw pile after doing these draws
/*
/*************************************************************************/
public static int dealHands(int[] deck, int[] player, int[] dealer) //returns current deck position
{
    int currDeckI = 0; // the current deck position (the face of the draw pile)
    currDeckI = fillHand(player, deck, currDeckI);
    currDeckI = fillHand(dealer, deck, currDeckI);
    return currDeckI; //currDeckI would be used for the future drawing/discard mechanic, and also if multiple turns are implimented
}

/*************************************************************************/
/*                                                                        
/* Function name:   fillHand
/* Description:     Fills the passed hand with 5 cards from the draw pile
/* Parameters:      int[] handReciever - What recieves the poker hand that we are filling.
                    int[] deck - Where we draw from. This should be a shuffled deck of cards numbered from 0-51
/* Return Value:    int - the index to the face of the draw pile after doing this draw
/*
/*************************************************************************/
public static int fillHand(int[] handReciever, int[] deck, int currDeckI)
{
    int handI = 0;
    int endCurrDeckI = currDeckI + 5; // index of where draw ended. Currently would seg fault if we draw more than 10 times, but it's like this as a reshuffle mechanic is not required for this assignment (i.e what to do when deck is all used up)
    for(; currDeckI < endCurrDeckI; currDeckI++) // this will need to be altered in the future, but works for the 1st hand
    {
        handReciever[handI] = deck[currDeckI];
        ++handI;
    }
    return currDeckI;
}

/*************************************************************************/
/*                                                                        
/* Function name:   askUserName
/* Description:     Asks the user for a name and then returns what they entered
/* Parameters:      Scanner cin - The scanner object we use to read user input
/* Return Value:    String - The username that the user enters
/*
/*************************************************************************/
public static String askUserName(Scanner cin)
{
    System.out.print("Enter your username: ");
    return cin.nextLine();
}

/*************************************************************************/
/*                                                                        
/* Function name:   welcome
/* Description:     Asks the user for their name and then greets them to Poker, referencing their name
/* Parameters:      Scanner cin - The Scanner object we use to read user input
/* Return Value:    void
/*
/*************************************************************************/
public static void welcome(Scanner cin)
{
    System.out.println("Welcome to the game of Poker, " + askUserName(cin) + "!\n");
}

/*************************************************************************/
/*                                                                        
/* Function name:   populateDeck
/* Description:     Fills the passed deck with cards represented as ints, from 0 to whatever size the deck is. For poker, it is 52
/* Parameters:      int[] deck - The empty (or will overwrite) deck that we add ascendingly numbered cards via int representation.
/* Return Value:    void
/*
/*************************************************************************/
public static void populateDeck(int[] deck) // I really only made this as I like the context the function name gives (maybe useful in the future????)
{
    for(int i = 0; i < deck.length; i++)
        deck[i] = i;
} 

////////////////


private static void shuffle(int[] d) //premade code from professor ( I assume we do not need to document this because you provided it, and it's kind of common sense what this does)
{
    for(int i = d.length - 1; i > 0; i--) {
        int rnd = (int) (Math.random() * (i + 1));
        int temp = d[i];
        d[i] = d[rnd];
        d[rnd] = temp;
    }//end for
}//end shuffle

  public static void parseCmdLineArgs(String[] args, int[] player, int[] dealer) {

    if (player == null || dealer == null)
      throw new IllegalArgumentException("Player and dealer arrays cannot be null.");
    
    if (player.length != 5 || dealer.length != 5)
      throw new IllegalArgumentException("Player and dealer arrays must both be length 5.");
    
    boolean sawP = false;
    boolean sawB = false;
    
    int pIndex = 0;
    int dIndex = 0;
    int mode = 0;
    
    HashSet<Integer> used = new HashSet<>();
    
    for(int i = 0; i < args.length; i++) {
      
      String token = args[i].toUpperCase();
      
      if( token.equals("-P") ) {
        sawP = true;
        mode = 1;
        continue;
      }//end if

      if( token.equals("-D") ) {
        sawB = true;
        mode = 2;
        continue;
      }//end if
      
      
      if(mode == 0) {
        throw new IllegalArgumentException("Card '" + token +
                                           "' provided before a flag. Use -p and -d.");
      }//end if
      
      int id = convertToId(token);
      if(id == -1) {
        throw new IllegalArgumentException("Invalid card: " + token + " (expected e.g., AS, 10H, QC)");
      }//end if

      if( !used.add(id) ) {
        throw new IllegalArgumentException("Duplicate card specified: " + token);
      }//end if
      
      if(mode == 1) {
        if(pIndex >= 5)
          throw new IllegalArgumentException("Too many player cards. Exactly 5 required.");
        player[pIndex++] = id;
      } else {
        if(dIndex >= 5)
          throw new IllegalArgumentException("Too many dealer/banker cards. Exactly 5 required.");
        dealer[dIndex++] = id;
      }//end if
      
    }//end for

    if (!sawP || !sawB) {
      throw new IllegalArgumentException("Both -p and -d must be specified.");
    }//end if

    // Exactly 5 cards each
    if(pIndex != 5 || dIndex != 5) {
      throw new IllegalArgumentException("Exactly 5 cards must be specified for each hand. " +
                                         "Got player=" + pIndex + ", dealer=" + dIndex + ".");
    }//end if
    
  }//end

  public static int convertToId(String card) {

    if (card == null) return -1;
    
    card = card.trim().toUpperCase();
    if(card.length() < 2 || card.length() > 3) return -1;

    String rankStr = card.substring(0, card.length() - 1);
    String suitStr = card.substring(card.length() - 1);

    String[] ranks = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    String[] suits = {"C","D","H","S"};

    int rankIndex = -1;
    int suitIndex = -1;
    
    for(int i = 0; i < ranks.length; i++) {
      if( ranks[i].equals(rankStr) ) {
        rankIndex = i;
        break;
      }//end if
    }//end for

    for(int i = 0; i < suits.length; i++) {
      if( suits[i].equals(suitStr) ) {
        suitIndex = i;
        break;
      }//end if
    }//end for
    
    if(rankIndex == -1 || suitIndex == -1) return -1;
    
    return suitIndex * 13 + rankIndex;
    
  }//end converToId

  
}//end Assignment1

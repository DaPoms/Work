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
import java.util.Arrays; // Is this allowed ?!?!?!?!?!??!?!?!?!?

public class Assignment1 {
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

        Arrays.sort(player); // is this allowed ? REIJOIRJJGEIJRJOGEGIJIGRGROIJGJREGIGRJEOJIJJJJIOJIJOJJOIOIJ
        Arrays.sort(dealer);    // I only do this as we were instructed to focus on one operation and a time, so dealHands() does not sort.
        String[] stringPlayer = stringifyHand(player);
        String[] stringDealer = stringifyHand(dealer);

        

        determineRanking(player);
        determineRanking(dealer);
        displayStringifiedHand(stringPlayer, "Your hand:");
        displayStringifiedHand(stringDealer, "Dealer's hand:");
    }//end main

public static boolean top2RankDuplicates() //returns the 2 cards in hand with the most occurences of their rank (EX: 3 Aces and 1 Jack)
{
    return -1;
}

//Code I made:///
public static boolean isSameSuit(int[] suitOccurences)
{
    for(int i : suitOccurences)
        if(i != 0 && i != 5) //if any cards are in a different suit (not = 5 cards/entire hand), then false.
            return false;
    return true;
}

// is a sorted hand by rank order or by cardID REIJOJGEIROGJROGERJGIJREOIJREOIJGROIJGOIJGEGOIJREGJJOGEGOIJGOIJROIJGEJRGREOJGE
public static boolean isAscending(int[] rankOccurences) //determines if hand is ascending based off of 
{
    int i = 0;
    while(rankOccurences[i] == 0) i++; //sets up to the first card we have from our hand 
    int endpoint = i + 5; // endpoint is 4 spaces from where the lowest rank card is
    for(; i < endpoint ; i++)
        if(rankOccurences[i] == 0) 
            return false;
  return true;
}

//things to check for ranking:
// 1. Suit amounts
// 2. Rank types (check for pairs)
// 3. Ascending order (because we sort already), for now, ignore ace
public static int determineRanking(int[] hand) // determines the ranking of a given hand
{ // returns a score from low to high representing its ranking, with 0 being high card ranking and 9 being royal flush
    int[] suitOccurences = new int[suits.length]; // Keeps track of how many cards in each suit for the hand   // IS THIS ALLOWED IN JAVA?
    int[] rankOccurences = new int[ranks.length]; //keeps track of how many of each card rank

    
        
    //maybe switch cases???? (return from highest -> lowest)
    for(int cardID : hand)
    {
        int rank = cardID % 13; //int and rank are stored in their int form, so if you did ranks[rank] it would give the actual rank symbol, same with the suit.
        int suit = cardID / 13;
        rankOccurences[rank]++;
        suitOccurences[suit]++;
    }

    //isAscending(rankOccurences); // debug code!!!!!!
    isSameSuit(suitOccurences);
    //determine from high to low
    //note only case of ace being high in ranking is a straight (5 consecutives)
    // max pair counter
    int consecutiveStreak = 0; //MAKE INTO A SEPARATE FUNCTION IREJGOIERJEGIEOIJGREOIRJGIJEROJGEIRGOIJEIIHGEIGH
    int[] maxKind = new int[2]; // keeps track of the max amount of "kinds" of each card (ex: 4 of a kind)
    for(int rankCount : rankOccurences)
    {
        if(rankCount == 0)
        {
            if(consecutiveStreak != 0)
                consecutiveStreak = -10; // means streak was beaten, made negative just so we can check if -, then it means it is not consecutive 
        }
        else consecutiveStreak++;
    }

  return -1;
}

public static void displayStringifiedHand(String[] hand, String title)
{
  System.out.println(title);
  for(String card : hand) // decided to use for each loop to have more formatting and less memory usage than that of Arrays.toString()
    System.out.print(card + " ");
  // insert rank here (flush, high card, etc...)
  System.out.println();
}
public static String[] stringifyHand(int[] hand)
{
    String[] stringifiedHand = new String[hand.length];
    for(int i = 0; i < hand.length; i++)
    {
        stringifiedHand[i] = ranks[hand[i] % 13];
        stringifiedHand[i] += suits[hand[i] / 13]; // could use StringBuilder, but this is not a lot of appending
    }
    return stringifiedHand;
}

public static void sortHands(int[] player, int[] dealer)
{
    Arrays.sort(player);
    Arrays.sort(dealer);
}

public static int dealHands(int[] deck, int[] player, int[] dealer) //returns current deck position
{
    int currDeckI = 0;
    currDeckI = fillHand(player, deck, currDeckI);
    currDeckI = fillHand(dealer, deck, currDeckI);
    return currDeckI;
}
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

public static String askUserName(Scanner cin)
{
    System.out.print("Enter your username: ");
    return cin.nextLine();
}
public static void welcome(Scanner cin)
{
    System.out.println("Welcome to the game of Poker, " + askUserName(cin) + "!");
}

public static void populateDeck(int[] deck) // I really only made this as I like the context the function name gives
{
    for(int i = 0; i < deck.length; i++)
        deck[i] = i;
} 

////////////////


private static void shuffle(int[] d) //premade code from professor
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

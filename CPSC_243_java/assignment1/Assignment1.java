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
    // ranked from lowest to highest value (royal flush is better than high card)
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

        Arrays.sort(player); // is this allowed ? REIJOIRJJGEIJRJOGEGIJIGRGROIJGJREGIGRJEOJIJJJJIOJIJOJJOIOIJ
        Arrays.sort(dealer);    // I only do this as we were instructed to focus on one operation and a time, so dealHands() does not sort.
        String[] stringPlayer = stringifyHand(player);
        String[] stringDealer = stringifyHand(dealer);

        
        
        System.out.println("player rank = " + determineRanking(player));
        System.out.println("dealer rank = " + determineRanking(dealer));
        
        displayStringifiedHand(stringPlayer, "Your hand:");
        displayStringifiedHand(stringDealer, "Dealer's hand:");
    }//end main

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
    if(endpoint > rankOccurences.length) return false; //edge case where if the 1st card in ascending order is a 10, then it cannot be strictly ascending order
    for(; i < endpoint ; i++)
        if(rankOccurences[i] == 0) 
            return false;
  return true;
}


public static void extractHandAttributes(int[] hand, int[] rankOccurencesHolder) // I just wanted to use polymorphism (even though "attributes" doesn't make sense when theres only 1 attribute we extract)
{
        for(int cardID : hand)
    {
        int rank = cardID % 13; //int and rank are stored in their int form, so if you did ranks[rank] it would give the actual rank symbol, same with the suit.
        rankOccurencesHolder[rank]++;
    }
}

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
            if(rankOccurences[9] != 0) return Ranking.ROYAL_FLUSH.ordinal();
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
    String[] stringifiedHand = new String[hand.length]; //each card is held as 1 string in the string array
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

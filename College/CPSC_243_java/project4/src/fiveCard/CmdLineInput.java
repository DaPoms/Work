/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  April 21, 2026                           */
/* Due Date:       April 24, 2026                           */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #4                                       */
/* Filename:       CmdLineInput.java                        */
/* Purpose:        For me, mainly just to write JavaDoc		*/
/*				   documentation. For poker, this implements*/
/*                 the testing system via command line      */                            
/************************************************************/

package fiveCard;
import java.util.Arrays;
import java.util.Map;
import java.util.HashMap;
import java.util.Map.Entry;

/**
 * fiveCard.CmdLineInput.java
 * CPSC243 Spring 2026
 * @author Griffin Nye
 * @author (documented by) Daniel Tripoli
 * @brief Enables command line input and validation for populating player and banker hands for smoother testing.
 */
public class CmdLineInput {

  private static Map<String, Integer> rankMap = new HashMap<>();
  private static Map<String, Integer> suitMap = new HashMap<>();
  private static int pidx = 0;
  private static int didx = 0;
 
  public static void populateRankMap() {
    rankMap = Map.ofEntries( Map.entry("2", 0), Map.entry("3", 1), Map.entry("4", 2),
                             Map.entry("5", 3), Map.entry("6", 4), Map.entry("7", 5),
														 Map.entry("8", 6), Map.entry("9", 7), Map.entry("10", 8), 
														 Map.entry("J", 9), Map.entry("Q", 10), Map.entry("K", 11),
														 Map.entry("A", 12) );
  }//end populateRankMap


	/**                                                   
    *      Populates map with all possible card suits
    */
  public static void populateSuitMap() {
    suitMap = Map.of("C", 0, "D", 1, "H", 2, "S", 3);
  }//end populateSuitMap

	/**                                                   
	*      Parses command line argument and populates hands with the input
  	*      @param args The command line argument that must follow a fixed format of -p followed by 5 card, then -d followed by 5 cards.
	*      Cards are referenced via a one character representation for their value (except for 10, the symbols are 2,3,4,5,6,7,8,9,10,J,Q,K,A) followed by the first letter of the suit name (C,S,H,D)
  	*      @param player The player hand which gets populated with the -p flag of the command line argument
	*      @param dealer The dealer hand which gets populated with the -d flag of the command line argument
	*/
	public static void parseArguments(String[] args, Hand player, Hand dealer) {

    if( rankMap.isEmpty() ) populateRankMap();
    if( suitMap.isEmpty() ) populateSuitMap();

    if( player == null || dealer == null)
      throw new IllegalArgumentException("Player and Dealer hands cannot be null");
    
    if(args.length < 12)
      throw new IllegalArgumentException("Not enough cards provided in input, or a flag has been omitted.");
      
		for (int i = 0; i < args.length; i++) {
			String flag = args[i];

			if ("-p".equals(flag)) {
				i++;
				while (i < args.length && !args[i].startsWith("-") ) {
					if( validateCard( args[i] ) ) {
						int r = rankMap.get(args[i].substring(0, args[i].length() - 1) );
						int s = suitMap.get( args[i].substring(args[i].length() - 1) );
						
						try {
							player.addCard( new Card( Card.Rank.values()[r], Card.Suit.values()[s] ) );
						} catch(PokerException e) {
							throw new IllegalArgumentException("Error creating card. Are you sure this is a real card?");
						}//end try-catch
						
						pidx++;
					} else {
						throw new IllegalArgumentException("Hello???? That's not even a real card.");
					}//end if
					i++;
				}//end while

				i--;
			
			} else if ("-d".equals(flag)) {
				i++;

				while (i < args.length && !args[i].startsWith("-") ) {
				
					if( validateCard( args[i] ) ) {
						int r = rankMap.get( args[i].substring(0, args[i].length() - 1) );
						int s = suitMap.get( args[i].substring(args[i].length() - 1) );
						
						try {
							dealer.addCard( new Card( Card.Rank.values()[r], Card.Suit.values()[s] ) );
						} catch(PokerException e) {
							throw new IllegalArgumentException("Error creating card. Are you sure this is a real card?");
						}//end try-catch
						
						didx++;
					} else {
						throw new IllegalArgumentException("Hello???? That's not even a real card.");
					}//end if

					i++;
				}//end while
			
			}//end if
		}//end for

		if(pidx == 0 || didx == 0)
			throw new IllegalArgumentException("Yo.... you gotta specify both the p and d flags.");

		if(pidx > 5)
			throw new IllegalArgumentException("Too many cards specified for Player hand. Exactly 5 expected.");
		else if (didx > 5)
			throw new IllegalArgumentException("Too many card specified for Dealer hand. Exactly 5 expected.");
		else if (pidx != 5 || didx != 5)
			throw new IllegalArgumentException("This is 5 card draw... each hand must have exactly 5 cards.");
	
	}//end parseArguments


	
	/**                                                   
	*      Verifies if the passed card is in an acceptable format
  	*      @param card The string representation of the card 
	*      @return True if string represents a valid card, false otherwise
	*/
	public static boolean validateCard(String card) {

		if (card.length() < 2 || card.length() > 3) {
			return false; 
		}

		String rank = card.substring(0, card.length() - 1);
		String suit = card.substring(card.length() - 1);

		boolean validRank = rankMap.containsKey(rank);
		boolean validSuit = suitMap.containsKey(suit);

		if (!validRank || !validSuit) {
			return false;  // Invalid card rank or suit
		}//end if

		return true; 
	}//end validateCards

}//end CmdLineInput

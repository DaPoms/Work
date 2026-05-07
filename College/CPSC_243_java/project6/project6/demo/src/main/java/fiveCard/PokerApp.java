package fiveCard;
/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  April 28th, 2026                         */
/* Due Date:       May 5th, 2026                            */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #6                                       */
/* Filename:       PokerApp.java                            */
/* Purpose:       Implements full stack of poker            */
/************************************************************/

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.scene.paint.Color;
import javafx.scene.control.Button;
import javafx.scene.shape.Rectangle;
import javafx.geometry.Insets;
import java.util.ArrayList;
import javafx.scene.layout.*;
import javafx.scene.control.TextField;
import javafx.scene.text.*;
import javafx.scene.image.*;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.control.CheckBox;


import fiveCard.PokerHand.HandRank;
import fiveCard.Card.Rank;
import fiveCard.Card.Suit;

public class PokerApp extends Application {

  private enum PokerStates
  {
    BETTING1,
    DISCARD1,
    BETTING2,
    REVEAL
  }
PokerCasinoGame pokerGame; // The backend object
PlayerSpace userSpace;
DealerSpace dealerSpace;
PokerStatsUI betStats;
PokerStatsUI balStat;
CenterBoard cBoard;
BettingRequestUI bettingUI;
StackPane overlay; // Contains all the UI for our poker game (used for adding/removing overlays)
PokerStates pokerState;
  

  //////////// end of old code ////////////

  /**
  * Implements a box with a header + value
  * fiveCard.ValueBoxWithHeader.java
  * CPSC243 Spring 2026
  * @author Daniel Tripoli
  */  
  class ValueBoxWithHeader extends VBox
  {
    Text value;
    /**                                                   
    *      Constructor for a UI element that is a box with header text to describe the value and a body text intended for displaying a value
    *      @param headerStr The text that describes the value
    *      @param startVal The text that represents the value (can be a string, but this object is intended for )
    */
    ValueBoxWithHeader(String headerStr, String startVal)
    {
      value = new Text(startVal);
      value.setFont(Font.font(22));
      value.setStyle("-fx-font-weight: 700;");
      value.setFill(Color.WHITE);
      
      Text header = new Text(headerStr);
      header.setFont(Font.font(18));
      header.setText(headerStr);
      header.setFill(Color.WHITE);
      header.setStyle(value.getStyle());
      getChildren().addAll(header, value);
      setAlignment(Pos.CENTER);
      setBorder(new Border(new BorderStroke(Color.WHITE, BorderStrokeStyle.SOLID, new CornerRadii(15),BorderWidths.DEFAULT)));
      setBackground(new Background(new BackgroundFill(Color.web("#013215"),new CornerRadii(15),Insets.EMPTY)));
      setMinSize(150,110);
      setMaxSize(150,110);
    }

    /**                                                   
    *      Sets the text in the box with a new value
    *      @param val The value the text will be set to (intended to be a 'value' as in number, but strings can be used too)
    */
    public void setValue(String val)
    {
      value.setText(val);
    }
  }


  /**
  * Implements stats displayed for both the player and dealer (or just player based on constructor)
  * fiveCard.PokerStatsUI.java
  * CPSC243 Spring 2026
  * @author Daniel Tripoli
  */
  class PokerStatsUI extends VBox
  {
    ValueBoxWithHeader dealerStatsUI;
    ValueBoxWithHeader playerStatsUI;

    /**                                                   
    *      Alternative constructor that displays stats only for the player
    *      @param statName The name of the stat being displayed
    *      @param playerStatVal The player's starting stat value
    */
    PokerStatsUI(String statName, String playerStatVal) //Player only variant
    {
      playerStatsUI = new ValueBoxWithHeader("Player " + statName, "$" + playerStatVal);
      dealerStatsUI = null;
      setMargin(playerStatsUI, new Insets(638,0,0,0));
      getChildren().addAll(playerStatsUI);

    }

    /**                                                   
    *      Constructor for the stats UI, which are intended to display information about the player and dealer
    *      @param statName The name of the stat being displayed
    *      @param playerStatVal The player's starting stat value
    *      @param dealerStatVal The dealer's starting stat value
    */
    PokerStatsUI(String statName, String playerStatVal, String dealerStatVal)
    {
      dealerStatsUI = new ValueBoxWithHeader("Dealer " + statName,  "$" + dealerStatVal);
      playerStatsUI = new ValueBoxWithHeader("Player " + statName,  "$" + playerStatVal);

      setSpacing(526);

      getChildren().addAll(dealerStatsUI, playerStatsUI);
    }

    /**                                                   
    *      Updates the player text to the passed text (intended for values/stats)
    *      @param playerStat The player's value for the stat that the player's text will be updated to
    */
    public void updatePlayerStat(String stat)
    {
      playerStatsUI.setValue( "$" + stat);
    }

    /**                                                   
    *      Updates the dealer text to the passed text (intended for values/stats)
    *      @param dealerStat The dealer's value for the stat that the dealer's text will be updated to
    */
    public void updateDealerStat(String stat)
    {
      dealerStatsUI.setValue( "$" + stat);
    }

    /**                                                   
    *      Updates both the player and dealer text to the passed text (intended for values/stats)
    *      @param dealerStat The dealer's value for the stat that the dealer's text will be updated to
    *      @param playerStat The player's value for the stat that the dealer's text will be updated to
    */
    public void updatePlayerAndDealerStats(String dealerStat, String playerStat)
    {
      dealerStatsUI.setValue( "$" + dealerStat);
       playerStatsUI.setValue( "$" + playerStat);
    }
  }

  /**                                                   
  *      Copies the passed test to a hard copy, mainly used to copy the style of the text
  *      @param t The text to be 'cloned'
  *      @return The copy of the text
  */
  public Text cloneText(Text t)
  {
    Text result = new Text(t.getText());
    result.setFont(t.getFont());
    result.setFill(t.getFill());
    result.setStyle(t.getStyle());
    return result;
  }

  /**
  * Implements a player card UI, which is a poker card paired with a checkbox for discards
  * fiveCard.PlayerCardUI.java
  * CPSC243 Spring 2026
  * @author Daniel Tripoli
  */
  class PlayerCardUI extends VBox
  {
    private PokerCardUI card;
    private CheckBox setForHold;
    /**                                                   
    *      Constructor for the UI of a single card for a player. Comprised of the card itself and a check box for selecting if the card is held or not for discarding
    *      @param r The rank of the card that is added
    */
    public PlayerCardUI(Rank r, Suit s)
    {
      card = new PokerCardUI(r,s);
      setForHold = new CheckBox("Hold");
      getChildren().addAll(card, setForHold);
      setSpacing(10);
      setPadding(new Insets(0,0,10,0));
      setForHold.setFont(Font.font("Arial",FontWeight.BOLD, 15)); //"system" just uses the systems default font (used just because I dislike css and this works around it)
      setForHold.setTextFill(Color.WHITE);
      setForHold.setPrefSize(80, 20);
      setAlignment(Pos.CENTER);
    }

    /**                                                   
    *      Returns if the card has been selected to be held (as in not discarded in discard phase)
    *      @return True if checkbox is checked, false otherwise.
    */
    public boolean isSetForHold() // This will be used for project 6 (put it here before I forget)
    {
      return setForHold.isSelected();
    }

    /**                                                   
    *      Reveals the front card UI (permanently removes the back of the card)
    */
    public void revealCard()
    {
      card.revealCard(); // This is required as java does not have multi-inheritance for classes
    }

    /**                                                   
    *      Returns a reference to the card's checkbox, for use in event handling
    *      @return A refrence to the check box associated with the card
    */
    public CheckBox getCheckBox()
    {
      return setForHold;
    }

  }

  /**
  * Implements a generalized poker card UI
  * fiveCard.PokerCardUI.java
  * CPSC243 Spring 2026
  * @author Daniel Tripoli
  */
  class PokerCardUI extends StackPane
  {
    protected Text suitSymbol;
    protected Node rankSymbol;
    protected StackPane backOfCard;
    /**                                                   
    *      Constructor for poker card UI. Follows the visuals of a standard deck
    *      @param cardRank The rank of the card that gets put on the card UI. Rank is shown in the upper left and lower right of the card, with face cards showing additionally through an image in the center
    *      @param cardSuit The suit of the card that gets put on the card UI. Suit is shown in the upper left and lower right for face cards and in the center for all numbered cards
    */
    public PokerCardUI(Rank cardRank, Suit cardSuit)
    {
      Rectangle backOfCardRim = createCardShape(); // This is to hide the front of the card while still allowing us to have BEAUTIFUL CURVES on the back
      Rectangle cardShape = createCardShape();
      setMinSize(cardShape.getWidth(), cardShape.getHeight());
      setMaxSize(cardShape.getWidth(), cardShape.getHeight()); // Forces ending card to be the size of the 
      ImageView backOfCardImg = new ImageView("file:C:/Users/Daniel Worktop/VsProjects/Work/College/CPSC_243_java/project6/project6/demo/src/main/java/fiveCard/assets/card_back.png");
      backOfCardImg.setFitHeight(185);
      backOfCardImg.setFitWidth(130);
      backOfCard = new StackPane(backOfCardRim, backOfCardImg);

      switch(cardSuit.stringifiedSuit )
      {
        case("S"): {suitSymbol = new Text("♠"); break;}
        case("H"): {suitSymbol = new Text("♥"); break;}
        case("D"): {suitSymbol = new Text("♦"); break;}
        case("C"): {suitSymbol = new Text("♣"); break;}
      }; 
      rankSymbol = new Text(cardRank.stringifiedRank); // Either text or an image (for J,Q,K)
      suitSymbol.setFont(Font.font(100));

      switch(cardRank.stringifiedRank)
      {
        case("J"): {rankSymbol = new ImageView("file:C:/Users/Daniel Worktop/VsProjects/Work/College/CPSC_243_java/project6/project6/demo/src/main/java/fiveCard/assets/jack.png"); break;} //image variants
        case("Q"): {rankSymbol = new ImageView("file:C:/Users/Daniel Worktop/VsProjects/Work/College/CPSC_243_java/project6/project6/demo/src/main/java/fiveCard/assets/queen.png"); break;}
        case("K"): {rankSymbol = new ImageView("file:C:/Users/Daniel Worktop/VsProjects/Work/College/CPSC_243_java/project6/project6/demo/src/main/java/fiveCard/assets/king.png"); break;}
        default  : {((Text)rankSymbol).setFont(Font.font(35)); break;}
      }; 

      StackPane.setAlignment(rankSymbol, Pos.BOTTOM_RIGHT); //This is weird syntax to me...
      getChildren().addAll(cardShape, rankSymbol, suitSymbol);
      setMaxSize(cardShape.getWidth(), cardShape.getHeight());
      

      if(rankSymbol instanceof ImageView) // Case of J, Q, K
      {
        ((ImageView) rankSymbol).setFitHeight(135);
        ((ImageView) rankSymbol).setPreserveRatio(true);
        StackPane.setAlignment(suitSymbol, Pos.BOTTOM_RIGHT); 
        suitSymbol.setFont(Font.font(25));
        
        StackPane.setAlignment(rankSymbol, Pos.CENTER); 
        

        Text upperLeftSuit = cloneText(suitSymbol);
        StackPane.setAlignment(upperLeftSuit, Pos.TOP_LEFT);

        Text upperLeftRank = cloneText(suitSymbol); // Just take advantage of clone to carry over 'css' (just using .set's) formatting
        upperLeftRank.setText(cardRank.stringifiedRank); //Have to overwrite the cloned text's value
        Text lowerRightRank = cloneText(upperLeftRank);
        lowerRightRank.setText(cardRank.stringifiedRank); //Have to overwrite the cloned text's value
        StackPane.setAlignment(upperLeftRank, Pos.TOP_LEFT);
        StackPane.setAlignment(lowerRightRank, Pos.BOTTOM_RIGHT);

        StackPane.setMargin(suitSymbol, new Insets(0,3,28,0));
        StackPane.setMargin(upperLeftSuit, new Insets(28,0,0,0));
        if(cardRank == Rank.JACK) // Formatting looked ugly on Jack but great on king queen, so this is custom for jack
        {
          StackPane.setMargin(upperLeftRank, new Insets(0,0,0,10));
          StackPane.setMargin(lowerRightRank, new Insets(0,10,5,0));
        }
        else
        {
          StackPane.setMargin(upperLeftRank, new Insets(0,0,0,3));
          StackPane.setMargin(lowerRightRank, new Insets(0,6,0,0));
        }
        getChildren().addAll(upperLeftRank, lowerRightRank, upperLeftSuit);
      }
      else
      {
        StackPane.setAlignment(rankSymbol, Pos.BOTTOM_RIGHT); 
        ((Text) rankSymbol).setFont(Font.font(35));
        StackPane.setMargin(rankSymbol, new Insets(155,8,0,0));

        Text upperLeftRank = cloneText((Text)rankSymbol);
        StackPane.setAlignment(upperLeftRank, Pos.TOP_LEFT);
        StackPane.setMargin(upperLeftRank, new Insets(0,0,155,8));
        getChildren().add(upperLeftRank);
      }
      getChildren().add(backOfCard); // freshly instantiated cards are hidden (ensures no peeking!)
    }  
    
  /**                                                   
  *      Reveals the front of the card
  */
    public void revealCard()
    {
      getChildren().remove(backOfCard);
    }
  }

  /**                                                   
  *      C
  *      @param 
  */
  public Rectangle createCardShape()
  {
    Rectangle cardShape = new Rectangle(140,195);
    cardShape.setArcHeight(15);
    cardShape.setArcWidth(15);
    cardShape.setStyle("-fx-fill: white;");
    return cardShape;
  }

  /**
  * Implements Implements the player hand UI
  * fiveCard.PlayerHandUI.java
  * CPSC243 Spring 2026
  * @author Daniel Tripoli
  */
  //For player hand (only difference between using createHand() on its own and playerHand class is playerHand has a checkbox for discarding)
  class PlayerHandUI extends HBox
  {
    /**                                                   
    *      Constructor for the player's card hand. Includes cards with checkboxes underneath for holding cards (preventing them from being discarded)
    *      @param cards The player's cards that will be turned into their hand
    */
    PlayerHandUI(ArrayList<Card> cards)
    {
      for(int i = 0; i < cards.size(); i++)
      {
        Card card = cards.get(i); // this is just the value of the card
        PlayerCardUI c = new PlayerCardUI(card.getRank(), card.getSuit()); // This is the actual card
        c.revealCard();
        getChildren().add(c); // This should be adding from left to right (so that getChildren()'s array at index 0 should bet he 1st card')
      }
      setSpacing(30);
    }
    /**                                                   
    *      Returns all the checkboxes of the player hand, to be used for checking each box's state
    *      @return Contains references to all the checkboxes, from left to right (index 0 = leftmost card)
    */
    public ArrayList<CheckBox> retrieveCheckBoxes()
    {
      ArrayList<CheckBox> ans = new ArrayList<>();
      for(Node c : getChildren())
        ans.add(((PlayerCardUI) c).getCheckBox());
      return ans;
    }
  }

  /**                                                   
  *      Creates hand UI given a value based card representation of the cards 
  *      @param cards The set of cards that get turned into their UI form
  *      @return The UI for the hand of cards
  */
  public HBox createHand(ArrayList<Card> cards) 
  {
    HBox cardGUI = new HBox();
    for(int i = 0; i < cards.size(); i++)
    {
      Card card = cards.get(i);
      PokerCardUI c = new PokerCardUI(card.getRank(), card.getSuit());
      cardGUI.getChildren().add(c);
    }
    cardGUI.setSpacing(30);
    return cardGUI;
  }

  /**
   * Implements the player's UI
   * fiveCard.pokerButton.java
   * CPSC243 Spring 2026
   * @author Daniel Tripoli
   */
  class PokerButton extends Button
  { // This class is just used for neater to read code
     /**                                                   
    *      Constructor for a single button box, styled to the poker game UI
    *      @param text The text of the button (inside of the button)
    *      @param color The color of the button
    *      @param length The length of the button box
    *      @param height The height of the button box
    */
    PokerButton(String text, String color, int length, int height)
    {
      setText(text);
      setStyle("-fx-background-color:" + color +"; -fx-font-weight: 700; -fx-text-fill: white;" +
               "-fx-font-size: 25; -fx-border-radius: 10; -fx-background-radius: 13;" + 
               "-fx-border-color: #c6e2c4; -fx-border-width: 1.5;");
      setPrefSize(200, 60);
    }
    //No setters included here as buttons "should" be static in terms of their text + visuals
  }

   /**
   * Implements user interaction buttons for poker (call, raise, fold, end)
   * fiveCard.PokerTurnDecisions.java
   * CPSC243 Spring 2026
   * @author Daniel Tripoli
   */
  class PokerTurnDecisions extends HBox
  {
    private PokerButton callButton; 
    private PokerButton raiseButton;
    private PokerButton foldButton;
    private PokerButton endRoundButton;
    /**                                                   
    *      Constructor for the poker turn decisions. Contains buttons for calling, raising, folding, and ending a round (used to confirm discards and bet decisions)
    */
    PokerTurnDecisions()
    {

      callButton = new PokerButton("Call", "#1b597e", 200, 60);
      raiseButton = new PokerButton("Raise", "#147530", 200, 60);
      foldButton = new PokerButton("Fold", "#926f07", 200, 60);
      endRoundButton = new PokerButton("End round", "#a2261e", 200, 60);
      getChildren().addAll(callButton, raiseButton, foldButton, endRoundButton);
      setAlignment(Pos.CENTER);
      setSpacing(40);
      setPadding(new Insets(0,0,20,0));
      
    }
    //All these getters are used to be referenced for event handling
    /**                                                   
    *      Returns a reference to the call button, mainly for event handling
    *      @return A reference to the call button
    */
    public PokerButton getCallButton() {return callButton;}
    /**                                                   
    *      Returns a reference to the raise button, mainly for event handling
    *      @return A reference to the raise button
    */
    public PokerButton getRaiseButtion() {return raiseButton;}
    /**                                                   
    *      Returns a reference to the fold button, mainly for event handling
    *      @return A reference to the fold button
    */
    public PokerButton getFoldButton() {return foldButton;}
    /**                                                   
    *      Returns a reference to the end round button, mainly for event handling
    *      @return A reference to the end round button
    */
    public PokerButton getEndRoundButton() {return endRoundButton;}
  }

  /**
   * Implements the player's UI
   * fiveCard.PlayerSpace.java
   * CPSC243 Spring 2026
   * @author Daniel Tripoli
   */
  class PlayerSpace extends VBox
  {
    private PlayerHandUI cards; // I will likely need to add a method to collect view all the checkBoxes of cards in order to check if they are checked or not, but project 5 doesn't require that
    private Label playerHeader;
    private PokerTurnDecisions userControls; //Will be used for more organized event handling

    /**                                                   
    *      Constructor for the player space. Contains the user's buttons for making round decisions, the players hand, and text above the hand to display the rank
    *      @param hand The hand the player's hand UI will display
    */
    PlayerSpace(PokerHand hand)
    {
      ArrayList<Card> handArr = hand.getHand();
      userControls = new PokerTurnDecisions();
      cards = new PlayerHandUI(handArr);
      cards.setPadding(new Insets(0,0,5,0));
      cards.setAlignment(Pos.CENTER);
      playerHeader = new Label("Player Hand: PLACEHOLDER"); // rank will be placed in placeholder
      playerHeader.setFont(Font.font(25));
      playerHeader.setStyle("-fx-font-weight: 700");
      playerHeader.setTextFill(Color.WHITE);
      setSpacing(10);
      getChildren().addAll(playerHeader, cards, userControls);
      setAlignment(Pos.CENTER);
    }

    /**                                                   
    *      Updates the text above the dealer space which contains that current rank of the hand (should start empty at the start of poker to hide the result from the player)
    *      @param r The hand rank that the header will display
    */
    public void setDisplayedRank(HandRank r)
    {
      playerHeader.setText("Player Hand: " + HandRank.toString(r));
    }

    /**                                                   
    *      Replaces the player's current hand with a new one
    *      @param hand The hand the player's hand UI will be replaced with
    */
    public void updateHand(ArrayList<Card> hand)
    {
      cards.getChildren().clear(); //Empties cards in HBox
      cards.getChildren().addAll(new PlayerHandUI(hand).getChildren()); // Populates hand with new cards
    }

    /**                                                   
    *      Returns an array corresponding to which buttons are set to be held and which are to be discarded.
    *      @param Array Contains Which cards set to be held. True = held, false = discarded
    */
    public ArrayList<Boolean> determineChecked() // Ok... I worked ahead
    {
      ArrayList<Boolean> ans = new ArrayList<>(cards.getChildren().size());
      ArrayList<CheckBox> checkBoxes = cards.retrieveCheckBoxes();
      for(int i = 0; i < checkBoxes.size(); i++)
      {
        if((checkBoxes.get(i)).isSelected())
          ans.set(i, true);
      }
      return ans;
    }
  
    /**                                                   
    *      Returns a reference to the call button, mainly for event handling
    *      @return A reference to the call button 
    */
    public PokerButton getCallButton() {return userControls.getCallButton();}
    /**                                                   
    *      Returns a reference to the raise button, mainly for event handling
    *      @return A reference to the raise button
    */
    public PokerButton getRaiseButtion() {return userControls.getRaiseButtion();}
    /**                                                   
    *      Returns a reference to the fold button, mainly for event handling
    *      @return A reference to the fold button
    */
    public PokerButton getFoldButton() {return userControls.getFoldButton();}
    /**                                                   
    *      Returns a reference to the end round button, mainly for event handling
    *      @return A reference to the end round button
    */
    public PokerButton getEndRoundButton() {return userControls.getEndRoundButton();} //Once again, used for (albeit ugly) event handling in the future. Something like PlayerSpace.getRaiseButton()

  }

  /**
   * Implements the dealer's UI
   * fiveCard.DealerSpace.java
   * CPSC243 Spring 2026
   * @author Daniel Tripoli
   */
  class DealerSpace extends VBox
  {
    private HBox cards;
    private Label dealerHeader;

    /**                                                   
    *      Constructor for the dealer space, which contains the hand rank display + cards
    *      @param hand The starting hand that gets displayed
    */
    DealerSpace(PokerHand hand)
    {
      ArrayList<Card> handArr = hand.getHand();
      cards = createHand(handArr);
      cards.setAlignment(Pos.CENTER);
      dealerHeader = new Label("Dealer Hand: PLACEHOLDER"); // For dealer, hand wont be shown at the start, but this is just for demonstration purposes
      dealerHeader.setFont(Font.font(25));
      dealerHeader.setStyle("-fx-font-weight: 700");
      dealerHeader.setTextFill(Color.WHITE);
      setSpacing(10);
      getChildren().addAll(dealerHeader, cards);
      setAlignment(Pos.CENTER);
      
    }

    /**                                                   
    *      Updates the text above the dealer space which contains that current rank of the hand (should start empty at the start of poker to hide the result from the player)
    *      @param r The hand rank that the header will display
    */
     public void setDisplayedRank(HandRank r)
    {
      dealerHeader.setText("Dealer Hand: " + HandRank.toString(r));
    }


    /**                                                   
    *      Replaces the current cards displayed with a new set of cards
    *      @param hand The array of cards, which is the structure to represent a card hand
    */
    public void updateHand(ArrayList<Card> hand)
    {
       cards.getChildren().clear(); //Empties cards in HBox
      cards.getChildren().addAll(createHand(hand).getChildren()); // Populates hand with new cards
    }

    /**                                                   
    * Reveals the front of all cards in the dealer's hand      
    */
    public void revealCards()
    {
      for(Node c : cards.getChildren())
        ((PokerCardUI) c).revealCard();
    }
  }

  /**
  * Implements the UI for the message board, used to display messages to the user
  * fiveCard.MessageBoard.java
  * CPSC243 Spring 2026
  * @author Daniel Tripoli
  */
  class MessageBoard extends VBox
  {
    private Text textBody;
    private Text header;
    /**                                                   
    *      Constructor for the message board, initializes a box with a top title/header, and updateable text below
    *      @param msg The text to display for the message board
    */
    MessageBoard(String title, String msg)
    {
      header = new Text(title); //learned of text type to get around using CSS
      header.setFill(Color.WHITE);
      header.setFont(Font.font(25));
      textBody = new Text(msg);
      textBody.setFill(Color.LIGHTYELLOW);
      textBody.setFont(Font.font(20));
      setPadding(new Insets(0,0,10,0));
      getChildren().addAll(header, textBody);
      setAlignment(Pos.CENTER);
      setStyle("-fx-border-color: #c6e2c4; -fx-background-color: #012f12; -fx-border-radius: 20; -fx-background-radius:20");
      setMaxSize(800, 100);
    }

    /**                                                   
    *      Updates the message displayed on the message board
    *      @param s 
    */
    public void setMessage(String s)
    {
      textBody.setText(s);
    }

        /**                                                   
    *      Updates the title displayed on the message board
    *      @param s 
    */
    public void setHeader(String s)
    {
      header.setText(s);
    }
    
  }

  /**
   * Implements a box that contains text below it, and an image above
   * fiveCard.pokerTextWithImage.java
   * CPSC243 Spring 2026
   * @author Daniel Tripoli
   */
  class pokerTextWithImage extends VBox
  {
    private Text text;

    /**                                                   
    *      Constructor for pokerTextWithImage. Creates a box with an image above and text below the image.
    *      @param strText The text to display below the image
    *      @param fontSize The size of the text displayed below the image 
    *      @param imgHeight The height of the image 
    *      @param boxwidth The width of the box that contains the image + text
    *      @param boxHeight The height of the box that contains the image + text
    */
    pokerTextWithImage(String strText, int fontSize, String imagePath, int imgHeight, int boxWidth, int boxHeight) // Image is static. Make sure path uses / not \
    {
      ImageView img = new ImageView("file:" + imagePath); // This is a better alternative to the image constructor variant
      img.setFitHeight(imgHeight);
      img.setPreserveRatio(true);
      text = new Text(strText);
      text.setFont(Font.font(fontSize));
      text.setStyle("-fx-font-weight: 700");
      text.setFill(Color.WHITE);
      getChildren().addAll(img, text);
      setAlignment(Pos.CENTER);
      setStyle("-fx-border-color: #c6e2c4; -fx-border-radius: 20;");
      setMaxSize(boxWidth, boxHeight);
    }

    public void setText(String strText) // This is just to avoid having to do .text.setText()
    {
      text.setText(strText);
    }
  }

  /**                                                   
  *      Creates a label header stylzed to match our poker game (just for more compact code).
  *      @param startingVal The starting value of the pot
  */
  public Label createPokerHeader(String msg, int fontSize)
  {
    Label result = new Label(msg);
    result.setFont(Font.font(fontSize));
    result.setStyle("-fx-font-weight: 700");
    result.setTextFill(Color.WHITE);
    return result;
  }

  /**
  * Implements the UI for the betting pot
  * fiveCard.PotPool.java
  * CPSC243 Spring 2026
  * @author Daniel Tripoli
  */
  class PotPool extends VBox
  {
    private pokerTextWithImage pot;

    /**                                                   
    *      Constructor for the PotPool, initializes the betting pot UI
    *      @param startingVal The starting value of the pot
    */
    public PotPool(Double startingVal)
    {
      Label potHeader = createPokerHeader("Pot", 25);
      pot = new pokerTextWithImage("$" + Double.toString(startingVal), 25, "C:/Users/Daniel Worktop/VsProjects/Work/College/CPSC_243_java/project6/project6/demo/src/main/java/fiveCard/assets/pot.png", 130, 200, 150);
      pot.setPadding(new Insets(20,80,10,80));
      getChildren().addAll(potHeader, pot);
      setAlignment(Pos.CENTER);
    }

    /**                                                   
    *      Updates the betting pot UI's value that is displayed.
    *      @param d The starting value of the pot
    */
    public void updateVal(Double d)
    {
      pot.setText("$" + Double.toString(d));
    }
  }

   /**
   * Implements the center UI of the poker game (displays messages + betting pot)
   * fiveCard.CenterBoard.java
   * CPSC243 Spring 2026
   * @author Daniel Tripoli
   */
  class CenterBoard extends VBox
  {
    private MessageBoard msgBoard;
    private PotPool pot;
    /**                                                   
    *      Constructor for the centerUI, initializes the betting pot UI and the message board.
    *      @param startingPot The starting value of the pot
    *      @param startingMsg The starting message of the message board
    */
    CenterBoard(Double startingPot, String msgTitle, String startingMsg)
    {
      pot = new PotPool(startingPot);
      msgBoard = new MessageBoard(msgTitle, startingMsg);
      getChildren().addAll(pot, msgBoard);
      setAlignment(Pos.CENTER);
      setSpacing(15);
      setPadding(new Insets(0,0,15,0));
    }

    /**                                                   
    *      Updates the message displayed on the message UI
    *      @param s The message that will be updated
    */
    public void updateMsg(String s)
    {
      msgBoard.setMessage(s);
    }

    /**                                                   
    *      Updates the value displayed on the pot UI
    *      @param d The double value the pot will be updated to
    */
    public void updatePot(double d)
    {
      pot.updateVal(d);
    }
  }

  /**
   * Implements the betting UI and it's associated behaviors
   * fiveCard.BettingRequestUI.java
   * CPSC243 Spring 2026
   * @author Daniel Tripoli
   */
  class BettingRequestUI extends VBox // This will normally show if user raises in the betting phase
  {
    private TextField userInputBox;
    private Button submitButton;
    BettingRequestUI() // will likely have better messages in the next project (like amount that must be betted)
    {
      Text header = new Text("Enter your bet:");
      header.setFont(Font.font(25));
      header.setStyle("-fx-font-weight: 700;");
      header.setFill(Color.WHITE);
      userInputBox = new TextField();
      userInputBox.setBackground(new Background(new BackgroundFill(Color.web("#186336"),new CornerRadii(15),Insets.EMPTY)));
      userInputBox.setFont(Font.font(25));
      userInputBox.setStyle("-fx-");
      userInputBox.setMaxWidth(200);
      userInputBox.setAlignment(Pos.CENTER);
      userInputBox.setStyle("-fx-text-fill: white;");
      userInputBox.setBorder(new Border(new BorderStroke(Color.WHITE, BorderStrokeStyle.SOLID, new CornerRadii(15),BorderWidths.DEFAULT)));
      submitButton = new Button("Submit");
      VBox.setMargin(userInputBox, new Insets(20,0,20,0));

      setMaxSize(600, 200);
      setAlignment(Pos.CENTER);
      setBorder(new Border(new BorderStroke(Color.WHITE, BorderStrokeStyle.SOLID, new CornerRadii(15),BorderWidths.DEFAULT)));
      setBackground(new Background(new BackgroundFill(Color.web("#013215"),new CornerRadii(15),Insets.EMPTY)));
      getChildren().addAll(header, userInputBox, submitButton);
    }
    public double getBet() {return Double.parseDouble(userInputBox.getText());}
    public Button getSubmitButton() {return submitButton;}
  }



  public void createPokerEventHandlingSuite()
  {
    PokerButton callButton = userSpace.getCallButton();
    PokerButton raiseButton = userSpace.getRaiseButtion();
    PokerButton foldButton = userSpace.getFoldButton();
    callButton.setOnAction(e -> {
        if(pokerState == PokerStates.BETTING1)
          try{
            pokerGame.call(true);
            betStats.updatePlayerAndDealerStats(pokerGame.getWagerAsString(), pokerGame.getWagerAsString());
            pokerState = PokerStates.DISCARD1;
          }
          catch(PokerException err) {cBoard.updateMsg(err.getMessage());} // TODO MUST ACCOUNT FOR ERROR CASES
    });
    
    raiseButton.setOnAction(e -> {
        if(pokerState == PokerStates.BETTING1 || pokerState == PokerStates.BETTING2)
        {
          displayBetUI();
            bettingUI.getSubmitButton().setOnAction(e2 -> {
              try{
              double bet = bettingUI.getBet();
              pokerGame.raise(bet);
              betStats.updatePlayerAndDealerStats(pokerGame.getWagerAsString(), pokerGame.getWagerAsString());
              pokerState = PokerStates.DISCARD1;
              hideBetUI();
            } catch(PokerException err) {} // TODO INSERT ERROR MESSAGE ON BETTING SCREEN Case of non double value being entered
            });
        }
   // TODO MUST ACCOUNT FOR ERROR CASES
    });
    foldButton.setOnAction(null);
  }


  @Override 
  public void init() // runs before start (good for elements that require backend first on startup)
  {
    try{
      pokerGame = new PokerCasinoGame(1000.0);
    } catch(PokerException e) {System.out.println("Reshufflecount was not within bounds."); System.exit(1);}
    pokerGame.draw();
  }


  @Override
  public void start(Stage primaryStage) {
    BorderPane pokerScreen = new BorderPane(); 
    userSpace   = new PlayerSpace(pokerGame.getPlayerHand());
    userSpace.setDisplayedRank(pokerGame.getPlayerHand().getHandRank());
    dealerSpace = new DealerSpace(pokerGame.getDealerHand());
    betStats    = new PokerStatsUI("Bet", pokerGame.getWagerAsString(), pokerGame.getWagerAsString());
    balStat     = new PokerStatsUI("Bal", pokerGame.getBalanceAsString()); 
    cBoard      = new CenterBoard(0.0, "Bet Phase", "Select call, raise, or fold to decide on your bet");
    bettingUI   = new BettingRequestUI(); // Hidden at the start
    overlay     = new StackPane(pokerScreen); // Use this version to hide the betting popup UI
    pokerState = PokerStates.BETTING1;
    VBox coreGameUI = new VBox(dealerSpace, cBoard, userSpace); //Outer most UI elements do not need to be accessed
    createPokerEventHandlingSuite();

    pokerScreen.setStyle("-fx-background-size: cover;-fx-background-image:url('file:project6/demo/src/main/java/fiveCard/assets/greenboard.jpg')");
    betStats.setPadding(new Insets(43,40,0,0));
    balStat.setPadding(new Insets(38,0,0,40));
    coreGameUI.setPadding(new Insets(0,0,20,0));

    pokerScreen.setCenter(coreGameUI);    
    pokerScreen.setRight(betStats);
    pokerScreen.setLeft(balStat);
    
    Scene scene = new Scene(overlay, 1280, 960);
    primaryStage.setScene(scene);      //Place the scene in the stage
    primaryStage.show();               //Display the stage    
  }//end start

  public void displayBetUI()
  {
    overlay.getChildren().add(bettingUI);
  }

    public void hideBetUI()
  {
    overlay.getChildren().remove(bettingUI);
  }

  public static void main(String[] args)
  {  
    launch(args);
  }
    
}//end MyFirstGUI


//TODO : Make sure to be updating the displayed hand rank as hands change

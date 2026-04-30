package com.example;
/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  April 28th, 2026                         */
/* Due Date:       May 5th, 2026                            */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #5                                       */
/* Filename:       PokerApp.java                            */
/* Purpose:       Implement static version of UI for poker  */
/************************************************************/

import javafx.application.Application;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.scene.paint.Color;
import javafx.scene.control.Button;
import javafx.scene.control.ContentDisplay;
import javafx.scene.shape.Rectangle;
import javafx.geometry.Bounds;
import javafx.geometry.Insets;
import java.util.ArrayList;

import com.example.PokerApp.HandRank;
import com.example.PokerApp.PlayerSpace;
import com.example.PokerApp.Rank;
import com.example.PokerApp.Suit;

import javafx.scene.layout.*;
import javafx.scene.control.TextField;
import javafx.scene.text.*;
import javafx.scene.image.*;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.control.CheckBox;


public class PokerApp extends Application {

  // THIS WILL BE FROM CARD FILE IN MY FINAL PROJECT, this is just for ease of usage

///////////////////////////Project 4 code ///////////////////////////
    enum HandRank 
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
        ROYAL_FLUSH;//9


        public static String toString(HandRank h) // THIS IS THE ONLY NEW CODE I MADE to get project 4 code working for this implementation of frontend
        { //Uses the name of the enum to format a string variant
          String strRank = h.name();
          String lower = strRank.toLowerCase().replace("_", " ");
          String ans = lower.substring(0,1).toUpperCase() + lower.substring(1); 
          
          return ans; 
        }
    }

      /**
     * Enum that represents a card's suit
     */
    enum Suit 
    { 
        CLUBS("C"), 
        DIAMONDS("D"), 
        HEARTS("H"), 
        SPADES("S");
        public final String stringifiedSuit;
        Suit(String passedSuitString)
        {
            stringifiedSuit = passedSuitString;
        }
    }
    enum Rank  
    { 
        TWO("2"), //0
        THREE("3"),  //1
        FOUR("4"), //2
        FIVE("5"), //3
        SIX("6"),  //4
        SEVEN("7"), //5
        EIGHT("8"), //6
        NINE("9"), //7
        TEN("10"), //8
        JACK("J"), //9
        QUEEN("Q"), //10
        KING("K"), //11
        ACE("A"); //12
        public final String stringifiedRank;
        /**
         * Sets a rank to its string representation
         * @param passedRankString The string representation of the rank enum
         */
        Rank(String passedRankString)
        {
            stringifiedRank = passedRankString;
        }
    }
class Card {
    /**
    * Enum that represents card rank
    */
  
    private Rank rank;
    private Suit suit;



  /**                                                   
  *     Constructor for the card class
  *     @param passedRank The rank that the card will be assigned to
  *     @param passedSuit The suit that the card will be assigned to
  */
  Card(Rank passedRank, Suit passedSuit) 
  {
    rank = passedRank;
    suit = passedSuit;
  }


  /**                                                   
  *     Returns the suit of the card
  *     @return The suit of the card object
  */
  Suit getSuit(){return suit;}


  /**                                                   
  *     Returns the value of the card based on the card's rank
  *     @return The score of the card
  */
  int getValue() // we do not need to specify scope due to package-private being the exact scope we need
  { 
      return rank.ordinal();
  }

  /**                                                   
  *     Returns the rank of the card
  *     @return The rank of the card
  */
  Rank getRank(){return rank;}

  /**                                                   
  *     Constructs a string representation of the card, with the first 1-2 chars of the string being the rank, 
  *     and the last char being the rank
  *     @return The string representation of the card
  */
  public String toString()
  {
    return rank.stringifiedRank + suit.stringifiedSuit;
  }
  
}//end Card


  //////////// end of old code //////////// "💵"

  class ValueBoxWithHeader extends VBox
  {
    Text value;
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

    public void setValue(String val)
    {
      value.setText(val);
    }
  }

  class PokerStatsUI extends VBox
  {
    ValueBoxWithHeader dealerStatsUI;
    ValueBoxWithHeader playerStatsUI;

    PokerStatsUI(String statName, String playerStatVal) //Player only variant
    {
      playerStatsUI = new ValueBoxWithHeader("Player " + statName, playerStatVal);
      dealerStatsUI = null;
      setMargin(playerStatsUI, new Insets(648,0,0,0));
      getChildren().addAll(playerStatsUI);

    }

    PokerStatsUI(String statName, String playerStatVal, String dealerStatVal)
    {
      dealerStatsUI = new ValueBoxWithHeader("Dealer " + statName, dealerStatVal);
      playerStatsUI = new ValueBoxWithHeader("Player " + statName, playerStatVal);

      setSpacing(538);

      getChildren().addAll(dealerStatsUI, playerStatsUI);
    }

    public void updatePlayerStat(String stat)
    {
      playerStatsUI.setValue(stat);
    }

    public void updateDealerStat(String stat)
    {
      dealerStatsUI.setValue(stat);
    }

    public void updatePlayerAndDealerStats(String dealerStat, String playerStat)
    {
      dealerStatsUI.setValue(dealerStat);
       playerStatsUI.setValue(playerStat);
    }

    
      
  }

  public Text cloneText(Text t)
  {
    Text result = new Text(t.getText());
    result.setFont(t.getFont());
    result.setFill(t.getFill());
    result.setStyle(t.getStyle());
    return result;
  }

  class PlayerCardUI extends VBox
  {
    private PokerCardUI card;
    private CheckBox setForDiscard;
    public PlayerCardUI(Rank r, Suit s)
    {
      card = new PokerCardUI(r,s);
      setForDiscard = new CheckBox("Hold");
      //setAlignment(Pos.CENTER);
      getChildren().addAll(card, setForDiscard);
      setSpacing(10);
      setPadding(new Insets(0,0,10,0));
      setForDiscard.setFont(Font.font("System",FontWeight.BOLD, 15)); //"system" just uses the systems default font (used just because I dislike css and this works around it)
      setForDiscard.setTextFill(Color.WHITE);
      setForDiscard.setPrefSize(80, 20);
      setAlignment(Pos.CENTER);
    }

    public boolean isSetForDiscard() // This will be used for project 6 (put it here before I forget)
    {
      return setForDiscard.isSelected();
    }

    public void revealCard()
    {
      card.revealCard();
    }

    public CheckBox getCheckBox()
    {
      return setForDiscard;
    }

  }



  class PokerCardUI extends StackPane
  {
    protected Text suitSymbol;
    protected Node rankSymbol;
    protected StackPane backOfCard;
    public PokerCardUI(Rank cardRank, Suit cardSuit)
    {
      Rectangle backOfCardRim = createCardShape(); // This is to hide the front of the card while still allowing us to have BEAUTIFUL CURVES on the back
      Rectangle cardShape = createCardShape();
      setMinSize(cardShape.getWidth(), cardShape.getHeight());
      setMaxSize(cardShape.getWidth(), cardShape.getHeight()); // Forces ending card to be the size of the 
      ImageView backOfCardImg = new ImageView("file:project5/demo/src/main/java/com/example/assets/card_back.png");
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
        case("J"): {rankSymbol = new ImageView("file:project5/demo/src/main/java/com/example/assets/jack.png"); break;} //image variants
        case("Q"): {rankSymbol = new ImageView("file:project5/demo/src/main/java/com/example/assets/queen.png"); break;}
        case("K"): {rankSymbol = new ImageView("file:project5/demo/src/main/java/com/example/assets/king.png"); break;}
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
        suitSymbol.setFont(Font.font(35));
        
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
        StackPane.setMargin(upperLeftSuit, new Insets(28,0,0,3));
        if(cardRank == Rank.JACK) // Formatting looked ugly on Jack but great on king queen, so this is custom for jack
        {
          StackPane.setMargin(upperLeftRank, new Insets(0,0,0,8));
          StackPane.setMargin(lowerRightRank, new Insets(0,8,0,0));
        }
        else
        {
          StackPane.setMargin(upperLeftRank, new Insets(0,0,0,3));
          StackPane.setMargin(lowerRightRank, new Insets(0,3,0,0));
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
    
    public void revealCard()
    {
      getChildren().remove(backOfCard);
    }
  }

  public Rectangle createCardShape()
  {
    Rectangle cardShape = new Rectangle(140,195);
    cardShape.setArcHeight(15);
    cardShape.setArcWidth(15);
    cardShape.setStyle("-fx-fill: white;");
    StackPane card = new StackPane(cardShape); // Use getChildren.add() to insert to pane
    return cardShape;
  }

  //For player hand (only difference between hand and playerHand is hand has a checkbox for discarding)
  class PlayerHandUI extends HBox
  {
    PlayerHandUI(ArrayList<Card> cards)
    {
      for(int i = 0; i < cards.size(); i++)
      {
        Card card = cards.get(i); // this is just the value of the card
        PlayerCardUI c = new PlayerCardUI(card.getRank(), card.getSuit()); // This is the actual card
        c.revealCard();
        getChildren().add(c);
      }
      setSpacing(30);
    }

    public ArrayList<CheckBox> retrieveCheckBoxes()
    {
      ArrayList<CheckBox> ans = new ArrayList<>();
      for(Node c : getChildren())
      {
        ans.add(((PlayerCardUI) c).getCheckBox());
      }
      return ans;
    }
  }

 
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


  class pokerButton extends Button
  { // This class is just used for neater to read code
    pokerButton(String text, String color, int length, int height)
    {
      setText(text);
      setStyle("-fx-background-color:" + color +"; -fx-font-weight: 700; -fx-text-fill: white;" +
               "-fx-font-size: 25; -fx-border-radius: 10; -fx-background-radius: 13;" + 
               "-fx-border-color: #c6e2c4; -fx-border-width: 1.5;");
      setPrefSize(200, 60);
    }
    //No setters included here as buttons "should" be static in terms of their text + visuals
  }

  // For bottom buttons
  public HBox createPlayerTurnDecisions()
  {
    pokerButton callButton = new pokerButton("Call", "#1b597e", 200, 60);
    pokerButton raiseButton = new pokerButton("Raise", "#147530", 200, 60);
    pokerButton foldButton = new pokerButton("Fold", "#926f07", 200, 60);
    pokerButton endRoundButton = new pokerButton("End round", "#a2261e", 200, 60);
    HBox buttons = new HBox(callButton, raiseButton, foldButton, endRoundButton);
    buttons.setAlignment(Pos.CENTER);
    buttons.setSpacing(40);
    buttons.setPadding(new Insets(0,0,20,0));
    return buttons;
  }




  class PlayerSpace extends VBox
  {
    private PlayerHandUI cards; // I will likely need to add a method to collect view all the checkBoxes of cards in order to check if they are checked or not, but project 5 doesn't require that
    private Label playerHeader;
    //userControls not included as its never altered (only observed)
    PlayerSpace(ArrayList<Card> hand)
    {
      HBox userControls = createPlayerTurnDecisions();
      cards = new PlayerHandUI(hand);
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

    public void setDisplayedRank(HandRank r)
    {
      playerHeader.setText("Player Hand: " + HandRank.toString(r));
    }

    public void updateHand(ArrayList<Card> hand)
    {
      cards.getChildren().clear(); //Empties cards in HBox
      cards.getChildren().addAll(new PlayerHandUI(hand).getChildren()); // Populates hand with new cards
    }

    public ArrayList<Integer> determineChecked() // Ok... I worked ahead
    {
      ArrayList<Integer> ans = new ArrayList<>();
      ArrayList<CheckBox> checkBoxes = cards.retrieveCheckBoxes();
      for(int i = 0; i < checkBoxes.size(); i++)
      {
        if((checkBoxes.get(i)).isSelected())
          ans.add(i);
      }
      return ans;
    }

  }

  class DealerSpace extends VBox
  {
    private HBox cards;
    private Label dealerHeader;
    DealerSpace(ArrayList<Card> hand)
    {
      
      cards = createHand(hand);
      cards.setAlignment(Pos.CENTER);
    
      dealerHeader = new Label("Dealer Hand: PLACEHOLDER"); // For dealer, hand wont be shown at the start, but this is just for demonstration purposes
      dealerHeader.setFont(Font.font(25));
      dealerHeader.setStyle("-fx-font-weight: 700");
      dealerHeader.setTextFill(Color.WHITE);
      setSpacing(10);

      getChildren().addAll(dealerHeader, cards);
      setAlignment(Pos.CENTER);
      
    }

     public void setDisplayedRank(HandRank r)
    {
      dealerHeader.setText("Dealer Hand: " + HandRank.toString(r));
    }

    public void updateHand(ArrayList<Card> hand)
    {
       cards.getChildren().clear(); //Empties cards in HBox
      cards.getChildren().addAll(createHand(hand).getChildren()); // Populates hand with new cards
    }

    public void revealCards()
    {
      for(Node c : cards.getChildren())
        ((PokerCardUI) c).revealCard();
    }
  }


  class MessageBoard extends VBox
  {
    private Text textBody;
    MessageBoard(String msg)
    {
      Text header = new Text("Game Messages"); //learned of text type to get around using CSS
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

    public void setMessage(String s)
    {
      textBody.setText(s);
    }
    
  }

  class pokerTextWithImage extends VBox
  {
    private Text text;
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

  public Label createPokerHeader(String msg, int fontSize)
  {
    Label result = new Label(msg);
    result.setFont(Font.font(fontSize));
    result.setStyle("-fx-font-weight: 700");
    result.setTextFill(Color.WHITE);
    return result;
  }

  class PotPool extends VBox
  {
    private pokerTextWithImage pot;

    public PotPool(Double startingVal)
    {
      Label potHeader = createPokerHeader("Pot", 25);
      pot = new pokerTextWithImage("$" + Double.toString(startingVal), 25, "C:/Users/Daniel Worktop/Desktop/project5_java/project5/demo/src/main/java/com/example/assets/pot.png", 130, 200, 150);
      pot.setPadding(new Insets(20,80,10,80));
      getChildren().addAll(potHeader, pot);
      setAlignment(Pos.CENTER);
    }

    public void updateVal(Double d)
    {
      pot.setText("$" + Double.toString(d));
    }
  }

  class CenterBoard extends VBox
  {
    private MessageBoard msgBoard;
    private PotPool pot;
    CenterBoard(Double startingPot, String startingMsg)
    {
      pot = new PotPool(startingPot);
      msgBoard = new MessageBoard(startingMsg);
      getChildren().addAll(pot, msgBoard);
      setAlignment(Pos.CENTER);
      setSpacing(15);
      setPadding(new Insets(0,0,15,0));
    }

    public void updateMsg(String s)
    {
      msgBoard.setMessage(s);
    }

    public void updatePot(double d)
    {
      pot.updateVal(d);
    }
  }

  class BettingRequestUI extends VBox // This will normally show if user raises in the betting phase
  {
    TextField userInputBox;
    Button submitButton;
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
  }



  @Override
  public void start(Stage primaryStage) {
    BorderPane pokerScreen = new BorderPane();
    pokerScreen.setStyle("-fx-background-size: cover;-fx-background-image: url('file:project5/demo/src/main/java/com/example/assets/greenboard.jpg')");
    ArrayList<Card> userHand = new ArrayList<Card>(); // These ArrayLists are just demo code to show off behavior, of course my final project wont be this ugly
    userHand.add(new Card(Rank.SEVEN,Suit.HEARTS));
    userHand.add(new Card(Rank.TEN,Suit.DIAMONDS));
    userHand.add(new Card(Rank.ACE,Suit.SPADES));
    userHand.add(new Card(Rank.ACE,Suit.CLUBS));
    userHand.add(new Card(Rank.JACK,Suit.HEARTS)); // For demonstration of the hand system
    PlayerSpace userSpace = new PlayerSpace(userHand);
    userSpace.setDisplayedRank(HandRank.ONE_PAIR);
    ArrayList<Card> dealerHand = new ArrayList<Card>();
    dealerHand.add(new Card(Rank.JACK,Suit.HEARTS));
    dealerHand.add(new Card(Rank.TWO,Suit.DIAMONDS));
    dealerHand.add(new Card(Rank.KING,Suit.CLUBS));
    dealerHand.add(new Card(Rank.QUEEN,Suit.CLUBS));
    dealerHand.add(new Card(Rank.JACK,Suit.HEARTS)); // For demonstration of the hand system. Will use our actual project's hands in proeject 6.
    DealerSpace dealerSpace = new DealerSpace(dealerHand);
    //pokerScreen.setTop(dealerSpace);
    dealerSpace.updateHand(userHand); // To demonstrate that when repopulation dealer hand, you must call the reveal again ( I am intentionally flipping the dealer hand w/player hand for demonstration)
    userSpace.updateHand(dealerHand);
    PokerStatsUI rStats = new PokerStatsUI("Bet", "💵 $0", "💵 $0");
    PokerStatsUI lStats = new PokerStatsUI("Bal", "💵 $1000");
    lStats.updatePlayerStat("💵 $505"); // To show ability to alter stats
    rStats.setPadding(new Insets(38,40,0,0));
    lStats.setPadding(new Insets(38,0,0,40));
    pokerScreen.setRight(rStats);
    pokerScreen.setLeft(lStats);
    CenterBoard cBoard = new CenterBoard(0.0, "Welcome to Poker! This is a test to see just how much text can fit into this box!");
    cBoard.updatePot(6.66); // Once again proof of edit-able values
    cBoard.updateMsg("Woah, I got changed!");
    VBox Test = new VBox(dealerSpace, cBoard, userSpace);
    Test.setPadding(new Insets(0,0,20,0));
    pokerScreen.setCenter(Test);    

    BettingRequestUI bettingUI = new BettingRequestUI(); // Will be hidden by default in project 2 (but this would require event handling)
    StackPane overlay = new StackPane(pokerScreen, bettingUI); //Used to display "popups" such as betting screen on top of the game.

    Scene scene = new Scene(overlay, 1280, 960);
    primaryStage.setScene(scene);      //Place the scene in the stage
    primaryStage.show();               //Display the stage

    
  }//end start

  public static void main(String[] args)
  {
    launch(args);
    
  }
    
}//end MyFirstGUI

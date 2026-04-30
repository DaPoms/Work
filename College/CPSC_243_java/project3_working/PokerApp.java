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
package fiveCard;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.scene.control.Button;

public class PokerApp extends Application {
    
  @Override
  public void start(Stage primaryStage) {
    Button btnHello = new Button("Hello?");
    Scene scene = new Scene(btnHello, 200, 250);
    primaryStage.setScene(scene);      //Place the scene in the stage
    primaryStage.show();               //Display the stage
  }//end start
    
}//end MyFirstGUI

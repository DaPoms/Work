/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  April 21, 2026                           */
/* Due Date:       May 16th, 2026                           */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #6                                       */
/* Filename:       PokerException.java                      */
/* Purpose:        Implements error handling for            */
/*                 poker                                    */
/************************************************************/

package fiveCard;

/**
 * Implements error handling for poker.
 * fiveCard.PokerException.java
 * CPSC243 Spring 2026
 * @author Daniel Tripoli
 */
public class PokerException extends Exception {
     /**                                                   
    *      Exception message, meant to inform what the cause of the exception is
    */
    String msg;
    /**                                                   
    *      Constructor for PokerException
    *      @param msg - The msg to be associated with the exception for exception context
    */
    public PokerException(String msg)
    {
        super(msg);
    }
}

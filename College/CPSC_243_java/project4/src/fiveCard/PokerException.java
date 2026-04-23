/**
 * Implements error handling for poker
 * fiveCard.PokerException.java
 * CPSC243 Spring 2026
 * @author Daniel Tripoli
 */

/************************************************************/
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  April 21, 2026                           */
/* Due Date:       April 24, 2026                           */
/* Course: CPSC    243 010                                  */
/* Professor Name: Griffin Nye                              */
/* Project:        #4                                       */
/* Filename:       PokerException.java                      */
/* Purpose:        Implements error handling for            */
/*                 poker                                    */
/************************************************************/

package fiveCard;


public class PokerException extends Exception {
    String msg;
    /**                                                   
    *      Constructor for PokerException
    *      @param msg - The msg to be associated with the exception for exception context
    */
    PokerException(String msg)
    {
        super(msg);
    }
}

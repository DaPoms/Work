package fiveCard;

public class PokerException extends Exception {
    String msg;
    PokerException(String msg)
    {
        super(msg);
    }
}

package pl.polsl.model;



/**
 * Class with exception (divide by zero and not allowed signs)
 *  @since 1.0
 *  @author Sylwia Molitor
 *  @version 1.0
 */
public class MyException extends Exception{


    /**
     * Exception constructor (not allowed signs)
     */
    public MyException(){}
    /**
     * Exception constructor (divide by zero)
     * @param message message
     */
    public MyException(String message)
    {
        super(message);
    }
}

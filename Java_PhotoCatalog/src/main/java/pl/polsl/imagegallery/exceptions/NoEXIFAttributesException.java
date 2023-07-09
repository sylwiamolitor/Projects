package pl.polsl.imagegallery.exceptions;

public class NoEXIFAttributesException extends Exception{

    final static String DEFAULT_MESSAGE = "File metadata not containing EXIF parameters!";

    public NoEXIFAttributesException(){
        super(DEFAULT_MESSAGE);
    }

    public NoEXIFAttributesException(String message){
        super(message);
    }
}

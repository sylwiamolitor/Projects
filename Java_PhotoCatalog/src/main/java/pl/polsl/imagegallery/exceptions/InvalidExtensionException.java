package pl.polsl.imagegallery.exceptions;

public class InvalidExtensionException extends Exception{

    final static String DEFAULT_MESSAGE = "Given file not in JPEG format!";

    public InvalidExtensionException(){
        super(DEFAULT_MESSAGE);
    }

    public InvalidExtensionException(String message){
        super(message);
    }

}

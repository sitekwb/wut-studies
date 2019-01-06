package exceptions;

/**
 * Exception class inheriting from Exception, containing enum indicator of type of error in program processing.
 * @author Wojciech Sitek
 * @version 1.0
 * @since 2018-06-03
 * @see Exception
 */
public class ConnException extends Exception {
    /**
     * Error messages, corresponding with {@link ConnException.ErrorTypes}
     */
    private static String messages []= {"You entered wrong password.","Account is not existing.",
            "This mail is occupied in database.", "Unknown error.", "Don't try to be hacker!"};

    /**
     * Internal enum class, containing different types of errors.
     */
    public enum ErrorTypes{ wrongPass,notExitsting, existing, err, hacker };

    /**
     * Private field of type {@link ConnException.ErrorTypes}.
     */
    private ErrorTypes errorType;

    /**
     * Copying constructor of class.
     * @param typeOfError value copied to field {@link ConnException#errorType}.
     */
    public ConnException(ErrorTypes typeOfError){
        errorType = typeOfError;
    }

    /**
     * Get method for error message of this exception.
     * @return Corresponding to error type value of array {@link ConnException#messages}.
     */
    public String getErrorMessage(){
        return messages[errorType.ordinal()];
    }

    /**
     * Get method for error type
     * @return {@link ConnException#errorType} of type {@link ConnException.ErrorTypes}.
     */
    public ErrorTypes getErrorType(){
        return errorType;
    }
}

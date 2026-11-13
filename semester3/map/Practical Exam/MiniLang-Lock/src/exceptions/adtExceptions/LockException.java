package exceptions.adtExceptions;

import exceptions.modelExceptions.ModelException;

public class LockException extends ModelException {
    public LockException(String message) {
        super(message);
    }
}

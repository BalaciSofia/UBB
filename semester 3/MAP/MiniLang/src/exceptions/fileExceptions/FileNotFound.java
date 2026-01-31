package exceptions.fileExceptions;

import exceptions.modelExceptions.ModelException;

public class FileNotFound extends ModelException {
    public FileNotFound(String message) {
        super(message);
    }
}

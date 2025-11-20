package exceptions.fileExceptions;

import exceptions.ModelException;

public class FileNotFound extends ModelException {
    public FileNotFound(String message) {
        super(message);
    }
}

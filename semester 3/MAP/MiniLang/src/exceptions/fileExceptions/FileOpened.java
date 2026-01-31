package exceptions.fileExceptions;

import exceptions.modelExceptions.ModelException;

public class FileOpened extends ModelException {
    public FileOpened(String message) {
        super(message);
    }
}

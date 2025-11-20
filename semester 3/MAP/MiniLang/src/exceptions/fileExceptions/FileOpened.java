package exceptions.fileExceptions;

import exceptions.ModelException;

public class FileOpened extends ModelException {
    public FileOpened(String message) {
        super(message);
    }
}

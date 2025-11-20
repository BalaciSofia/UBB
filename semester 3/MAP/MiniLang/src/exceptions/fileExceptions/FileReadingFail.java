package exceptions.fileExceptions;

import exceptions.ModelException;

public class FileReadingFail extends ModelException {
    public FileReadingFail(String message) {
        super(message);
    }
}

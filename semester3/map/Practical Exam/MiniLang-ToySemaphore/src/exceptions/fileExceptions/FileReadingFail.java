package exceptions.fileExceptions;

import exceptions.modelExceptions.ModelException;

public class FileReadingFail extends ModelException {
    public FileReadingFail(String message) {
        super(message);
    }
}

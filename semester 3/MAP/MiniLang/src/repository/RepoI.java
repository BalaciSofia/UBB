package repository;

import exceptions.RepoException;
import model.ProgramState;

public interface RepoI {
    ProgramState getCurrentProgram();
    void logProgramState() throws RepoException, Exception;
}

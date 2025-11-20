package model.statements;

import exceptions.DictException;
import exceptions.ModelException;
import model.ProgramState;

public interface Statement {
    ProgramState execute(ProgramState state) throws ModelException, DictException;
    //String toString();
}

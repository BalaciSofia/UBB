package model.statements;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.ModelException;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.types.Type;

public interface Statement {
    ProgramState execute(ProgramState state) throws ModelException, DictException;
    MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) throws ModelException, DictException, Exception;
    //String toString();
}

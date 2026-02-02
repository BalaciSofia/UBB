package model.statements;

import exceptions.modelExceptions.ModelException;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.types.Type;

public class ReturnStatement implements Statement {
    @Override
    public ProgramState execute(ProgramState state) throws ModelException {
        if (state.getSymTableStack().size() <= 1) {
            return null;
        }
        state.getSymTableStack().pop();
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) {
        return typeEnv;
    }

    @Override
    public String toString() { return "return"; }
}

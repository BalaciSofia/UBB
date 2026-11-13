package model.statements;

import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.types.Type;

public class NopStatement implements Statement{
    @Override
    public ProgramState execute(ProgramState state){
        return null;
    }

    @Override
    public String toString(){
        return "nop";
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) {
        return typeEnv;
    }
}

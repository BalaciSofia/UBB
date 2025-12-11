package model.statements;

import exceptions.DictException;
import exceptions.ModelException;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.stackADT.MyStackI;
import model.ProgramState;
import model.types.Type;
import model.values.Value;

public class VarDeclStatement implements Statement{
    private String name;
    private Type type;

    public VarDeclStatement(String name, Type type) {
        this.name = name;
        this.type = type;
    }
    @Override
    public String toString(){
        return type.toString() + " " +name;
    }

    @Override
    public ProgramState execute(ProgramState state)throws ModelException, DictException {
        MyStackI<Statement> stack = state.getStack();
        MyDictionaryI<String, Value> table = state.getTable();
        if(!table.containsKey(name)){
            table.add(name,type.defaultValue());
        }
        else{
            throw new ModelException("Variable with name "+name+" already declared");
        }
        return null;
    }
}

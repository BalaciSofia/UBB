package model.expressions;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.ModelException;
import exceptions.modelExceptions.VarNotDefined;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.types.Type;
import model.values.Value;

public class VariableExpression implements Expression{

    private String variable;

    public VariableExpression(String variable){
        this.variable = variable;
    }

    @Override
    public Value evaluate(MyDictionaryI<String, Value> table, MyHeapI heap) throws ModelException, DictException {
        if(!table.containsKey(variable))
            throw new VarNotDefined("Variable " + variable + " not found");
        return table.get(variable);
    }

    @Override
    public Type typeCheck(MyDictionaryI<String, Type> typeEnv) throws ModelException {
        return typeEnv.get(variable);
    }

    @Override
    public String toString(){
        return variable;
    }
}

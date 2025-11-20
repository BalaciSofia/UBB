package model.expressions;

import exceptions.DictException;
import exceptions.ModelException;
import exceptions.VarNotDefined;
import model.adts.dictionaryADT.MyDictionaryI;
import model.values.Value;

public class VariableExpression implements Expression{

    private String variable;

    public VariableExpression(String variable){
        this.variable = variable;
    }

    @Override
    public Value evaluate(MyDictionaryI<String, Value> table) throws ModelException, DictException {
        if(!table.containsKey(variable))
            throw new VarNotDefined("Variable " + variable + " not found");
        return table.get(variable);
    }

    @Override
    public String toString(){
        return variable;
    }
}

package model.expressions;

import exceptions.ModelException;
import exceptions.VarNotDefined;
import model.adts.dictionaryADT.MyDictionaryI;
import model.values.Value;

public class ValueExpression implements Expression {

    private Value v;

    public ValueExpression(Value v){
        this.v = v;
    }

    @Override
    public Value evaluate(MyDictionaryI<String,Value> table)throws ModelException {
        if(table == null)
            throw new VarNotDefined("Symbol table is null");
        return this.v;
    }

    @Override
    public String toString(){
        return v.toString();
    }
}

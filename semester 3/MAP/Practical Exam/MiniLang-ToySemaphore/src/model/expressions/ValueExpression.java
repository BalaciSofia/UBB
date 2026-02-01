package model.expressions;

import exceptions.modelExceptions.ModelException;
import exceptions.modelExceptions.VarNotDefined;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.types.Type;
import model.values.Value;

public class ValueExpression implements Expression {

    private Value v;

    public ValueExpression(Value v){
        this.v = v;
    }

    @Override
    public Value evaluate(MyDictionaryI<String,Value> table, MyHeapI heap)throws ModelException {
        if(table == null)
            throw new VarNotDefined("Symbol table is null");
        return this.v;
    }

    @Override
    public Type typeCheck(MyDictionaryI<String, Type> typeEnv) throws ModelException {
        return v.getType();
    }

    @Override
    public String toString(){
        return v.toString();
    }
}

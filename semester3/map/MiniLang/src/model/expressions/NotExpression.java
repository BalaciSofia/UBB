package model.expressions;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.ModelException;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.types.BoolType;
import model.types.Type;
import model.values.BoolValue;
import model.values.Value;

public class NotExpression implements Expression {
    private Expression expression;

    public NotExpression(Expression expression){
        this.expression = expression;
    }

    @Override
    public Value evaluate(MyDictionaryI<String,Value> table, MyHeapI heap) throws ModelException, DictException{
        Value v = expression.evaluate(table, heap);
        if (!v.getType().equals(new BoolType()))
            throw new ModelException("NOT operand is not boolean");

        boolean b = ((BoolValue) v).getValue();
        return new BoolValue(!b);
    }

    @Override
    public Type typeCheck(MyDictionaryI<String, Type> typeEnv) throws ModelException{
        Type t = expression.typeCheck(typeEnv);
        if (!t.equals(new BoolType()))
            throw new ModelException("NOT operand is not boolean");
        return new BoolType();
    }

    @Override
    public String toString(){
        return "!(" + expression.toString() + ")";
    }
}

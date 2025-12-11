package model.expressions;

import exceptions.DictException;
import exceptions.InvalidExpression;
import exceptions.InvalidOperator;
import exceptions.ModelException;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.types.BoolType;
import model.types.Type;
import model.values.BoolValue;
import model.values.Value;

public class LogicExpression implements Expression {
    private Expression exp1;
    private Expression exp2;
    private String op;

    @Override
    public Value evaluate(MyDictionaryI<String,Value> table, MyHeapI heap) throws ModelException, DictException {
        Value v1 = exp1.evaluate(table,heap);
        Value v2 = exp2.evaluate(table,heap);
        if(v1.getType().equals(new BoolType())){
            if(v2.getType().equals(new BoolType())){
                BoolValue i1 = (BoolValue)v1;
                BoolValue i2 = (BoolValue)v2;
                boolean n1=i1.getValue();
                boolean n2=i2.getValue();
                switch(op){
                    case "and":return new BoolValue(n1 && n2);
                    case "or":return new BoolValue(n1 || n2);
                    default:throw new InvalidOperator("invalid operator");
                }
            }
            else throw new InvalidExpression("second expression is not a boolean");
        }
        else throw new InvalidExpression("first expression is not a boolean");
    }

    @Override
    public Type typeCheck(MyDictionaryI<String, Type> typeEnv) throws ModelException {
        Type typ1, typ2;
        typ1=exp1.typeCheck(typeEnv);
        typ2=exp2.typeCheck(typeEnv);
        if (typ1.equals(new BoolType())){
            if(typ2.equals(new BoolType())){
                return new BoolType();
            }
            else throw new InvalidExpression("second operand is not a boolean");
        }
        else throw new InvalidExpression("first operand is not a boolean");
    }

    @Override
    public String toString() {
        return exp1.toString() + op + exp2.toString();
    }
}

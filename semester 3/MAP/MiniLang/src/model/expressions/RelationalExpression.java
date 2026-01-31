package model.expressions;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.InvalidOperator;
import exceptions.modelExceptions.ModelException;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.types.BoolType;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;
import model.values.Value;
import model.values.BoolValue;

public class RelationalExpression implements Expression{

    private Expression expression1;
    private Expression expression2;
    private RelationalOp op;

    public RelationalExpression(Expression expression1, Expression expression2, RelationalOp op) {
        this.expression1 = expression1;
        this.expression2 = expression2;
        this.op = op;
    }

    @Override
    public Value evaluate(MyDictionaryI<String,Value>  table, MyHeapI heap)throws ModelException, DictException {
        IntValue i1 = (IntValue)expression1.evaluate(table,heap);
        IntValue i2 = (IntValue)expression2.evaluate(table,heap);
        int n1=i1.getValue();
        int n2=i2.getValue();
        boolean result;
        switch (op) {
            case EQUAL:result=n1==n2;break;
            case NOTEQUAL:result=n1!=n2;break;
            case GT:result=n1>n2;break;
            case GTEQUAL:result=n1<n2;break;
            case LT:result=n1<n2;break;
            case LTEQUAL:result=n1<=n2;break;
            default:throw new InvalidOperator("invalid operator for relational expression");
        }
        return new BoolValue(result);
    }

    @Override
    public Type typeCheck(MyDictionaryI<String, Type> typeEnv) throws ModelException {
        Type type1 = expression1.typeCheck(typeEnv);
        Type type2 = expression2.typeCheck(typeEnv);
        if (!type1.equals(new IntType()))
            throw new ModelException("first operand is not an integer");
        if (!type2.equals(new IntType()))
            throw new ModelException("second operand is not an integer");
        return new BoolType();
    }

    public String toString(){
        return "("+expression1+op.toString()+expression2+')';
    }
}

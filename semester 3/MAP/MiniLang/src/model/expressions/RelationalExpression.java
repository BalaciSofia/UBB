package model.expressions;

import exceptions.DictException;
import exceptions.InvalidOperator;
import exceptions.ModelException;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.types.IntType;
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
        Value v1=expression1.evaluate(table,heap);
        Value v2=expression2.evaluate(table,heap);
        if(!v1.getType().equals(new IntType()) || !v2.getType().equals(new IntType()))
            throw new ModelException("Relational expressions are not compatible(need int)");
        else{
            IntValue i1 = (IntValue)v1;
            IntValue i2 = (IntValue)v2;
            int n1=i1.getValue();
            int n2=i2.getValue();
            boolean result;
            switch (op) {
                case EQUAL:result=n1==n2;break;
                case NOTEQUAL:result=n1!=n2;break;
                case GT:result=n1>n2;break;
                case GTEQUAL:result=n1<n2;break;
                case LT:result=n1>=n2;break;
                case LTEQUAL:result=n1<=n2;break;
                default:throw new InvalidOperator("invalid operator for relational expression");
            }
            return new BoolValue(result);
        }
    }

    public String toString(){
        return "RelationalExpression("+expression1+op.toString()+expression2+')';
    }
}

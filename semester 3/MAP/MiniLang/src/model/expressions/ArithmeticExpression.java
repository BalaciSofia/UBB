package model.expressions;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.DivisionByZero;
import exceptions.modelExceptions.InvalidExpression;
import exceptions.modelExceptions.InvalidOperator;
import exceptions.modelExceptions.ModelException;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.types.IntType;
import model.values.IntValue;
import model.values.Value;
import model.types.Type;

public class ArithmeticExpression implements Expression{
    private Expression exp1;
    private Expression exp2;
    private char op;//"+" "-" "*" "/"

    public ArithmeticExpression(Expression exp1, Expression exp2,char op)
    {
        this.op = op;
        this.exp1 = exp1;
        this.exp2 = exp2;
    }

    @Override
    public Value evaluate(MyDictionaryI<String,Value> table, MyHeapI heap) throws ModelException, DictException {
        Value v1 = exp1.evaluate(table,heap);
        Value v2 = exp2.evaluate(table,heap);
        IntValue i1 = (IntValue)v1;
        IntValue i2 = (IntValue)v2;
        int n1=i1.getValue();
        int n2=i2.getValue();
        switch(op){
            case '+':return new IntValue(n1+n2);
            case '-':return new IntValue(n1-n2);
            case '*':return new IntValue(n1*n2);
            case '/':
                if(n2==0) throw new DivisionByZero("division by zero");
                else return  new IntValue(n1/n2);
                default: throw new InvalidOperator("invalid operator for arithmetic expression");
        }
    }

    @Override
    public Type typeCheck(MyDictionaryI<String, Type> typeEnv) throws ModelException {
        Type typ1, typ2;
        typ1=exp1.typeCheck(typeEnv);
        typ2=exp2.typeCheck(typeEnv);
        if (op != '+' && op != '-' && op != '*' && op != '/')
            throw new InvalidOperator("invalid operator for arithmetic expression");
        if (typ1.equals(new IntType())){
            if (typ2.equals(new IntType())){
                return new IntType();
            }
            else throw new InvalidExpression("second operand is not an integer");
        }
        else throw new InvalidExpression("first operand is not an integer");
    }

    @Override
    public String toString(){
        return exp1.toString() + op + exp2.toString();
    }


    @Override
    public Object clone() throws CloneNotSupportedException {
        ArithmeticExpression r = (ArithmeticExpression)super.clone();
//        r.exp1 = (Expression)exp1.clone();
//        r.exp2 = (Expression)exp2.clone();
        return r;
    }

}

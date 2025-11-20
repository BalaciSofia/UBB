package model.expressions;

import exceptions.*;
import model.adts.dictionaryADT.MyDictionaryI;
import model.types.IntType;
import model.values.IntValue;
import model.values.Value;

public class ArithmeticExpression implements Expression, Cloneable {
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
    public Value evaluate(MyDictionaryI<String, Value> table) throws ModelException, DictException {
        Value v1 = exp1.evaluate(table);
        Value v2 = exp2.evaluate(table);
        if(v1.getType().equals(new IntType())){
            if(v2.getType().equals(new IntType())){
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
            else throw new InvalidExpression("second expression is not an integer");
        }
        else throw new InvalidExpression("first expression is not an integer");
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

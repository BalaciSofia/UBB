package model.statements;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.InvalidExpression;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.adts.stackADT.MyStackI;
import model.expressions.Expression;
import model.ProgramState;
import model.types.BoolType;
import model.types.Type;
import model.values.BoolValue;
import model.values.Value;
import exceptions.modelExceptions.ModelException;

public class IfStatement implements Statement{
    private Expression exp;
    private Statement thenStatement;
    private Statement elseStatement;

    public IfStatement(Expression exp, Statement thenStatement, Statement elseStatement) {
        this.exp = exp;
        this.thenStatement = thenStatement;
        this.elseStatement = elseStatement;
    }
    @Override
    public String toString(){
        return "IF("+exp.toString()+")THEN("+thenStatement.toString()+")ELSE("+elseStatement.toString()+")";
    }

    @Override
    public ProgramState execute(ProgramState state)throws ModelException, DictException {
        //first evaluate exp
        MyStackI<Statement> stack = state.getStack();
        MyDictionaryI<String, Value> table = state.getTable();
        MyHeapI heap= state.getHeap();
        Value rez = exp.evaluate(table,heap);
        if(rez.getType().equals(new BoolType())){
            //if true the if false else
            BoolValue rez2 = (BoolValue) rez;
            if(rez2.getValue()){
                //true->then
                //execute thenStatement
                stack.push(thenStatement);
            }
            else{
                stack.push(elseStatement);
            }
        }
        else{
            throw new InvalidExpression("Expression form if statement is invalid");
        }
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) throws Exception {
        Type typeExp = exp.typeCheck(typeEnv);
        if (typeExp.equals(new BoolType())) {
            thenStatement.typeCheck(typeEnv.clone());
            elseStatement.typeCheck(typeEnv.clone());
            return typeEnv;
        } else {
            throw new ModelException("The condition of IF does not have the type bool");
        }
    }
}

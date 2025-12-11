package model.statements;

import exceptions.DictException;
import exceptions.ModelException;
import model.adts.listADT.MyListI;
import model.expressions.Expression;
import model.ProgramState;
import model.values.Value;

public class PrintStatement implements Statement {
    private Expression exp;

    public PrintStatement(Expression exp){
        this.exp = exp;
    }

    @Override
    public ProgramState execute(ProgramState state)throws ModelException, DictException {
        MyListI<Value> out =state.getOut();
        out.add(exp.evaluate(state.getTable(),state.getHeap()));
        return null;
    }

    @Override
    public String toString(){
        return "print["+exp.toString()+"]";
    }
}

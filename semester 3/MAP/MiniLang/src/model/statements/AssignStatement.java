package model.statements;

import exceptions.DictException;
import exceptions.ModelException;
import exceptions.VarNotDefined;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.stackADT.MyStackI;
import model.expressions.Expression;
import model.ProgramState;
import model.values.Value;

public class AssignStatement implements Statement{
    private String var;
    public Expression exp;

    public AssignStatement(String var, Expression exp){
        this.var = var;
        this.exp = exp;
    }

    @Override
    public ProgramState execute (ProgramState state) throws ModelException, DictException {
        MyStackI<Statement> stack = state.getStack();
        MyDictionaryI<String, Value> table = state.getTable();
        Value val=exp.evaluate(table);
        if(table.containsKey(var)){
            if(val.getType().equals(table.get(var).getType())){
                table.set(var,val);
            }
            else{
                throw new ModelException("declared type of "+var + " does not match the assigned expression");
            }
        }
        else throw new VarNotDefined("Variable "+var+" not found");
        return state;
    }

    @Override
    public String toString(){
        return var + "=" + exp.toString();
    }
}

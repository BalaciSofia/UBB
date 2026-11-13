package model.statements;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.ModelException;
import exceptions.modelExceptions.VarNotDefined;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.adts.stackADT.MyStackI;
import model.expressions.Expression;
import model.ProgramState;
import model.types.Type;
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
        MyHeapI heap= state.getHeap();
        Value val=exp.evaluate(table,heap);
        if(table.containsKey(var)){
            if(val.getType().equals(table.get(var).getType())){
                table.set(var,val);
            }
            else{
                throw new ModelException("declared type of "+var + " does not match the assigned expression");
            }
        }
        else throw new VarNotDefined("Variable "+var+" not found");
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) throws ModelException {
        Type varType = typeEnv.get(var);
        Type expType = exp.typeCheck(typeEnv);
        if (varType.equals(expType)) {
            return typeEnv;
        } else {
            throw new ModelException("Assignment: right hand side and left hand side have different types ");
        }
    }

    @Override
    public String toString(){
        return var + "=" + exp.toString();
    }
}

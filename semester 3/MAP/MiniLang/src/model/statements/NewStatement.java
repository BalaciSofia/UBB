package model.statements;

import exceptions.DictException;
import exceptions.ModelException;
import exceptions.VarNotDefined;
import model.ProgramState;
import model.expressions.Expression;
import model.types.RefType;
import model.values.RefValue;
import model.values.Value;

public class NewStatement implements Statement{
    private String label;
    private Expression exp;

    public NewStatement(String label, Expression exp) {
        this.label = label;
        this.exp = exp;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ModelException, DictException {
        if(!state.getTable().containsKey(this.label)){
            throw new VarNotDefined("Variable "+this.label+" not defined");
        }
        if(!(state.getTable().get(this.label).getType() instanceof RefType)){
            throw new VarNotDefined("Variable "+this.label+" is not a reference");
        }

        Value result=this.exp.evaluate(state.getTable(),state.getHeap());
        RefType refType=(RefType) state.getTable().get(this.label).getType();

        if (!result.getType().equals(refType.getInner())) {
            throw new ModelException("Variable " + this.label + " does not match expression result type");
        }

        int addr=state.getHeap().allocate(result);
        state.getTable().set(this.label,new RefValue(addr,refType.getInner()));
        return state;
    }

    @Override
    public String toString(){
        return "new("+this.label+","+this.exp.toString()+")";
    }
}

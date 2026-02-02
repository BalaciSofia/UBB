package model.statements;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.ModelException;
import exceptions.modelExceptions.VarNotDefined;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.expressions.Expression;
import model.types.RefType;
import model.types.Type;
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
        return null;
    }
    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) throws ModelException {
        Type varType = typeEnv.get(this.label);
        Type expType = this.exp.typeCheck(typeEnv);
        if (varType.equals(new RefType(expType))) {
            return typeEnv;
        } else {
            throw new ModelException("NEW statement: right hand side and left hand side have different types ");
        }
    }

    @Override
    public String toString(){
        return "new("+this.label+","+this.exp.toString()+")";
    }
}

// src/model/statements/WriteHeapStatement.java
package model.statements;

import exceptions.DictException;
import exceptions.ModelException;
import exceptions.VarNotDefined;
import model.ProgramState;
import model.expressions.Expression;
import model.types.RefType;
import model.values.RefValue;
import model.values.Value;

public class WriteHeapStatement implements Statement {
    private final String varName;
    private final Expression expr;

    public WriteHeapStatement(String varName, Expression expr) {
        this.varName = varName;
        this.expr = expr;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ModelException, DictException {
        if (!state.getTable().containsKey(varName)) {
            throw new VarNotDefined("Variable " + varName + " not defined");
        }

        Value varValue = state.getTable().get(varName);
        if (!(varValue.getType() instanceof RefType)) {
            throw new ModelException("Variable " + varName + " is not a reference");
        }

        RefValue ref = (RefValue) varValue;
        int address = ref.getAddress();

        if (!state.getHeap().getHeap().containsKey(address)) {
            throw new ModelException("Invalid heap address: " + address);
        }

        Value newValue = expr.evaluate(state.getTable(), state.getHeap());
        RefType refType = (RefType) varValue.getType();
        if (!newValue.getType().equals(refType.getInner())) {
            throw new ModelException("Type of expression does not match reference location type");
        }

        state.getHeap().write(address, newValue);
        return null;
    }

    @Override
    public String toString() {
        return "WriteHeap(" + varName + ", " + expr.toString() + ")";
    }
}

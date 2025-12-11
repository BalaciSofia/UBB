package model.statements;

import exceptions.DictException;
import exceptions.ModelException;
import model.ProgramState;
import model.adts.stackADT.MyStackI;
import model.expressions.Expression;
import model.types.BoolType;
import model.values.BoolValue;
import model.values.Value;

public class WhileStatement implements Statement {
    private final Expression cond;
    private final Statement instructions;

    public WhileStatement(Expression cond, Statement instructions) {
        this.cond = cond;
        this.instructions = instructions;
    }

    @Override
    public ProgramState execute(ProgramState state) throws DictException,ModelException{
        MyStackI<Statement> stack = state.getStack();
        Value condValue = cond.evaluate(state.getTable(), state.getHeap());
        if (!condValue.getType().equals(new BoolType())) {
            throw new ModelException("While condition is not a boolean.");
        }
        boolean cond = ((BoolValue) condValue).getValue();
        if (cond) {
            stack.push(this);
            stack.push(this.instructions);
        }
        return null;
    }

    @Override
    public String toString() {
        return "while(" + cond.toString() + ") { " + instructions.toString() + " }";
    }
}

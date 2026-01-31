package model.statements;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.ModelException;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.stackADT.MyStackI;
import model.expressions.Expression;
import model.types.BoolType;
import model.types.Type;
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
        boolean conditionrez = ((BoolValue) condValue).getValue();

        if (conditionrez) {
            stack.push(this);
            stack.push(this.instructions);
        }
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) throws Exception {
        Type condType = cond.typeCheck(typeEnv);
        if (!condType.equals(new BoolType())) {
            throw new ModelException("While condition is not a boolean.");
        }
        instructions.typeCheck(typeEnv.clone());
        return typeEnv;
    }

    @Override
    public String toString() {
        return "while(" + cond.toString() + ") { " + instructions.toString() + " }";
    }
}

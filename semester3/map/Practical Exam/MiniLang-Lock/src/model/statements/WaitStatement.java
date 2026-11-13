package model.statements;

import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.expressions.ValueExpression;
import model.types.Type;
import model.values.IntValue;

public class WaitStatement implements Statement {
    private int duration;

    public WaitStatement(int duration) {
        this.duration = duration;
    }

    @Override
    public ProgramState execute(ProgramState state) {
        if (duration > 0) {
            duration--;
            state.getStack().push(this);
            state.getStack().push(new PrintStatement(new ValueExpression(new IntValue(duration+1))));
        }
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "wait(" + duration + ")";
    }
}

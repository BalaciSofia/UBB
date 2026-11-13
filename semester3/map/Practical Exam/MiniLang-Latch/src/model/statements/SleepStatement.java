package model.statements;

import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.types.Type;

public class SleepStatement implements Statement {
    private int duration;

    public SleepStatement(int duration) {
        this.duration = duration;
    }

    @Override
    public ProgramState execute(ProgramState state) {
        if (duration > 0) {
            duration--;
            state.getStack().push(this);
        }
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "sleep(" + duration + ")";
    }
}

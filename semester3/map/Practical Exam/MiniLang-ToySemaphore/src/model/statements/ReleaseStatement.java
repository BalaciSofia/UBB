package model.statements;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.ModelException;
import javafx.util.Pair;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.semaphoreADT.MySemaphoreI;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;
import model.values.Value;

import java.util.List;

public class ReleaseStatement implements Statement {
    private final String varName;

    public ReleaseStatement(String varName) {
        this.varName = varName;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ModelException, DictException {
        MyDictionaryI<String, Value> symTable = state.getTable();
        MySemaphoreI semTable = state.getSemaphoreTable();

        Value v = symTable.get(varName);
        int foundIndex = ((IntValue) v).getValue();

        ProgramState.semaphoreLock.lock();
        try {
            if (!semTable.containsKey(foundIndex)) {
                throw new ModelException("release: no semaphore at index " + foundIndex);
            }

            Pair<Integer, Pair<List<Integer>, Integer>> entry = semTable.get(foundIndex);
            int n1 = entry.getKey();
            List<Integer> list = entry.getValue().getKey();
            int n2 = entry.getValue().getValue();

            list.remove((Integer)state.getId());
            semTable.update(foundIndex, new Pair<>(n1, new Pair<>(list, n2)));
        } finally {
            ProgramState.semaphoreLock.unlock();
        }
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) throws Exception {
        Type t = typeEnv.get(varName);
        if (t == null || !t.equals(new IntType())) {
            throw new ModelException("release: '" + varName + "' must be int");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "release(" + varName + ")";
    }
}

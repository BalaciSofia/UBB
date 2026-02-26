package model.statements;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.ModelException;
import javafx.util.Pair;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.semaphoreADT.MySemaphoreTableI;
import model.adts.stackADT.MyStackI;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;
import model.values.Value;

import java.util.List;

public class AcquireStatement implements Statement {
    private String varName;

    public AcquireStatement(String var) {
        this.varName = var;
    }

    public ProgramState execute(ProgramState state) throws ModelException, DictException {
        MyStackI<Statement> stack = state.getStack();
        MyDictionaryI<String, Value> symTable = state.getTable();
        MySemaphoreTableI semTable = state.getSemaphoreTable();

        ProgramState.semaphoreLock.lock();
        try {
            if(!symTable.containsKey(varName)) {
                throw new ModelException(varName + " is not defined");
            }
            Value v = symTable.get(varName);

            if (!v.getType().equals(new IntType())) {
                throw new ModelException(varName + " must be of type int");
            }

            int foundIndex = ((IntValue) v).getValue();

            if (!semTable.containsKey(foundIndex)) {
                throw new ModelException("no semaphore at index " + foundIndex);
            }
            Pair<Integer,List<Integer>> entry = semTable.get(foundIndex);
            int n1 = entry.getKey();
            List<Integer> list = entry.getValue();
            int nl = list.size();

            if (n1>nl) {
                if (!list.contains(state.getId())) {
                    list.add(state.getId());
                    semTable.update(foundIndex, new Pair<>(n1, list));
                }
            } else {
                stack.push(this);
            }
        } finally {
            ProgramState.semaphoreLock.unlock();
        }
        return null;
    }


    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) throws Exception {
        Type t = typeEnv.get(varName);
        if (t == null || !t.equals(new IntType())) {
            throw new ModelException(varName + " must be int");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "Acquire(" + varName + ")";
    }
}

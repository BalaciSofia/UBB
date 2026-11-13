package model.statements;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.ModelException;
import javafx.util.Pair;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.adts.semaphoreADT.MySemaphoreI;
import model.expressions.Expression;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;
import model.values.Value;

import java.util.ArrayList;
import java.util.List;

public class NewSemaphoreStatement implements Statement {
    private final String varName;
    private final Expression exp1;
    private final Expression exp2;

    public NewSemaphoreStatement(String varName, Expression exp1, Expression exp2) {
        this.varName = varName;
        this.exp1 = exp1;
        this.exp2 = exp2;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ModelException, DictException {
        MyDictionaryI<String, Value> symTable = state.getTable();
        MyHeapI heap = state.getHeap();
        MySemaphoreI semTable = state.getSemaphoreTable();

        Value v1 = exp1.evaluate(symTable, heap);
        Value v2 = exp2.evaluate(symTable, heap);
        int n1 = ((IntValue) v1).getValue();
        int n2 = ((IntValue) v2).getValue();

        ProgramState.semaphoreLock.lock();
        try {
            List<Integer> emptyList = new ArrayList<>();
            int location = semTable.put(new Pair<>(n1, new Pair<>(emptyList, n2)));
            symTable.set(varName, new IntValue(location));
        } finally {
            ProgramState.semaphoreLock.unlock();
        }

        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) throws Exception {
        Type varType = typeEnv.get(varName);
        if (varType == null || !varType.equals(new IntType())) {
            throw new ModelException("newSemaphore: '" + varName + "' must be declared as int");
        }
        if (!exp1.typeCheck(typeEnv).equals(new IntType())) {
            throw new ModelException("newSemaphore: exp1 must be int");
        }
        if (!exp2.typeCheck(typeEnv).equals(new IntType())) {
            throw new ModelException("newSemaphore: exp2 must be int");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "newSemaphore(" + varName + ", " + exp1 + ", " + exp2 + ")";
    }
}

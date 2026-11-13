package model.statements;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.ModelException;
import javafx.util.Pair;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.adts.semaphoreADT.MySemaphoreTableI;
import model.expressions.Expression;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;
import model.values.Value;

import java.util.ArrayList;
import java.util.List;

public class CreateSemaphore implements Statement {
    private String varName;
    private Expression cap;

    public CreateSemaphore(String varName, Expression cap) {
        this.varName = varName;
        this.cap = cap;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ModelException, DictException {
        MySemaphoreTableI semTable = state.getSemaphoreTable();
        MyHeapI heap = state.getHeap();
        MyDictionaryI<String, Value> symTable = state.getTable();

        ProgramState.semaphoreLock.lock();
        try {
            Value capValue = cap.evaluate(symTable, heap);
            if (!capValue.getType().equals(new IntType())) {
                throw new ModelException("Expression must evaluate to an int");
            }
            int number = ((IntValue) capValue).getValue();

            Value aux = symTable.get(varName);
            if (aux == null || !aux.getType().equals(new IntType())) {
                throw new ModelException("Variable must be defined as int");
            }

            List<Integer> emptyList = new ArrayList<>();
            int location = semTable.put(new Pair<>(number,emptyList));
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
            throw new ModelException(varName + " must be declared as int");
        }
        if (!cap.typeCheck(typeEnv).equals(new IntType())) {
            throw new ModelException("Expression must evaluate to int");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "CreateSemaphore(" + varName + ", " + cap.toString() + ")";
    }
}

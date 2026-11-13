package model.statements;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.ModelException;
import javafx.util.Pair;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeap;
import model.adts.heapADT.MyHeapI;
import model.expressions.Expression;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;
import model.values.Value;

import java.util.ArrayList;
import java.util.List;

public class NewBarrierStatement implements Statement {
    private String varName;
    private Expression exp;

    public NewBarrierStatement(String varName, Expression exp) {
        this.varName = varName;
        this.exp = exp;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ModelException, DictException {
        MyDictionaryI<String, Value> symTable = state.getTable();
        MyHeapI heap = state.getHeap();
        Value expValue = exp.evaluate(symTable,heap);
        if (!expValue.getType().equals(new IntType())) {
            throw new ModelException("NewBarrier: expression must evaluate to an integer");
        }
        int number = ((IntValue) expValue).getValue();
        ProgramState.barrierLock.lock();
        try {
            List<Integer> emptyList = new ArrayList<>();
            int location = state.getBarrierTable().put(new Pair<>(number,emptyList));
            symTable.set(varName, new model.values.IntValue(location));
        }finally {
            ProgramState.barrierLock.unlock();
        }
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) throws Exception {
        Type varType = typeEnv.get(varName);
        if (varType == null || !varType.equals(new IntType())) {
            throw new ModelException("NewBarrier: '" + varName + "' must be declared as int");
        }
        Type expType = exp.typeCheck(typeEnv);
        if (!expType.equals(new IntType())) {
            throw new ModelException("NewBarrier: expression must be of type int");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "newBarrier("+varName+", "+exp.toString()+")";
    }
}

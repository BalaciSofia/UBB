package model.statements;

import exceptions.adtExceptions.BarrierException;
import javafx.util.Pair;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeap;
import model.adts.heapADT.MyHeapI;
import model.barrierADT.MyBarrierI;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;
import model.values.Value;

import java.util.List;

public class AwaitStatement implements Statement {
    private String var;

    public AwaitStatement(String var) {
        this.var = var;
    }

    @Override
    public ProgramState execute(ProgramState state) throws BarrierException {
        MyDictionaryI<String, Value> symTable = state.getTable();
        MyBarrierI barrierTable = state.getBarrierTable();

        ProgramState.barrierLock.lock();
        try {
        if(!symTable.containsKey(var)) {
            throw new BarrierException("Variable " + var + " not defined.");
        }

        int foundIndex = ((IntValue)symTable.get(var)).getValue();
        
        if(!barrierTable.containsKey(foundIndex)){
            throw new BarrierException("Await: no barrier at index " + foundIndex);
        }

        Pair<Integer, List<Integer>> entry = barrierTable.get(foundIndex);
        int n1 = entry.getKey();
        List<Integer> list = entry.getValue();
        int nl = list.size();
        if (n1 > nl){
            if (!list.contains(state.getId())) {
                list.add(state.getId());
                //barrierTable.update(foundIndex, new Pair<>(n1, list));
                state.getStack().push(this);
            }
            else{
                state.getStack().push(this);
            }
        }
        }finally {
            ProgramState.barrierLock.unlock();
        }
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) {
        Type varType = typeEnv.get(var);
        if (varType == null || !varType.equals(new IntType())) {
            throw new RuntimeException("Await: '" + var + "' must be declared as int");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "await(" + var + ")";
    }
}

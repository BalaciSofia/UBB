package model.statements;

import exceptions.adtExceptions.LatchException;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.adts.latchADT.MyLatchTableI;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;
import model.values.Value;

public class AwaitStatement implements Statement {
    private String varName;

    public AwaitStatement(String varName) {
        this.varName = varName;
    }

    @Override
    public ProgramState execute(ProgramState state) {
        MyDictionaryI<String, Value> symTable = state.getTable();
        MyHeapI heap = state.getHeap();
        MyLatchTableI latchTable = state.getLatchTable();

        ProgramState.latchLock.lock();
        try{
            if(!symTable.containsKey(varName)){
                throw new LatchException("Await: variable " + varName + " not defined");
            }
            if(!symTable.get(varName).getType().equals(new IntType())){
                throw new LatchException("Await: variable " + varName + " is not of type int");
            }
            int foundIndex = ((IntValue) symTable.get(varName)).getValue();

            if(!latchTable.containsKey(foundIndex)){
                throw new LatchException("Await: no latch at index " + foundIndex);
            }
            if (latchTable.get(foundIndex) != 0) {
                state.getStack().push(this);
            }
        }finally {
            ProgramState.latchLock.unlock();
        }
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) {
        Type t = typeEnv.get(varName);
        if (t == null || !t.equals(new IntType())) {
            throw new LatchException("Await: '" + varName + "' must be int");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "await(" + varName + ")";
    }
}

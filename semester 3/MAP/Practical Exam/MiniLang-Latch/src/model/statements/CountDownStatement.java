package model.statements;

import exceptions.adtExceptions.LatchException;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.adts.latchADT.MyLatchTableI;
import model.adts.listADT.MyListI;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;
import model.values.Value;

public class CountDownStatement implements Statement {
    private String varName;

    public CountDownStatement(String varName) {
        this.varName = varName;
    }

    @Override
    public ProgramState execute(ProgramState state) {
        MyDictionaryI<String, Value> symTable = state.getTable();
        MyHeapI heap = state.getHeap();
        MyLatchTableI latchTable = state.getLatchTable();
        MyListI<Value> out = state.getOut();

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
            if (latchTable.get(foundIndex) > 0) {
                latchTable.update(foundIndex, latchTable.get(foundIndex) - 1);
                out.add(new IntValue(state.getId()));
            }
            else{
                out.add(new IntValue(state.getId()));
            }
        }finally {
            ProgramState.latchLock.unlock();
        }
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) {
        Type varType = typeEnv.get(varName);
        if (varType == null || !varType.equals(new IntType())) {
            throw new LatchException("CountDown: '" + varName + "' must be declared as int");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "countDown(" + varName + ")";
    }
}

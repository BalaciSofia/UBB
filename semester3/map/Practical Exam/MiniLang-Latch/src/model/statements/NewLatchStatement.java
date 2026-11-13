package model.statements;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.ModelException;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.expressions.Expression;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;
import model.values.Value;
import model.adts.latchADT.MyLatchTableI;

public class NewLatchStatement implements Statement {
    private String varName;
    private Expression exp;

    public NewLatchStatement(String varName, Expression exp) {
        this.varName = varName;
        this.exp = exp;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ModelException, DictException {
        MyDictionaryI<String, Value> symTable = state.getTable();
        MyHeapI heap = state.getHeap();
        MyLatchTableI latchTable = state.getLatchTable();

        ProgramState.latchLock.lock();
        try {
            Value expValue = exp.evaluate(symTable, heap);

            if(!expValue.getType().equals(new IntType())){
                throw new ModelException("NewLatch: expression must evaluate to int");
            }
            if(!symTable.containsKey(varName)){
                throw new ModelException("NewLatch: variable " + varName + " not defined");
            }
            if(!symTable.get(varName).getType().equals(new IntType())){
                throw new ModelException("NewLatch: variable " + varName + " is not of type int");
            }
            int number = ((IntValue) expValue).getValue();
            int loc = latchTable.put(number);
            symTable.set(varName, new IntValue(loc));
        } finally {
            ProgramState.latchLock.unlock();
        }
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) throws ModelException {
        Type varType = typeEnv.get(varName);
        if (varType == null || !varType.equals(new IntType())) {
            throw new ModelException("NewLatch: '" + varName + "' must be declared as int");
        }
        Type expType = exp.typeCheck(typeEnv);
        if (!expType.equals(new IntType())) {
            throw new ModelException("NewLatch: expression must be of type int");
        }
        return typeEnv;
    }


    @Override
    public String toString() {
        return "newLatch(" + varName + ", " + exp.toString() + ")";
    }

}

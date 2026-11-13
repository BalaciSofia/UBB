package model.statements;

import exceptions.adtExceptions.DictException;
import exceptions.adtExceptions.LockException;
import exceptions.modelExceptions.ModelException;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.lockADT.MyLockI;
import model.types.Type;
import model.values.IntValue;
import model.values.Value;

public class NewLockStatement implements Statement {
    private String varName;

    public NewLockStatement(String varName) {
        this.varName = varName;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ModelException, DictException {
        MyDictionaryI<String, Value> symTable = state.getTable();
        MyLockI lockTable = state.getLockTable();
        ProgramState.locklock.lock();
        try {
            if (!symTable.containsKey(varName)) {
                throw new LockException("Variable " + varName + " not defined.");
            }
            if (!symTable.get(varName).getType().equals(new model.types.IntType())) {
                throw new LockException("Variable " + varName + " is not of type int.");
            }
            int loc=lockTable.put(-1);
            symTable.set(varName, new IntValue(loc));
        }finally {
            ProgramState.locklock.unlock();
        }
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) throws LockException {
        Type varType = typeEnv.get(varName);
        if (varType == null || !varType.equals(new model.types.IntType())) {
            throw new LockException("NewLock: '" + varName + "' must be declared as int");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "newLock(" + varName + ")";
    }
}

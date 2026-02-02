package model.statements;

import exceptions.adtExceptions.LockException;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.lockADT.MyLockI;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;
import model.values.Value;

public class UnlockStatement implements Statement {
    private String varName;

    public UnlockStatement(String varName) {
        this.varName = varName;
    }

    @Override
    public ProgramState execute(ProgramState state) throws LockException {
        MyDictionaryI<String, Value> symTable = state.getTable();
        MyLockI lockTable = state.getLockTable();

        ProgramState.locklock.lock();
        try{
            if (!symTable.containsKey(varName)) {
                throw new LockException("Lock: variable " + varName + " not defined");
            }
            if(!symTable.get(varName).getType().equals(new IntType())){
                throw new LockException("Lock: variable " + varName + " is not of type int");
            }

            int foundIndex = ((IntValue) symTable.get(varName)).getValue();

            if(!lockTable.containsKey(foundIndex)){
                throw new LockException("Lock: no lock at index " + foundIndex);
            }

            int lockValue = lockTable.get(foundIndex);
            if (lockValue == state.getId()) {
                lockTable.update(foundIndex, -1);
            }
            } finally {
            ProgramState.locklock.unlock();
        }
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) throws LockException {
        Type t = typeEnv.get(varName);
        if (t == null || !t.equals(new IntType())) {
            throw new LockException("Unlock: '" + varName + "' must be int");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "unlock(" + varName + ")";
    }
}

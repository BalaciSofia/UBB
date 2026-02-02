package model.adts.lockADT;

import exceptions.adtExceptions.LockException;

import java.util.Hashtable;
import java.util.Map;

public class MyLock implements MyLockI {
    private int freeLoc;
    private Map<Integer, Integer> table;

    public MyLock(){
        this.freeLoc = 1;
        this.table = new Hashtable<>();
    }

    @Override
    public int put(Integer value) throws LockException{
        table.put(freeLoc, value);
        return freeLoc++;
    }

    @Override
    public Integer get(int key) throws LockException{
        if(!table.containsKey(key)){
            throw new LockException("Lock key not found: " + key);
        }
        return table.get(key);

    }
    @Override
    public void update(int key, Integer value) throws LockException{
        if(!table.containsKey(key)){
            throw new LockException("Lock key not found: " + key);
        }
        table.put(key,value);
    }
    @Override
    public boolean containsKey(int key){
        return table.containsKey(key);
    }

    @Override
    public Map<Integer, Integer> getContent(){
        return table;
    }
}

package model.adts.latchADT;

import java.util.Hashtable;
import java.util.Map;
import exceptions.adtExceptions.LatchException;

public class MyLatchTable implements MyLatchTableI {
    private int freeLoc;
    private Map<Integer, Integer> table;

    public MyLatchTable() {
        this.freeLoc = 1;
        this.table = new Hashtable<>();
    }

    @Override
    public int put(Integer value) throws LatchException{
        table.put(freeLoc, value);
        return freeLoc++;
    }

    @Override
    public Integer get(int key) throws LatchException{
        if(!table.containsKey(key)){
            throw new LatchException("Latch key not found: " + key);
        }
        return table.get(key);

    }
    @Override
    public void update(int key, Integer value) throws LatchException{
        if(!table.containsKey(key)){
            throw new LatchException("Latch key not found: " + key);
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

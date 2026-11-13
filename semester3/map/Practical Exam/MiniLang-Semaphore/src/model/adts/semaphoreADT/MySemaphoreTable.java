package model.adts.semaphoreADT;


import java.util.Hashtable;
import java.util.List;
import java.util.Map;

import exceptions.adtExceptions.SemaphoreException;
import javafx.util.Pair;

public class MySemaphoreTable implements MySemaphoreTableI {
    private int nextFree=1;
    private Map<Integer,Pair<Integer,List<Integer>>> table;

    public MySemaphoreTable(){
        this.table=new Hashtable<>();
    }

    @Override
    public int put(Pair<Integer,List<Integer>> value){
        table.put(nextFree,value);
        return nextFree++;
    }
    @Override
    public Pair<Integer,List<Integer>> get(int key) throws SemaphoreException{
        if(!table.containsKey(key)){
            throw new SemaphoreException("Semaphore key not found: " + key);
        }
        return table.get(key);
    }
    @Override
    public void update(int key, Pair<Integer,List<Integer>> value) throws SemaphoreException{
        if(!table.containsKey(key)){
            throw new SemaphoreException("Semaphore key not found: " + key);
        }
        table.put(key,value);
    }
    @Override
    public boolean containsKey(int key){
        return table.containsKey(key);
    }

    @Override
    public Map<Integer, Pair<Integer,List<Integer>>> getContent(){
        return table;
    }

    public String toString() {
        StringBuilder result =new StringBuilder();
        for(Integer key: table.keySet()){
            result.append(key).append(" -> ").append(table.get(key).toString()).append("\n");
        }
        return result.toString();
    }
}

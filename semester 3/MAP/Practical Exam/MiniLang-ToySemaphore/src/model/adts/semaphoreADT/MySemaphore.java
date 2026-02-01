package model.adts.semaphoreADT;

import exceptions.adtExceptions.SemaphoreException;
import javafx.util.Pair;

import java.util.Hashtable;
import java.util.List;
import java.util.Map;

public class MySemaphore implements MySemaphoreI {
    private int freeLocation = 1;
    private final Map<Integer, Pair<Integer, Pair<List<Integer>, Integer>>> table;

    public MySemaphore() {
        this.table = new Hashtable<>();
    }

    @Override
    public int put(Pair<Integer, Pair<List<Integer>, Integer>> value) {
        table.put(freeLocation, value);
        return freeLocation++;
    }

    @Override
    public Pair<Integer, Pair<List<Integer>, Integer>> get(int key) throws SemaphoreException {
        if (!table.containsKey(key)) {
            throw new SemaphoreException("Semaphore key not found: " + key);
        }
        return table.get(key);
    }

    @Override
    public void update(int key, Pair<Integer, Pair<List<Integer>, Integer>> value) throws SemaphoreException {
        if (!table.containsKey(key)) {
            throw new SemaphoreException("Semaphore key not found: " + key);
        }
        table.put(key, value);
    }

    @Override
    public boolean containsKey(int key) {
        return table.containsKey(key);
    }

    @Override
    public Map<Integer, Pair<Integer, Pair<List<Integer>, Integer>>> getContent() {
        return table;
    }

    @Override
    public String toString() {
        StringBuilder result =new StringBuilder();
        for(Integer key: table.keySet()){
            result.append(key).append(" -> ").append(table.get(key).toString()).append("\n");
        }
        return result.toString();
    }
}

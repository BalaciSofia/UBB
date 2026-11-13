package model.adts.semaphoreADT;

import exceptions.adtExceptions.SemaphoreException;
import javafx.util.Pair;

import java.util.List;
import java.util.Map;

public interface MySemaphoreTableI {
    int put(Pair<Integer,List<Integer>> value);
    Pair<Integer,List<Integer>> get(int key) throws SemaphoreException;
    void update(int key, Pair<Integer,List<Integer>> value) throws SemaphoreException;
    boolean containsKey(int key);
    Map<Integer, Pair<Integer,List<Integer>>> getContent();
}

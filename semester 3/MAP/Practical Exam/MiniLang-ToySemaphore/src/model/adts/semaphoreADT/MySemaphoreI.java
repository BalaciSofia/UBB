package model.adts.semaphoreADT;

import exceptions.adtExceptions.SemaphoreException;
import javafx.util.Pair;

import java.util.List;
import java.util.Map;

public interface MySemaphoreI {
    int put(Pair<Integer, Pair<List<Integer>, Integer>> value) throws SemaphoreException;
    Pair<Integer, Pair<List<Integer>, Integer>> get(int key) throws SemaphoreException;
    void update(int key, Pair<Integer, Pair<List<Integer>, Integer>> value) throws SemaphoreException;
    boolean containsKey(int key);
    Map<Integer, Pair<Integer, Pair<List<Integer>, Integer>>> getContent();
}

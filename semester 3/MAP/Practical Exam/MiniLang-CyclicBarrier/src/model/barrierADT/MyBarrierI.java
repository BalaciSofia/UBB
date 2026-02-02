package model.barrierADT;

import exceptions.adtExceptions.BarrierException;
import javafx.util.Pair;

import java.util.List;
import java.util.Map;

public interface MyBarrierI {
    int put(Pair<Integer, List<Integer>> value) throws BarrierException;
    Pair<Integer,List<Integer>> get(int key) throws BarrierException;
    void update(int key, Pair<Integer,List<Integer>> value) throws BarrierException;
    boolean containsKey(int key);
    Map<Integer, Pair<Integer,List<Integer>>> getContent();
}

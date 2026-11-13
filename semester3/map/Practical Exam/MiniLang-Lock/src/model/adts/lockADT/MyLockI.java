package model.adts.lockADT;

import exceptions.adtExceptions.LockException;
import javafx.util.Pair;

import java.util.List;
import java.util.Map;

public interface MyLockI {
    int put(Integer value) throws LockException;
    Integer get(int key) throws LockException;
    void update(int key, Integer value) throws LockException;
    boolean containsKey(int key);
    Map<Integer, Integer> getContent();
}

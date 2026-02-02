package model.adts.latchADT;

import exceptions.adtExceptions.LatchException;

import java.util.Map;

public interface MyLatchTableI {
    int put(Integer value) throws LatchException;
    Integer get(int key) throws LatchException;
    void update(int key, Integer value) throws LatchException;
    boolean containsKey(int key);
    Map<Integer, Integer> getContent();
}

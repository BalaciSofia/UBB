package model.adts.heapADT;

import exceptions.DictException;
import model.adts.dictionaryADT.MyDictionaryI;
import model.values.Value;

import java.util.Arrays;
import java.util.Map;

public interface MyHeapI {
    public int allocate(Value value) throws DictException;
    Value read(int address);
    void write(int address, Value value)throws DictException;
    Map<Integer,Value> getHeap();
    void set(MyDictionaryI<Integer,Value> heap);
    boolean containsKey(int address);
    Value get(int address);
}

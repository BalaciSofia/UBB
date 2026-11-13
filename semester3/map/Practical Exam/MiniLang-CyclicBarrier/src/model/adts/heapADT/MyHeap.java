package model.adts.heapADT;

import exceptions.adtExceptions.DictException;
import model.adts.dictionaryADT.MyDictionary;
import model.adts.dictionaryADT.MyDictionaryI;
import model.values.Value;

import java.util.Map;

public class MyHeap implements MyHeapI{
    private MyDictionaryI<Integer, Value> heap;
    private int firstFree;

    public MyHeap(){
        this.heap= new MyDictionary<>();
        this.firstFree=1;
    }

    @Override
    public int allocate(Value value) throws DictException {
        this.heap.add(firstFree,value);
//        firstFree++;
        return firstFree++;
    }

    @Override
    public Value read(int address) {
        return this.heap.get(address);
    }

    @Override
    public void write(int address, Value value) throws DictException{
        if(this.heap.containsKey(address)){
            this.heap.set(address,value);
        }
        else {
            this.heap.add(address,value);
        }
    }


    @Override
    public Map<Integer,Value> getHeap() {
        return this.heap.getDictionary();
    }

    @Override
    public String toString(){
        return this.heap.toString();
    }

    @Override
    public void set(MyDictionaryI<Integer,Value> heap){
        this.heap=heap;
    }

    @Override
    public boolean containsKey(int address){
        return this.heap.containsKey(address);
    }

    @Override
    public Value get(int address){
        return this.heap.get(address);
    }

}

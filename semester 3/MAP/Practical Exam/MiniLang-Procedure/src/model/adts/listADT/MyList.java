package model.adts.listADT;
import exceptions.adtExceptions.ListException;

import java.util.ArrayList;
import java.util.List;
public class MyList<T> implements MyListI<T> {

    private List<T> list;

    public MyList() {
        this.list = new ArrayList<T>();
    }
    
    @Override
    public void add(T item) {
        this.list.add(item);
    }
    
    @Override
    public void remove(int index) throws ListException {
        if (index < 0 || index >= this.list.size()) {
            throw new ListException("Index out of bounds: " + index);
        }
        this.list.remove(index);
    }
    
    @Override
    public int size() {
        return this.list.size();
    }
    
    @Override
    public T get(int index) throws ListException {
        if (index < 0 || index >= this.list.size()) {
            throw new ListException("Index out of bounds: " + index);
        }
        return this.list.get(index);
    }
    
    @Override
    public boolean contains(T item) {
        return this.list.contains(item);
    }
    
    @Override
    public boolean isEmpty() {
        return this.list.isEmpty();
    }
    
    @Override
    public void set(int index, T item) throws ListException {
        if (index < 0 || index >= this.list.size()) {
            throw new ListException("Index out of bounds: " + index);
        }
        this.list.set(index, item);
    }

    @Override
    public List<T> getList() {
        return this.list;
    }

    @Override
    public String  toString() {
        StringBuilder result = new StringBuilder();
        for(T val: list){
            result.append(val.toString()).append("\n");
        }
        return result.toString();
    }


    @Override
    public MyListI<T> deepCopy() {
        MyList<T> newList = new MyList<>();
        for (T item : this.list) {
            newList.add(item);
        }
        return newList;
    }
}

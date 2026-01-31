package model.adts.listADT;

import exceptions.adtExceptions.ListException;

import java.util.List;

public interface MyListI<T>{
    void add(T item);
    void remove(int index)throws ListException;
    T get(int index)throws ListException;
    boolean isEmpty();
    void set(int index, T item)throws ListException;
    int size();
    boolean contains(T item);
    List<T> getList();
    //MyListI<T> clone();
    MyListI<T> deepCopy();
}

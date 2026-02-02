package model.adts.stackADT;

import exceptions.adtExceptions.StackException;

public interface MyStackI<T> {
    T pop() throws StackException;
    T peek() throws StackException;
    void push(T v);
    boolean isEmpty();
    //MyStackI<T> clone();
    MyStackI<T> deepCopy();
    int size();
}

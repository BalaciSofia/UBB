package model.adts.stackADT;
import exceptions.adtExceptions.StackException;

import java.util.ArrayList;
import java.util.List;

public class MyStack<T> implements MyStackI<T>,Cloneable{
    private List<T> stack;
    public MyStack(){
        this.stack= new ArrayList<>();
    }

    @Override
    public void push(T v) {
        this.stack.addFirst(v);
    }

    @Override
    public T pop()throws StackException {
        if(stack.isEmpty())
            throw new StackException("Stack is empty");
        return stack.removeFirst();
    }

    @Override
    public boolean isEmpty() {
        return this.stack.isEmpty();
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder();
        for(T val: stack){
            result.append(val.toString()).append("\n");
        }
        return result.toString();
    }


    @Override
    public MyStackI<T> deepCopy() {
        MyStack<T> newStack = new MyStack<>();
        ArrayList<T> tempStack = new ArrayList<>();
        while (!this.stack.isEmpty()) {
            T element = this.stack.removeFirst();
            tempStack.addFirst(element);
        }
        while (!tempStack.isEmpty()) {
            T element = tempStack.removeFirst();
            this.stack.addFirst(element);
            newStack.push(element);
        }
        return newStack;
    }

}

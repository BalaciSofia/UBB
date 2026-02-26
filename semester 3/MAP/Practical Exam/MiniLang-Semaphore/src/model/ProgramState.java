package model;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.ModelException;
import exceptions.adtExceptions.StackException;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.adts.listADT.MyListI;
import model.adts.semaphoreADT.MySemaphoreTableI;
import model.adts.stackADT.MyStackI;
import model.statements.Statement;
import model.values.Value;

import java.io.BufferedReader;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ProgramState {
    private final MyStackI<Statement> exeStack;
        private final MyDictionaryI<String, Value> table;
        private final MyListI<Value> output;
        private final MyDictionaryI<String, BufferedReader> fileTable;
        private final MyHeapI heap;
        private int id;
        private static int nextId=0;
        private MySemaphoreTableI semaphoreTable;
        public final static Lock semaphoreLock = new ReentrantLock();

    public ProgramState(MyStackI<Statement> stk, MyDictionaryI<String, Value> symtbl, MyListI<Value> ot,
                        MyDictionaryI<String, BufferedReader> fileTable, MyHeapI heap, MySemaphoreTableI semaphoreTable){
        this.exeStack = stk;
        this.table = symtbl;
        this.output = ot;
        this.fileTable=fileTable;
        this.heap=heap;
        this.semaphoreTable = semaphoreTable;
        this.id=getNewId();
    }
    public int getId(){
        return this.id;
    }
    public int getNewId(){
        return ++nextId;
    }
    public MyDictionaryI<String,BufferedReader> getFileTable(){
        return this.fileTable;
    }
    public MyStackI<Statement> getStack(){
        return this.exeStack;
    }
    public MyDictionaryI<String, Value> getTable(){
        return this.table;
    }
    public MyListI<Value> getOut(){
        return this.output;
    }
    public MyHeapI getHeap(){
        return this.heap;
    }
    public MySemaphoreTableI getSemaphoreTable(){
        return this.semaphoreTable;
    }

    public boolean isNotCompleted(){
        return !exeStack.isEmpty();
    }

    public ProgramState oneStep() throws ModelException, StackException, DictException {
        if (exeStack.isEmpty())
            throw new StackException("Program stack is empty");
        Statement currentStatement = exeStack.pop();
        return currentStatement.execute(this);
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append("ID:").append(this.id).append("\n").
                append("ExeStack:\n").append(exeStack.toString()).
                append("Table:\n").append(table.toString()).
                append("Output:\n").append(output.toString()).
                append("FileTable:\n").append(fileTable.toString()).
                append("Heap:\n").append(heap.toString()).
        append("SemaphoreTable:\n").append(semaphoreTable.toString()).append("\n");
        return s.toString();
    }
}

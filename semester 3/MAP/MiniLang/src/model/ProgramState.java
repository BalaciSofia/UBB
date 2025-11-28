package model;

import exceptions.DictException;
import exceptions.StackException;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.adts.listADT.MyListI;
import model.adts.stackADT.MyStackI;
import model.statements.Statement;
import model.values.Value;

import java.io.BufferedReader;

public class ProgramState {
    private final MyStackI<Statement> exeStack;
        private final MyDictionaryI<String, Value> table;
        private final MyListI<Value> output;
        private final MyDictionaryI<String, BufferedReader> fileTable;
        private final MyHeapI heap;
        //private Statement program;

    public ProgramState(MyStackI<Statement> stk, MyDictionaryI<String, Value> symtbl,MyListI<Value> ot,
                        MyDictionaryI<String, BufferedReader> fileTable, MyHeapI heap){
        this.exeStack = stk;
        this.table = symtbl;
        this.output = ot;
        this.fileTable=fileTable;
        this.heap=heap;
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

    //public Statement getProgram(){
       // return this.program;
    //}

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append("ExeStack:\n").append(exeStack.toString()).
                append("Table:\n").append(table.toString()).
                append("Output:\n").append(output.toString()).
                append("FileTable:\n").append(fileTable.toString()).
                append("Heap:\n").append(heap.toString());
        return s.toString();
    }
}

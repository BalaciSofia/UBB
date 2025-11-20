package model;

import exceptions.DictException;
import exceptions.StackException;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.listADT.MyListI;
import model.adts.stackADT.MyStackI;
import model.statements.Statement;
import model.values.Value;

import java.io.BufferedReader;

public class ProgramState {
    private MyStackI<Statement> exeStack;
        private MyDictionaryI<String, Value> table;
        private MyListI<Value> output;
        private MyDictionaryI<String, BufferedReader> fileTable;
        //private Statement program;

    public ProgramState(MyStackI<Statement> stk, MyDictionaryI<String, Value> symtbl,MyListI<Value> ot, MyDictionaryI<String, BufferedReader> fileTable){
        this.exeStack = stk;
        this.table = symtbl;
        this.output = ot;
        this.fileTable=fileTable;
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

    //public Statement getProgram(){
       // return this.program;
    //}

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append("ExeStack:\n").append(exeStack.toString()).
                append("Table:\n").append(table.toString()).
                append("Output:\n").append(output.toString()).
                append("FileTable:\n").append(fileTable.toString());
        return s.toString();
    }
}

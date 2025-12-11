package model.statements;

import model.ProgramState;
import model.adts.dictionaryADT.MyDictionary;
import model.adts.stackADT.MyStack;
import model.adts.stackADT.MyStackI;
import model.values.Value;

public class ForkStatement implements Statement{
    private Statement statement;

    public ForkStatement(Statement statement){
        this.statement=statement;
    }

    public ProgramState execute(ProgramState state){
        MyStackI<Statement> newStack = new MyStack<>();
        newStack.push(statement);
        ProgramState newProgramState = new ProgramState(newStack,state.getTable().deepCopy(), state.getOut(),state.getFileTable(), state.getHeap());
        return newProgramState;
    }

    public String toString(){
        return "fork("+statement.toString()+")";
    }
}

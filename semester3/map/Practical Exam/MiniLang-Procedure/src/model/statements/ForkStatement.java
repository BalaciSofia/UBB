package model.statements;

import exceptions.adtExceptions.StackException;
import exceptions.modelExceptions.ModelException;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionary;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.stackADT.MyStack;
import model.adts.stackADT.MyStackI;
import model.types.Type;
import model.values.Value;

public class ForkStatement implements Statement{
    private Statement statement;

    public ForkStatement(Statement statement){
        this.statement=statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ModelException {
        MyStackI<Statement> newStack = new MyStack<>();
        newStack.push(statement);
        ProgramState newProgramState = new ProgramState(newStack,state.getSymTableStack().deepCopy(), state.getOut(),state.getFileTable(), state.getHeap(), state.getProcedureTable());
        return newProgramState;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String,Type> typeEnv)throws Exception{
        statement.typeCheck(typeEnv.clone());
        return typeEnv;
    }

    public String toString(){
        return "fork("+statement.toString()+")";
    }
}

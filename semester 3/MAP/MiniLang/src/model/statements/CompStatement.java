package model.statements;

import model.adts.stackADT.MyStackI;
import model.ProgramState;

public class CompStatement implements Statement {
    private Statement statement1;
    private Statement statement2;

    public CompStatement(Statement statement1, Statement statement2) {
        this.statement1 = statement1;
        this.statement2 = statement2;
    }

    @Override
    public ProgramState execute(ProgramState state) {
        MyStackI<Statement> stack = state.getStack();
        stack.push(statement2);
        stack.push(statement1);
        return state;
    }

    @Override
    public String toString(){
        return "["+statement1.toString()+";"+statement2.toString()+"]";
    }
}

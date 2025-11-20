package controller;

import exceptions.DictException;
import exceptions.ModelException;
import exceptions.StackException;
import model.adts.stackADT.MyStackI;
import model.ProgramState;
import model.statements.Statement;
import repository.RepoI;
import exceptions.ControllerException;
public class Controller {
    private RepoI repository;
    private boolean displayFlag = false;

    public Controller(RepoI repo){
        this.repository=repo;
    }

    public Controller(RepoI repo, boolean displayFlag){
        this.repository=repo;
        this.displayFlag=displayFlag;
    }

    public void setDisplayFlag(boolean value){
        this.displayFlag=value;
    }

    public ProgramState oneStep(ProgramState state) throws ControllerException, ModelException, StackException, DictException {
        MyStackI<Statement> stack = state.getStack();
        if (stack.isEmpty())
            throw new ControllerException("Program stack is empty");
        Statement currentStatement = stack.pop();
        return currentStatement.execute(repository.getCurrentProgram());

    }

    public void allSteps() throws Exception {
        ProgramState program = repository.getCurrentProgram();
        repository.logProgramState();
        if(displayFlag)
        {
            System.out.println(program);
            System.out.println("-----------------------------------------------------");
        }
        while(!program.getStack().isEmpty()){
            oneStep(program);
            repository.logProgramState();
            if(displayFlag)
            {
                System.out.println(program);
                System.out.println("-----------------------------------------------------");
            }
        }
    }
}

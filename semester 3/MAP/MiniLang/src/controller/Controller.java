package controller;

import exceptions.DictException;
import exceptions.ModelException;
import exceptions.StackException;
import model.adts.dictionaryADT.MyDictionary;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeap;
import model.adts.heapADT.MyHeapI;
import model.adts.stackADT.MyStackI;
import model.ProgramState;
import model.statements.Statement;
import model.values.RefValue;
import model.values.Value;
import repository.RepoI;
import exceptions.ControllerException;

import java.util.ArrayList;
import java.util.List;

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

    public void garbageCollector(ProgramState state) throws DictException {
        MyDictionaryI<String,Value> table=state.getTable();
        MyHeapI heap=state.getHeap();
        List<Integer> reachable = new ArrayList<>();

        for (Value v : table.values()) {
            if (v instanceof RefValue refVal) {
                int addr = refVal.getAddress();
                if (!reachable.contains(addr))
                    reachable.add(addr);
            }
        }
        boolean changed = true;
        while (changed) {
            changed = false;
            for (int addr : new ArrayList<>(reachable)) {
                //if the heap has a value at that address
                if (heap.containsKey(addr)) {
                    Value heapValue = heap.get(addr);
                    //if heapValue is another RefValue
                    if (heapValue instanceof RefValue refVal) {
                        int nextAddr = refVal.getAddress();
                        //if new,add continue searching
                        if (!reachable.contains(nextAddr)) {
                            reachable.add(nextAddr);
                            changed = true;
                        }
                    }
                }
            }
        }
        System.out.println("Garbage Collector: Reachable addresses: " + reachable);
        MyDictionaryI<Integer, Value> newHeap = new MyDictionary<>();
        for (int addr : reachable) {
            if (heap.containsKey(addr)) {
                newHeap.add(addr, heap.get(addr));
            }
        }
        state.getHeap().set(newHeap);
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
            this.garbageCollector(program);
            repository.logProgramState();
            if(displayFlag)
            {
                System.out.println(program);
                System.out.println("-----------------------------------------------------");
            }
        }
    }
}

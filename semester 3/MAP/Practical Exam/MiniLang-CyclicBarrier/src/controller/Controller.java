package controller;

import exceptions.adtExceptions.DictException;
import model.adts.dictionaryADT.MyDictionary;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.ProgramState;
import model.values.RefValue;
import model.values.Value;
import repository.RepoI;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class Controller {
    private RepoI repository;
    private boolean displayFlag = false;
    private ExecutorService executor;

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
        //System.out.println("Garbage Collector: Reachable addresses: " + reachable);
        MyDictionaryI<Integer, Value> newHeap = new MyDictionary<>();
        for (int addr : reachable) {
            if (heap.containsKey(addr)) {
                newHeap.add(addr, heap.get(addr));
            }
        }
        state.getHeap().set(newHeap);
    }

    public void conservativeGarbageCollector(List<ProgramState> states) throws DictException {
        MyHeapI heap = states.get(0).getHeap();
        List<Integer> reachable = new ArrayList<>();

        for (ProgramState state : states) {
            MyDictionaryI<String,Value> table=state.getTable();
            for (Value v : table.values()) {
                if (v instanceof RefValue refVal) {
                    int addr = refVal.getAddress();
                    if (!reachable.contains(addr))
                        reachable.add(addr);
                }
            }
        }
        boolean changed = true;
        while (changed) {
            changed = false;
            for (int addr : new ArrayList<>(reachable)) {
                if (heap.containsKey(addr)) {
                    Value heapValue = heap.get(addr);
                    if (heapValue instanceof RefValue refVal) {
                        int nextAddr = refVal.getAddress();
                        if (!reachable.contains(nextAddr)) {
                            reachable.add(nextAddr);
                            changed = true;
                        }
                    }
                }
            }
        }
        MyDictionaryI<Integer, Value> newHeap = new MyDictionary<>();
        for (int addr : reachable) {
            if (heap.containsKey(addr)) {
                newHeap.add(addr, heap.get(addr));
            }
        }
        heap.set(newHeap);
    }

    public List<ProgramState> removeCompletedPrograms(List<ProgramState> programs){
        return programs.stream().filter(p->p.isNotCompleted()).collect(Collectors.toList());
    }

    public void oneStepAllPrograms(List<ProgramState> programs) throws Exception {
        programs.forEach(p-> {
            try {
                repository.logProgramState(p);
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        });
        List<Callable<ProgramState>> callList = programs.stream()
                .map((ProgramState p) -> (Callable<ProgramState>)(() -> {
                    return p.oneStep();
                })).toList();
        List<ProgramState> newProgramList = executor.invokeAll(callList).stream()
                .map(future -> {
                    try {
                        return future.get();
                    } catch (Exception e) {
                        throw new RuntimeException(e);
                    }
                })
                .filter(p -> p != null)
                .toList();
        programs.addAll(newProgramList);
        repository.setProgramList(programs);
        programs.forEach(p-> {
            try {
                repository.logProgramState(p);
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        });

    }

    public void allSteps() throws Exception {
        executor= Executors.newFixedThreadPool(2);
        List<ProgramState> programList=removeCompletedPrograms(repository.getProgramList());
        while(programList.size()>0){
            this.conservativeGarbageCollector(programList);
            oneStepAllPrograms(programList);
            programList=removeCompletedPrograms(repository.getProgramList());
        }
        executor.shutdownNow();
        repository.setProgramList(programList);
    }

    public void oneStepAllProgramsGui(List<ProgramState> programs) throws Exception {
        executor= Executors.newFixedThreadPool(2);
        this.conservativeGarbageCollector(programs);
        this.oneStepAllPrograms(programs);
        executor.shutdownNow();
        repository.setProgramList(programs);
    }

    public RepoI getRepository(){
        return this.repository;
    }

    public int numberOfPrograms() {
        return this.repository.getProgramsSize();
    }
}

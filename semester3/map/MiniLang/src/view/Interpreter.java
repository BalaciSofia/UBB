package view;

import controller.Controller;
import exceptions.adtExceptions.ListException;
import model.adts.dictionaryADT.MyDictionary;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeap;
import model.adts.heapADT.MyHeapI;
import model.adts.listADT.MyList;
import model.adts.listADT.MyListI;
import model.adts.stackADT.MyStack;
import model.adts.stackADT.MyStackI;
import model.ProgramState;
import model.statements.Statement;
import model.types.Type;
import model.values.Value;
import repository.HardcodedRepo;
import repository.Repo;
import repository.RepoI;

import java.io.BufferedReader;

public class Interpreter {
    public void main(String[] args) {
        HardcodedRepo examples = new HardcodedRepo();
        Statement ex1, ex2, ex3, ex4, ex5, ex6, ex7, ex8, ex9, ex10, ex11;
        Controller c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11;

        try {
            ex1 = examples.getStatements(0);
            c1 = this.createProgram(ex1,"log1.txt");

            ex2 = examples.getStatements(1);
            c2 = this.createProgram(ex2,"log2.txt");

            ex3 = examples.getStatements(2);
            c3 = this.createProgram(ex3,"log3.txt");

            ex4 = examples.getStatements(3);
            c4 = this.createProgram(ex4,"log4.txt");

            ex5 = examples.getStatements(4);
            c5 = this.createProgram(ex5,"log5.txt");

            ex6 = examples.getStatements(5);
            c6 = this.createProgram(ex6,"log6.txt");

            ex7 = examples.getStatements(6);
            c7 = this.createProgram(ex7,"log7.txt");

            ex8 = examples.getStatements(7);
            c8 = this.createProgram(ex8,"log8.txt");

            ex9 = examples.getStatements(8);
            c9 = this.createProgram(ex9,"log9.txt");

            ex10 = examples.getStatements(9);
            c10 = this.createProgram(ex10,"log10.txt");

            ex11 = examples.getStatements(10);
            c11 = this.createProgram(ex11,"log11.txt");
        } catch (ListException e) {
            throw new RuntimeException(e);
        }

        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));
        menu.addCommand(new RunExampleCommand("1", ex1.toString(), c1));
        menu.addCommand(new RunExampleCommand("2", ex2.toString(), c2));
        menu.addCommand(new RunExampleCommand("3", ex3.toString(), c3));
        menu.addCommand(new RunExampleCommand("4", ex4.toString(), c4));
        menu.addCommand(new RunExampleCommand("5", ex5.toString(), c5));
        menu.addCommand(new RunExampleCommand("6", ex6.toString(), c6));
        menu.addCommand(new RunExampleCommand("7", ex7.toString(), c7));
        menu.addCommand(new RunExampleCommand("8", ex8.toString(), c8));
        menu.addCommand(new RunExampleCommand("9", ex9.toString(), c9));
        menu.addCommand(new RunExampleCommand("10", ex10.toString(), c10));
        menu.addCommand(new RunExampleCommand("11", ex11.toString(), c11));
        menu.show();
    }

    public Controller createProgram(Statement s,String filename){
        MyDictionaryI<String, Type> typeEnv = new MyDictionary<>();
        try {
            s.typeCheck(typeEnv);
        } catch (Exception e) {
            throw new RuntimeException("Typecheck failed for program: " + e.getMessage());
        }
        MyStackI<Statement> exeStack1 = new MyStack<>();
        MyDictionaryI<String, Value> symTable1 = new MyDictionary<>();
        MyListI<Value> out1 = new MyList<>();
        MyDictionaryI<String, BufferedReader> fileTable1 = new MyDictionary<>();
        MyHeapI heap=new MyHeap();
        exeStack1.push(s);
        ProgramState programState1 = new ProgramState(exeStack1, symTable1, out1, fileTable1,heap);
        RepoI repository = new Repo(programState1, filename);
        Controller controller = new Controller(repository, true);
        return controller;
    }
}

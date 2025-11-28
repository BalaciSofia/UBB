package view;

import controller.Controller;
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
import model.values.Value;
import repository.HardcodedRepo;
import repository.Repo;
import repository.RepoI;

import java.io.BufferedReader;

public class Interpreter {
    public void main(String[] args) {
        HardcodedRepo examples = new HardcodedRepo();

        Statement ex1 = examples.getStatements(0);
        Controller c1 = this.createProgram(ex1,"log1.txt");

        Statement ex2 = examples.getStatements(1);
        Controller c2 = this.createProgram(ex2,"log2.txt");

        Statement ex3 = examples.getStatements(2);
        Controller c3 = this.createProgram(ex3,"log3.txt");

        Statement ex4 = examples.getStatements(3);
        Controller c4 = this.createProgram(ex4,"log4.txt");

        Statement ex5 = examples.getStatements(4);
        Controller c5 = this.createProgram(ex5,"log5.txt");

        Statement ex6 = examples.getStatements(5);
        Controller c6 = this.createProgram(ex6,"log6.txt");

        Statement ex7 = examples.getStatements(6);
        Controller c7 = this.createProgram(ex7,"log7.txt");

        Statement ex8 = examples.getStatements(7);
        Controller c8 = this.createProgram(ex8,"log8.txt");

        Statement ex9 = examples.getStatements(8);
        Controller c9 = this.createProgram(ex9,"log9.txt");

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
        menu.show();
    }

    public Controller createProgram(Statement s,String filename){
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

package repository;

import model.ProgramState;
import model.adts.listADT.MyList;
import model.adts.listADT.MyListI;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Repo implements RepoI {
    private List<ProgramState> programs;
    private String filename;

    public Repo(ProgramState program, String filename) {
        this.programs = new ArrayList<ProgramState>();
        this.programs.add(program);
        this.filename = filename;
    }

    @Override
    public List<ProgramState> getProgramList() {
        return this.programs;
    }

    @Override
    public void setProgramList(List<ProgramState> programs) {
        this.programs = programs;
    }

    @Override
    public void logProgramState(ProgramState program) throws Exception {
        PrintWriter logFile= new PrintWriter(new BufferedWriter(new FileWriter(filename, true)));
        logFile.print(program.toString());
        logFile.close();
    }

}

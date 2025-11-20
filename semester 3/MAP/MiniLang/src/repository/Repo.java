package repository;

import model.ProgramState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.PrintWriter;

public class Repo implements RepoI {
    private ProgramState program;
    private String filename;

    public Repo(ProgramState program, String filename) {
        this.program = program;
        this.filename = filename;
    }

    @Override
    public ProgramState getCurrentProgram() {
        return this.program;
    }

    @Override
    public void logProgramState() throws Exception {
        PrintWriter logFile= new PrintWriter(new BufferedWriter(new FileWriter(filename, true)));
        logFile.print(this.program.toString());
        logFile.close();
    }
}

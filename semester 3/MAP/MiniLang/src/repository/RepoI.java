package repository;

import exceptions.RepoException;
import model.ProgramState;
import model.adts.listADT.MyList;
import model.adts.listADT.MyListI;

import java.util.List;

public interface RepoI {
    public List<ProgramState> getProgramList();
    public void setProgramList(List<ProgramState> programStates);
    void logProgramState(ProgramState program) throws RepoException, Exception;
    int getProgramsSize();
    ProgramState getProgramWithId(int index) throws RepoException;
}

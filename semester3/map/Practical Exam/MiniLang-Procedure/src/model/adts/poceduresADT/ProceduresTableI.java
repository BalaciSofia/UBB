package model.adts.poceduresADT;

import exceptions.adtExceptions.ProcedureException;
import javafx.util.Pair;
import model.statements.Statement;

import java.util.List;
import java.util.Map;

public interface ProceduresTableI {
    boolean containsKey(String name);
    void put(String name, Pair<List<String>, Statement> def);
    Pair<List<String>, Statement> get(String name)throws ProcedureException;
    Map<String, Pair<List<String>, Statement>> getContent();
}

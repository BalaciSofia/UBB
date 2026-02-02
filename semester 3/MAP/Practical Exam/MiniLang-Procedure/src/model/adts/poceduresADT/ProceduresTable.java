package model.adts.poceduresADT;

import javafx.util.Pair;
import model.statements.Statement;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import exceptions.adtExceptions.ProcedureException;
public class ProceduresTable implements ProceduresTableI {
    private HashMap<String, Pair<List<String>, Statement>> table;

    public ProceduresTable(){
        this.table = new HashMap<>();
    }

    @Override
    public boolean containsKey(String name){
        return table.containsKey(name);
    }
    @Override
    public void put(String name, Pair<List<String>, Statement> def){
        table.put(name, def);
    }
    @Override
    public Pair<List<String>, Statement> get(String name)throws ProcedureException{
        if(!table.containsKey(name)){
            throw new ProcedureException("Procedure " + name + " not found in the procedures table.");
        }
        return table.get(name);
    }
    @Override
    public Map<String, Pair<List<String>, Statement>> getContent(){
        return table;
    }
}

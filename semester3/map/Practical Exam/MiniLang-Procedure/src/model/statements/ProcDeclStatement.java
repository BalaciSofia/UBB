package model.statements;

import exceptions.modelExceptions.ModelException;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.types.Type;
import javafx.util.Pair;

import java.util.List;

public class ProcDeclStatement implements Statement {

    private final String name;
    private final List<String> params;
    private final Statement body;

    public ProcDeclStatement(String name, List<String> params, Statement body) {
        this.name = name;
        this.params = params;
        this.body = body;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ModelException {
        var procTable = state.getProcedureTable();

        if (procTable.containsKey(name)) {
            throw new ModelException("Procedure already defined: " + name);
        }

        procTable.put(name, new Pair<>(params, body));
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "procedure " + name + "(" + String.join(",", params) + ") " + body;
    }
}

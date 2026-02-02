package model.statements;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.ModelException;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.expressions.Expression;
import model.statements.Statement;
import model.types.Type;
import model.values.Value;
import model.adts.dictionaryADT.MyDictionary;


import java.util.List;

public class CallStatement implements Statement {
    private final String fname;
    private final List<Expression> args;

    public CallStatement(String fname, List<Expression> args) {
        this.fname = fname;
        this.args = args;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ModelException, DictException {
        var procTable = state.getProcedureTable();
        if (!procTable.containsKey(fname)) {
            throw new ModelException("Procedure not found: " + fname);
        }

        var def = procTable.get(fname);
        List<String> formals = def.getKey();
        Statement body = def.getValue();

        if (formals.size() != args.size()) {
            throw new ModelException("Call " + fname + ": expected " + formals.size() +
                    " args, got " + args.size());
        }

        var currentSym = state.getSymTableStack().peek();
        var heap = state.getHeap();

        MyDictionaryI<String, Value> newSym = new MyDictionary<>();
        for (int i = 0; i < formals.size(); i++) {
            Value v = args.get(i).evaluate(currentSym, heap);
            newSym.add(formals.get(i), v);
        }

        state.getSymTableStack().push(newSym);

        state.getStack().push(new ReturnStatement());
        state.getStack().push(body);

        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) throws Exception {
        for (Expression e : args) e.typeCheck(typeEnv);
        return typeEnv;
    }

    @Override
    public String toString() {
        return "call " + fname + args;
    }
}

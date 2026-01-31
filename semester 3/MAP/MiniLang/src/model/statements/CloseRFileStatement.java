package model.statements;

import exceptions.adtExceptions.DictException;
import exceptions.fileExceptions.FileNotFound;
import exceptions.fileExceptions.FileOpened;
import exceptions.modelExceptions.InvalidExpression;
import exceptions.modelExceptions.ModelException;
import model.adts.dictionaryADT.MyDictionaryI;
import model.expressions.Expression;
import model.ProgramState;
import model.types.StringType;
import model.types.Type;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseRFileStatement implements Statement{
    private Expression exp;

    public CloseRFileStatement(Expression exp){
        this.exp = exp;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ModelException, DictException {
        Value value = exp.evaluate(state.getTable(),state.getHeap());
        if (value.getType().equals(new StringType())) {
            StringValue file = (StringValue) value;
            BufferedReader buff = (BufferedReader) state.getFileTable().get(file.toString());
            if (buff==null) {
                throw new FileOpened("File not open");
            }
            try {
                buff.close();
                state.getFileTable().remove(file.getValue());
            } catch (IOException e) {
                throw new FileNotFound("Error opening file: File not found.");
            }
        } else {
            throw new InvalidExpression("Expression is not string.");
        }
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String,Type> typeEnv) throws ModelException{
        Type typeExp = exp.typeCheck(typeEnv);
        if (!typeExp.equals(new StringType())){
            throw new ModelException("CloseRFileStatement: expression is not a string");
        }
        return typeEnv;
    }

    @Override
    public String toString(){
        return "Close File " + this.exp.toString();
    }
}

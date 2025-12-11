package model.statements;

import exceptions.DictException;
import exceptions.fileExceptions.FileNotFound;
import exceptions.fileExceptions.FileOpened;
import exceptions.ModelException;
import exceptions.InvalidExpression;
import model.expressions.Expression;
import model.ProgramState;
import model.types.StringType;
import model.values.StringValue;
import model.values.Value;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class OpenRFileStatement implements Statement{
    private Expression exp;

    public OpenRFileStatement(Expression exp){
        this.exp = exp;
    }

    @Override
    public ProgramState execute(ProgramState state)throws ModelException, DictException {
        Value value = exp.evaluate(state.getTable(),state.getHeap());
        if (value.getType().equals(new StringType())) {
            StringValue file = (StringValue) value;
            if (state.getFileTable().containsKey(file.getValue()))
                throw new FileOpened("File already opened");
            try {
                String path = file.getValue();
                BufferedReader reader = new BufferedReader(new FileReader(path));
                state.getFileTable().add(path, reader);
            } catch (IOException e) {
                throw new FileNotFound("Error opening file: File not found.");
            }
        }
        else {
            throw new InvalidExpression("Expression is not string.");
        }
        return null;
    }

    @Override
    public String toString(){
        return "Open File " + this.exp.toString();
    }
}

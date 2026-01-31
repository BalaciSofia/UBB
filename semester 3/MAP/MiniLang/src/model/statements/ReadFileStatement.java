package model.statements;

import exceptions.adtExceptions.DictException;
import exceptions.fileExceptions.FileNotFound;
import exceptions.fileExceptions.FileReadingFail;
import exceptions.modelExceptions.InvalidExpression;
import exceptions.modelExceptions.ModelException;
import model.adts.dictionaryADT.MyDictionaryI;
import model.expressions.Expression;
import model.ProgramState;
import model.types.IntType;
import model.types.StringType;
import model.types.Type;
import model.values.IntValue;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;

public class ReadFileStatement implements Statement{
    private Expression exp;
    private String varName;

    public ReadFileStatement(Expression exp, String varName) {
        this.exp = exp;
        this.varName = varName;
    }

    @Override
    public ProgramState execute(ProgramState state)throws ModelException, DictException {
        if(state.getTable().containsKey(varName) &&
        state.getTable().get(varName).getType().equals(new IntType())){
            Value value = exp.evaluate(state.getTable(),state.getHeap());
            if (value.getType().equals(new StringType())) {
                StringValue file = (StringValue) value;
                if(state.getFileTable().containsKey(file.getValue())){
                    BufferedReader reader = state.getFileTable().get(file.getValue());
                    try {
                        String line = reader.readLine();
                        if (line == null) {
                            state.getTable().set(varName, new IntType().defaultValue());
                        } else {
                            state.getTable().set(varName, new IntValue(Integer.parseInt(line)));
                        }
                    } catch (Exception e) {
                        throw new FileReadingFail("Error reading from file.");
                    }
                }
                else{
                    throw new FileNotFound("File not found");
                }
            }
            else {
                throw new InvalidExpression("Expression is not string.");
            }
        }
        else{
            throw new ModelException("Variable "+varName+" not found or invalid type");
        }
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) throws ModelException {
        Type varType = typeEnv.get(varName);
        Type expType = exp.typeCheck(typeEnv);
        if (varType.equals(new IntType())) {
            if (expType.equals(new StringType())) {
                return typeEnv;
            } else {
                throw new ModelException("ReadFile: expression is not of type string");
            }
        } else {
            throw new ModelException("ReadFile: variable " + varName + " is not of type int");
        }
    }

    @Override
    public String toString(){
        return "Read File " + this.exp.toString() + " Variable: " + this.varName;
    }
}

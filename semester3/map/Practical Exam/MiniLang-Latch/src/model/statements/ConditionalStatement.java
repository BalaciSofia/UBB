package model.statements;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.ModelException;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.stackADT.MyStackI;
import model.expressions.Expression;
import model.types.BoolType;
import model.types.Type;
import model.values.BoolValue;

public class ConditionalStatement implements Statement{
    private String varName;
    private Expression cond;
    private Expression thenExpr;
    private Expression elseExpr;


    public ConditionalStatement(String varName, Expression cond, Expression thenExpr, Expression elseExpr){
        this.varName = varName;
        this.cond = cond;
        this.thenExpr = thenExpr;
        this.elseExpr = elseExpr;
    }
    @Override
    public ProgramState execute(ProgramState state) throws ModelException, DictException{
        MyStackI<Statement> stack = state.getStack();

        Statement newstatement = new IfStatement(
                cond,
                new AssignStatement(varName, thenExpr),
                new AssignStatement(varName, elseExpr)
        );
        stack.push(newstatement);
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) throws ModelException, DictException, Exception{
        Type condType = cond.typeCheck(typeEnv);
        if (!condType.equals(new BoolType())) {
            throw new ModelException("Conditional condition is not a boolean.");
        }
        Type thenType = thenExpr.typeCheck(typeEnv);
        Type elseType = elseExpr.typeCheck(typeEnv);
        Type varType = typeEnv.get(varName);
        if (!thenType.equals(elseType)) {
            throw new ModelException("Conditional branches have different types.");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return varName + " = (" + cond + " ? " + thenExpr + " : " + elseExpr + ")";
    }

}

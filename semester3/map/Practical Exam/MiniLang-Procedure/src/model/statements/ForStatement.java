package model.statements;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.ModelException;
import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.stackADT.MyStack;
import model.adts.stackADT.MyStackI;
import model.expressions.Expression;
import model.expressions.RelationalExpression;
import model.expressions.VariableExpression;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;

import java.util.Stack;

import static model.expressions.RelationalOp.LT;

public class ForStatement implements Statement{
    private String varName;
    private Statement body;
    private Expression exprInit;
    private Expression exprCond;
    private Expression exprIncr;

    public ForStatement(String varname,Expression exprInit, Expression exprCond, Expression exprIncr, Statement body){
        this.exprInit = exprInit;
        this.exprCond = exprCond;
        this.exprIncr = exprIncr;
        this.body = body;
        this.varName = varname;
    }

    @Override
    public ProgramState execute(ProgramState state) throws ModelException, DictException{
        MyStackI stack = state.getStack();

        Statement newstatment=
                new CompStatement(
                        new VarDeclStatement(varName, new IntType()),
                        new CompStatement(
                                new AssignStatement(varName, exprInit),
                                new WhileStatement(
                                        new RelationalExpression(
                                                new VariableExpression(varName),
                                                exprCond,
                                                LT
                                        ),
                                        new CompStatement(
                                                body,
                                                new AssignStatement(varName, exprIncr)
                                        )
                                )
                        )
                );

        stack.push(newstatment);
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) throws ModelException, DictException, Exception{
        // exp1 must be int (checked BEFORE v exists)
        Type t1 = exprInit.typeCheck(typeEnv);
        if (!t1.equals(new IntType())) {
            throw new ModelException("ForStatement: exp1 (init) must have type int.");
        }

        // Now v exists as int (because desugaring declares int v;)
        MyDictionaryI<String, Type> env2 = typeEnv.clone();

        // IMPORTANT: in most projects this method is called put(...)
        // If your dictionary uses add(...), replace put with add.
        env2.add(varName, new IntType());

        Type t2 = exprCond.typeCheck(env2);
        if (!t2.equals(new IntType())) {
            throw new ModelException("ForStatement: exp2 (limit) must have type int.");
        }

        Type t3 = exprIncr.typeCheck(env2);
        if (!t3.equals(new IntType())) {
            throw new ModelException("ForStatement: exp3 (update) must have type int.");
        }

        body.typeCheck(env2);
        return typeEnv;
    }

    @Override
    public String toString(){
        return "for("+varName +"="+exprInit.toString()+";"+varName+"<"+exprCond.toString()+";"+varName+"="+exprIncr.toString()+") {"+body.toString()+"}";
    }
}

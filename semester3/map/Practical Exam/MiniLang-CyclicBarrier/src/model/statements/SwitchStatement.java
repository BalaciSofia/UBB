package model.statements;

import model.ProgramState;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.stackADT.MyStackI;
import model.expressions.Expression;
import model.expressions.RelationalExpression;
import model.types.Type;

import static model.expressions.RelationalOp.EQUAL;

public class SwitchStatement implements Statement {
    private Expression exp;
    private Expression exp1;
    private Expression exp2;
    private Statement stmt1;
    private Statement stmt2;
    private Statement defaultStmt;

    public SwitchStatement(Expression exp,Expression exp1, Expression exp2, Statement stmt1, Statement stmt2, Statement defaultStmt) {
        this.exp = exp;
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.stmt1 = stmt1;
        this.stmt2 = stmt2;
        this.defaultStmt = defaultStmt;
    }

    @Override
    public ProgramState execute(ProgramState state) {
        MyStackI<Statement> stack = state.getStack();

        Statement newStatement =
                        new IfStatement(
                                new RelationalExpression(exp, exp1,EQUAL),
                                stmt1,
                                new IfStatement(
                                        new RelationalExpression(exp, exp2,EQUAL),
                                        stmt2,
                                        defaultStmt
                                )
                        );
        stack.push(newStatement);
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) throws Exception {
        Type expType = exp.typeCheck(typeEnv);
        Type exp1Type = exp1.typeCheck(typeEnv);
        Type exp2Type = exp2.typeCheck(typeEnv);
        if (!expType.equals(exp1Type) || !expType.equals(exp2Type) || !exp1Type.equals(exp2Type)) {
            throw new Exception("Switch statement expressions must be of the same type.");
        }
        stmt1.typeCheck(typeEnv.clone());
        stmt2.typeCheck(typeEnv.clone());
        defaultStmt.typeCheck(typeEnv.clone());
        return typeEnv;
    }

    @Override
    public String toString() {
        return "switch("+exp.toString()+") case "+exp1.toString()+": "+stmt1.toString()+" case "+exp2.toString()+": "+stmt2.toString()+" default: "+defaultStmt.toString();
    }
}

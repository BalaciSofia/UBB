package model.statements;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.ModelException;
import model.ProgramState;
import model.adts.stackADT.MyStackI;
import model.expressions.Expression;
import model.expressions.NotExpression;
import model.types.BoolType;
import model.types.Type;
import model.values.BoolValue;
import model.values.Value;
import model.adts.dictionaryADT.MyDictionaryI;

public class RepeatStatement implements Statement{
    private Statement body;
    private Expression condition;

    public RepeatStatement(Expression condition,Statement body) {
        this.body = body;
        this.condition = condition;
    }

    @Override
    public ProgramState execute(ProgramState state) throws DictException,ModelException{
        MyStackI<Statement> stack = state.getStack();
        Statement newstatement =
                new CompStatement(
                        body,
                        new WhileStatement(
                                new NotExpression(condition),
                                body
                        )
                );

        stack.push(newstatement);
        return null;
    }

    @Override
    public MyDictionaryI<String, Type> typeCheck(MyDictionaryI<String, Type> typeEnv) throws Exception {
        Type condType = condition.typeCheck(typeEnv);
        if (!condType.equals(new BoolType())) {
            throw new ModelException("Repeat until condition is not a boolean.");
        }
        body.typeCheck(typeEnv.clone());
        return typeEnv;
    }

    @Override
    public String toString() {
        return "repeat { " + body.toString() + " } until" + condition.toString();
    }
}

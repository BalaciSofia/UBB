package repository;
import model.expressions.ArithmeticExpression;
import model.expressions.ValueExpression;
import model.expressions.VariableExpression;
import model.statements.*;
import model.types.BoolType;
import model.types.IntType;
import model.types.StringType;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.StringValue;

public class HardcodedRepo {
    private Statement[] statements;

    public HardcodedRepo() {
        this.statements = new Statement[5];
        this.addStatements();
    }

    public Statement getStatements(int index) {
        return this.statements[index];
    }
    public void addStatements(){
        this.statements[0] = new CompStatement(
                new VarDeclStatement("v", new IntType()),
                new CompStatement(
                        new AssignStatement("v", new ValueExpression(new IntValue(2))),
                        new PrintStatement(new VariableExpression("v"))));

        this.statements[1] = new CompStatement(new VarDeclStatement("a", new IntType()), new CompStatement(new VarDeclStatement("b", new IntType()),
                new CompStatement(new AssignStatement("a", new ArithmeticExpression(new ValueExpression(new IntValue(2)), new
                        ArithmeticExpression(new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5)), '*'), '+')),
                        new CompStatement(new AssignStatement("b", new ArithmeticExpression(new VariableExpression("a"), new ValueExpression(new
                                IntValue(1)), '+')), new PrintStatement(new VariableExpression("b"))))));

        this.statements[2] = new CompStatement(new VarDeclStatement("a", new BoolType()),
                new CompStatement(new VarDeclStatement("v", new IntType()),
                        new CompStatement(new AssignStatement("a", new ValueExpression(new BoolValue(true))),
                                new CompStatement(new IfStatement(new VariableExpression("a"), new AssignStatement("v", new ValueExpression(new
                                        IntValue(2))), new AssignStatement("v", new ValueExpression(new IntValue(3)))), new PrintStatement(new
                                        VariableExpression("v"))))));
        this.statements[3] = new CompStatement(
                new VarDeclStatement("varf", new StringType()),
                new CompStatement(
                        new AssignStatement("varf", new ValueExpression(new StringValue("test.in"))),
                        new CompStatement(
                                new OpenRFileStatement(new VariableExpression("varf")),
                                new CompStatement(
                                        new VarDeclStatement("varc", new IntType()),
                                        new CompStatement(
                                                new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                                new CompStatement(
                                                        new PrintStatement(new VariableExpression("varc")),
                                                        new CompStatement(
                                                                new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                                                new CompStatement(
                                                                        new PrintStatement(new VariableExpression("varc")),
                                                                        new CloseRFileStatement(new VariableExpression("varf"))
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );
    }
}

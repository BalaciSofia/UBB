package repository;
import exceptions.ListException;
import model.adts.listADT.MyList;
import model.adts.listADT.MyListI;
import model.expressions.*;
import model.statements.*;
import model.types.BoolType;
import model.types.IntType;
import model.types.RefType;
import model.types.StringType;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.StringValue;

import java.util.List;

import static model.expressions.RelationalOp.*;

public class HardcodedRepo {
    private MyListI<Statement> statements;

    public HardcodedRepo() {
        this.statements = new MyList<>();
        this.addStatements();
    }

    public Statement getStatements(int index) throws ListException {
        return this.statements.get(index);
    }

    public List<Statement> getStatementsList() {
        return this.statements.getList();
    }

    public MyListI<Statement> getAllStatements() {
        return this.statements;
    }

    public void addStatements() {
        this.statements.add(new CompStatement(
                new VarDeclStatement("v", new IntType()),
                new CompStatement(
                        new AssignStatement("v", new ValueExpression(new IntValue(2))),
                        new PrintStatement(new VariableExpression("v")))));

        this.statements.add(new CompStatement(new VarDeclStatement("a", new IntType()), new CompStatement(new VarDeclStatement("b", new IntType()),
                new CompStatement(new AssignStatement("a", new ArithmeticExpression(new ValueExpression(new IntValue(2)), new
                        ArithmeticExpression(new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5)), '*'), '+')),
                        new CompStatement(new AssignStatement("b", new ArithmeticExpression(new VariableExpression("a"), new ValueExpression(new
                                IntValue(1)), '+')), new PrintStatement(new VariableExpression("b")))))));

        this.statements.add(new CompStatement(new VarDeclStatement("a", new BoolType()),
                new CompStatement(new VarDeclStatement("v", new IntType()),
                        new CompStatement(new AssignStatement("a", new ValueExpression(new BoolValue(true))),
                                new CompStatement(new IfStatement(new VariableExpression("a"), new AssignStatement("v", new ValueExpression(new
                                        IntValue(2))), new AssignStatement("v", new ValueExpression(new IntValue(3)))), new PrintStatement(new
                                        VariableExpression("v")))))));
        this.statements.add(new CompStatement(
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
            )
        );
        //de la heap aloc
        this.statements.add(new CompStatement(new VarDeclStatement("v", new RefType(new IntType())),
                new CompStatement(new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompStatement(new VarDeclStatement("a", new RefType(new RefType(new IntType()))),
                                new CompStatement(new NewStatement("a", new VariableExpression("v")),
                                        new CompStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new VariableExpression("a"))))))));
        //de la heap write
        this.statements.add(
                new CompStatement(
                        new VarDeclStatement("v", new RefType(new IntType())),
                        new CompStatement(
                                new NewStatement("v", new ValueExpression(new IntValue(20))),
                                new CompStatement(
                                        new PrintStatement(
                                                new ReadHeapExpression(new VariableExpression("v"))
                                        ),
                                        new CompStatement(
                                                new WriteHeapStatement("v", new ValueExpression(new IntValue(30))),
                                                new PrintStatement(
                                                        new ArithmeticExpression(
                                                                new ReadHeapExpression(new VariableExpression("v")),
                                                                new ValueExpression(new IntValue(5)),
                                                                '+'
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );
        //garbage collector
        this.statements.add(new CompStatement(
                new VarDeclStatement("v", new RefType(new IntType())),
                new CompStatement(
                        new NewStatement("v", new ValueExpression(new IntValue(20))),
                        new CompStatement(
                                new VarDeclStatement("a", new RefType(new RefType(new IntType()))),
                                new CompStatement(
                                        new NewStatement("a", new VariableExpression("v")),
                                        new CompStatement(
                                                new NewStatement("v", new ValueExpression(new IntValue(30))),
                                                new PrintStatement(
                                                        new ReadHeapExpression(
                                                                new ReadHeapExpression(
                                                                        new VariableExpression("a")
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                )
        )
        );
        this.statements.add(
                new CompStatement(
                        new VarDeclStatement("v", new RefType(new IntType())),
                        new CompStatement(
                                new NewStatement("v", new ValueExpression(new IntValue(20))),
                                new CompStatement(
                                        new NewStatement("v", new ValueExpression(new IntValue(30))),
                                        new PrintStatement(
                                                new ReadHeapExpression(new VariableExpression("v"))
                                        )
                                )
                        )
                )
        );

        //while check
        this.statements.add(
                new CompStatement(
                        new VarDeclStatement("v", new IntType()),
                        new CompStatement(
                                new AssignStatement("v", new ValueExpression(new IntValue(4))),
                                new CompStatement(
                                        new WhileStatement(
                                                new RelationalExpression(
                                                        new VariableExpression("v"),
                                                        new ValueExpression(new IntValue(0)),
                                                        GT
                                                ),
                                                new CompStatement(
                                                        new PrintStatement(new VariableExpression("v")),
                                                        new AssignStatement(
                                                                "v",
                                                                new ArithmeticExpression(
                                                                        new VariableExpression("v"),
                                                                        new ValueExpression(new IntValue(1)),
                                                                        '-'
                                                                )
                                                        )
                                                )
                                        ),
                                        new PrintStatement(new VariableExpression("v"))
                                )
                        )
                )
        );
        this.statements.add(new CompStatement(new VarDeclStatement("v",new IntType()), new CompStatement(new VarDeclStatement("a",new RefType(new IntType())),
                new CompStatement(new AssignStatement("v",new ValueExpression(new IntValue(10))), new CompStatement(new NewStatement("a", new ValueExpression(new IntValue(22))),
                        new CompStatement(new ForkStatement(new CompStatement(new WriteHeapStatement("a", new ValueExpression(new IntValue(30))),
                                new CompStatement(new AssignStatement("v",new ValueExpression(new IntValue(32))), new CompStatement(new PrintStatement(new VariableExpression("v")),
                                        new PrintStatement(new ReadHeapExpression(new VariableExpression("a"))))))), new CompStatement(new PrintStatement(new VariableExpression("v")),
                                new PrintStatement(new ReadHeapExpression(new VariableExpression("a"))))))))));
        this.statements.add(new CompStatement(
                new VarDeclStatement("a", new IntType()),
                new CompStatement(
                        new ForkStatement(
                                new CompStatement(
                                        new AssignStatement("a", new ValueExpression(new IntValue(10))),
                                        new PrintStatement(new VariableExpression("a"))
                                )
                        ),
                        new CompStatement(
                                new AssignStatement("a", new ValueExpression(new IntValue(5))),
                                new PrintStatement(new VariableExpression("a"))
                        )
                )
        )
        );
    }
}

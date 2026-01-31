package repository;
import exceptions.adtExceptions.ListException;
import model.adts.listADT.MyList;
import model.adts.listADT.MyListI;
import model.expressions.*;
import model.statements.*;
import model.types.BoolType;
import model.types.IntType;
import model.types.RefType;
import model.types.StringType;
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
                        new CompStatement(new AssignStatement("a", new ValueExpression(new IntValue())),
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
        //repeat until check
        this.statements.add(
                new CompStatement(
                        new VarDeclStatement("v", new IntType()),
                        new CompStatement(
                                new VarDeclStatement("x", new IntType()),
                                new CompStatement(
                                        new VarDeclStatement("y", new IntType()),
                                        new CompStatement(
                                                new AssignStatement(
                                                        "v",
                                                        new ValueExpression(new IntValue(0))
                                                ),
                                                new CompStatement(
                                                        new RepeatStatement(
                                                                // condition: v == 3
                                                                new RelationalExpression(
                                                                        new VariableExpression("v"),
                                                                        new ValueExpression(new IntValue(3)),
                                                                        EQUAL
                                                                ),
                                                                // body
                                                                new CompStatement(
                                                                        new ForkStatement(
                                                                                new CompStatement(
                                                                                        new PrintStatement(
                                                                                                new VariableExpression("v")
                                                                                        ),
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
                                                                        new AssignStatement(
                                                                                "v",
                                                                                new ArithmeticExpression(
                                                                                        new VariableExpression("v"),
                                                                                        new ValueExpression(new IntValue(1)),
                                                                                        '+'
                                                                                )
                                                                        )
                                                                )
                                                        ),
                                                        new CompStatement(
                                                                new AssignStatement(
                                                                        "x",
                                                                        new ValueExpression(new IntValue(1))
                                                                ),
                                                                new CompStatement(
                                                                        new NopStatement(),
                                                                        new CompStatement(
                                                                                new AssignStatement(
                                                                                        "y",
                                                                                        new ValueExpression(new IntValue(3))
                                                                                ),
                                                                                new CompStatement(
                                                                                        new NopStatement(),
                                                                                        new PrintStatement(
                                                                                                new ArithmeticExpression(
                                                                                                        new VariableExpression("v"),
                                                                                                        new ValueExpression(new IntValue(10)),
                                                                                                        '*'
                                                                                                )
                                                                                        )
                                                                                )
                                                                        )
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );

        //for statement
        this.statements.add(
                new CompStatement(
                        // Ref int a;
                        new VarDeclStatement("a", new RefType(new IntType())),

                        new CompStatement(
                                // new(a,20);
                                new NewStatement(
                                        "a",
                                        new ValueExpression(new IntValue(20))
                                ),

                                new CompStatement(
                                        // (for(v=0; v<3; v=v+1) fork(print(v); v=v*rh(a)));
                                        new ForStatement(
                                                "v",
                                                new ValueExpression(new IntValue(0)),  // exp1 = 0
                                                new ValueExpression(new IntValue(3)),  // exp2 = 3 (LIMIT!)
                                                new ArithmeticExpression(              // exp3 = v + 1
                                                        new VariableExpression("v"),
                                                        new ValueExpression(new IntValue(1)),
                                                        '+'
                                                ),
                                                new ForkStatement(
                                                        new CompStatement(
                                                                new PrintStatement(new VariableExpression("v")),
                                                                new AssignStatement(
                                                                        "v",
                                                                        new ArithmeticExpression(
                                                                                new VariableExpression("v"),
                                                                                new ReadHeapExpression(new VariableExpression("a")),
                                                                                '*'
                                                                        )
                                                                )
                                                        )
                                                )
                                        ),

                                        // print(rh(a))
                                        new PrintStatement(
                                                new ReadHeapExpression(new VariableExpression("a"))
                                        )
                                )
                        )
                )
        );

        //conditional statement
        this.statements.add(
                new CompStatement(
                        // Ref int a;
                        new VarDeclStatement("a", new RefType(new IntType())),

                        new CompStatement(
                                // Ref int b;
                                new VarDeclStatement("b", new RefType(new IntType())),

                                new CompStatement(
                                        // int v;
                                        new VarDeclStatement("v", new IntType()),

                                        new CompStatement(
                                                // new(a,0);
                                                new NewStatement(
                                                        "a",
                                                        new ValueExpression(new IntValue(0))
                                                ),

                                                new CompStatement(
                                                        // new(b,0);
                                                        new NewStatement(
                                                                "b",
                                                                new ValueExpression(new IntValue(0))
                                                        ),

                                                        new CompStatement(
                                                                // wh(a,1);
                                                                new WriteHeapStatement(
                                                                        "a",
                                                                        new ValueExpression(new IntValue(1))
                                                                ),

                                                                new CompStatement(
                                                                        // wh(b,2);
                                                                        new WriteHeapStatement(
                                                                                "b",
                                                                                new ValueExpression(new IntValue(2))
                                                                        ),

                                                                        new CompStatement(
                                                                                // v = (rh(a) < rh(b)) ? 100 : 200;
                                                                                new ConditionalStatement(
                                                                                        "v",
                                                                                        new RelationalExpression(
                                                                                                new ReadHeapExpression(
                                                                                                        new VariableExpression("a")
                                                                                                ),
                                                                                                new ReadHeapExpression(
                                                                                                        new VariableExpression("b")
                                                                                                ),
                                                                                                RelationalOp.LT
                                                                                        ),
                                                                                        new ValueExpression(new IntValue(100)),
                                                                                        new ValueExpression(new IntValue(200))
                                                                                ),

                                                                                new CompStatement(
                                                                                        // print(v);
                                                                                        new PrintStatement(
                                                                                                new VariableExpression("v")
                                                                                        ),

                                                                                        new CompStatement(
                                                                                                // v = ((rh(b)-2) > rh(a)) ? 100 : 200;
                                                                                                new ConditionalStatement(
                                                                                                        "v",
                                                                                                        new RelationalExpression(
                                                                                                                new ArithmeticExpression(
                                                                                                                        new ReadHeapExpression(
                                                                                                                                new VariableExpression("b")
                                                                                                                        ),
                                                                                                                        new ValueExpression(new IntValue(2)),
                                                                                                                        '-'
                                                                                                                ),
                                                                                                                new ReadHeapExpression(
                                                                                                                        new VariableExpression("a")
                                                                                                                ),
                                                                                                                RelationalOp.GT
                                                                                                        ),
                                                                                                        new ValueExpression(new IntValue(100)),
                                                                                                        new ValueExpression(new IntValue(200))
                                                                                                ),

                                                                                                // print(v);
                                                                                                new PrintStatement(
                                                                                                        new VariableExpression("v")
                                                                                                )
                                                                                        )
                                                                                )
                                                                        )
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );

        //switch statement
        this.statements.add(
                new CompStatement(
                        // int a;
                        new VarDeclStatement("a", new IntType()),

                        new CompStatement(
                                // int b;
                                new VarDeclStatement("b", new IntType()),

                                new CompStatement(
                                        // int c;
                                        new VarDeclStatement("c", new IntType()),

                                        new CompStatement(
                                                // a = 1;
                                                new AssignStatement(
                                                        "a",
                                                        new ValueExpression(new IntValue(1))
                                                ),

                                                new CompStatement(
                                                        // b = 2;
                                                        new AssignStatement(
                                                                "b",
                                                                new ValueExpression(new IntValue(2))
                                                        ),

                                                        new CompStatement(
                                                                // c = 5;
                                                                new AssignStatement(
                                                                        "c",
                                                                        new ValueExpression(new IntValue(5))
                                                                ),

                                                                new CompStatement(
                                                                        // switch(a*10)
                                                                        new SwitchStatement(
                                                                                // exp: a * 10
                                                                                new ArithmeticExpression(
                                                                                        new VariableExpression("a"),
                                                                                        new ValueExpression(new IntValue(10)),
                                                                                        '*'
                                                                                ),

                                                                                // exp1: b * c
                                                                                new ArithmeticExpression(
                                                                                        new VariableExpression("b"),
                                                                                        new VariableExpression("c"),
                                                                                        '*'
                                                                                ),

                                                                                // exp2: 10
                                                                                new ValueExpression(new IntValue(10)),

                                                                                // stmt1: print(a); print(b)
                                                                                new CompStatement(
                                                                                        new PrintStatement(
                                                                                                new VariableExpression("a")
                                                                                        ),
                                                                                        new PrintStatement(
                                                                                                new VariableExpression("b")
                                                                                        )
                                                                                ),

                                                                                // stmt2: print(100); print(200)
                                                                                new CompStatement(
                                                                                        new PrintStatement(
                                                                                                new ValueExpression(new IntValue(100))
                                                                                        ),
                                                                                        new PrintStatement(
                                                                                                new ValueExpression(new IntValue(200))
                                                                                        )
                                                                                ),

                                                                                // default: print(300)
                                                                                new PrintStatement(
                                                                                        new ValueExpression(new IntValue(300))
                                                                                )
                                                                        ),

                                                                        // print(300)
                                                                        new PrintStatement(
                                                                                new ValueExpression(new IntValue(300))
                                                                        )
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );

        //sleep statement

        this.statements.add(
                new CompStatement(
                        // int v;
                        new VarDeclStatement("v", new IntType()),

                        new CompStatement(
                                // v = 0;
                                new AssignStatement(
                                        "v",
                                        new ValueExpression(new IntValue(0))
                                ),

                                new CompStatement(
                                        // while (v < 3) ( fork(print(v); v=v+1); v=v+1 )
                                        new WhileStatement(
                                                new RelationalExpression(
                                                        new VariableExpression("v"),
                                                        new ValueExpression(new IntValue(3)),
                                                        RelationalOp.LT
                                                ),
                                                new CompStatement(
                                                        new ForkStatement(
                                                                new CompStatement(
                                                                        new PrintStatement(new VariableExpression("v")),
                                                                        new AssignStatement(
                                                                                "v",
                                                                                new ArithmeticExpression(
                                                                                        new VariableExpression("v"),
                                                                                        new ValueExpression(new IntValue(1)),
                                                                                        '+'
                                                                                )
                                                                        )
                                                                )
                                                        ),
                                                        new AssignStatement(
                                                                "v",
                                                                new ArithmeticExpression(
                                                                        new VariableExpression("v"),
                                                                        new ValueExpression(new IntValue(1)),
                                                                        '+'
                                                                )
                                                        )
                                                )
                                        ),

                                        new CompStatement(
                                                // sleep(5);
                                                new SleepStatement(5),

                                                // print(v*10)
                                                new PrintStatement(
                                                        new ArithmeticExpression(
                                                                new VariableExpression("v"),
                                                                new ValueExpression(new IntValue(10)),
                                                                '*'
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );

        //wait statement
        this.statements.add(
                new CompStatement(
                        new VarDeclStatement("v", new IntType()),
                        new CompStatement(
                                new AssignStatement("v", new ValueExpression(new IntValue(20))),
                                new CompStatement(
                                        new WaitStatement(10),
                                        new PrintStatement(
                                                new ArithmeticExpression (new VariableExpression("v"),new ValueExpression(new IntValue(10)),'*')
                                        )
                                )
                        )
                )
        );
    }
}

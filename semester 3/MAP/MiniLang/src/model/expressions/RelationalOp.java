package model.expressions;

public enum RelationalOp {
    EQUAL("=="),
    NOTEQUAL("!="),
    GT(">"),
    GTEQUAL(">="),
    LT("<"),
    LTEQUAL("<=");

    private String value;

    RelationalOp(String value){
        this.value = value;
    }
    @Override
    public String toString(){
        return value;
    }
}

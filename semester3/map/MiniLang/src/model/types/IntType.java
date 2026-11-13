package model.types;

import model.values.IntValue;
import model.values.Value;

public class IntType implements Type {
    public static IntValue DEFAULT_VALUE = new IntValue(0);

    @Override
    public boolean equals(Object o){
        return o instanceof IntType;
    }

    @Override
    public String toString(){
        return "int";
    }

    @Override
    public Value defaultValue(){
        return DEFAULT_VALUE;
    }
}

package model.types;

import model.values.BoolValue;
import model.values.Value;

public class BoolType implements Type {
    public static BoolValue DEFAULT_VALUE = new BoolValue(false);

    @Override
    public boolean equals(Object o){
        return o instanceof BoolType;
    }

    @Override
    public String toString(){
        return "bool";
    }

    @Override
    public Value defaultValue() {
        return DEFAULT_VALUE;
    }
}

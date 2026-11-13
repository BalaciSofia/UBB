package model.values;

import model.types.BoolType;
import model.types.Type;

public class BoolValue implements Value{

    public boolean value;

    public BoolValue(){
        this.value = false;
    }

    public BoolValue(boolean v) {
        this.value=v;
    }

    @Override
    public Type getType(){
        return new BoolType();
    }

    public boolean getValue(){
        return this.value;
    }

    public String toString(){
        return String.valueOf(this.value);
    }

    @Override
    public boolean equals(Object o){
        if(o instanceof BoolValue){
            BoolValue other = (BoolValue)o;
            return this.value == other.value;
        }
        return false;
    }

    @Override
    public Value clone(){
        return new BoolValue(this.value);
    }
}

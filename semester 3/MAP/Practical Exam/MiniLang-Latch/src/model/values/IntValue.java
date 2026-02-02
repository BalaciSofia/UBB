package model.values;

import model.types.IntType;
import model.types.Type;

public class IntValue implements Value{
    private int value;

    public IntValue(){
        this.value = 0;
    }

    public IntValue(int v){
        this.value = v;
    }

    public int getValue(){
        return this.value;
    }

    @Override
    public Type getType(){
        return new IntType();
    }

    @Override
    public String toString(){
        return String.valueOf(this.value);
    }

    @Override
    public boolean equals(Object o){
        if(o instanceof IntValue){
            IntValue other = (IntValue)o;
            return this.value == other.value;
        }
        return false;
    }

    @Override
    public Value clone(){
        return new IntValue(this.value);
    }
}

package model.values;

import model.types.StringType;
import model.types.Type;

import java.util.Objects;

public class StringValue implements Value{
    private String value;

    public StringValue(String value){
        this.value=value;
    }

    public String getValue(){
        return value;
    }

    @Override
    public String toString(){
        return value;
    }

    @Override
    public Type getType(){
        return new StringType();
    }

    @Override
    public boolean equals(Object o){
        if(o instanceof StringValue){
            StringValue other = (StringValue)o;
            return Objects.equals(this.value, other.value);
        }
        return false;
    }

    @Override
    public Value clone(){
        return new StringValue(this.value);
    }
}

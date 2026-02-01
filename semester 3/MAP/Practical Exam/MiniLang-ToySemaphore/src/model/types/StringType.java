package model.types;

import model.values.StringValue;
import model.values.Value;

public class StringType implements Type{
    public static StringValue DEFAULT_VALUE = new StringValue("");

    @Override
    public boolean equals(Object o)
    {
        return o instanceof StringType;
    }

    @Override
    public Value defaultValue() {
        return DEFAULT_VALUE;
    }

    @Override
    public String toString()
    {
        return "string";
    }
}

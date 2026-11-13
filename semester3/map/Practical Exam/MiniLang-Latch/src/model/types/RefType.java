package model.types;
import model.types.Type;
import model.values.RefValue;
import model.values.Value;

public class RefType implements Type{
    private Type inner;

    public RefType(Type inner){
        this.inner = inner;
    }

    public Type getInner(){
        return this.inner;
    }

    @Override
    public boolean equals(Object o){
        if(o instanceof RefType)return inner.equals(((RefType) o).getInner());
        else return false;
    }

    public String toString(){
        return "Ref("+inner.toString()+")";
    }

    @Override
    public Value defaultValue() {
        //return inner.defaultValue();
        return new RefValue(0,inner);
    }
}

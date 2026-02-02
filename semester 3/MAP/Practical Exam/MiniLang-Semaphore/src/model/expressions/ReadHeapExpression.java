package model.expressions;

import exceptions.adtExceptions.DictException;
import exceptions.modelExceptions.ModelException;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.types.RefType;
import model.types.Type;
import model.values.RefValue;
import model.values.Value;

public class ReadHeapExpression implements Expression{
    private Expression expr;

    public ReadHeapExpression(Expression expr){
        this.expr = expr;
    }

    @Override
    public Value evaluate(MyDictionaryI<String, Value> table, MyHeapI heap) throws ModelException, DictException {
        Value exprValue = expr.evaluate(table, heap);
        RefValue refValue = (RefValue) exprValue;
        int address = refValue.getAddress();
        if (!heap.getHeap().containsKey(address)) {
            throw new ModelException("invalid heap address " + address);
        }
        return heap.read(address);
    }

    @Override
    public Type typeCheck(MyDictionaryI<String, Type> typeEnv) throws ModelException {
        Type exprType = expr.typeCheck(typeEnv);
        if (exprType instanceof RefType) {
            RefType refType = (RefType) exprType;
            return refType.getInner();
        } else {
            throw new ModelException("Expression is not a reference.");
        }
    }

    @Override
    public String toString(){
        return "ReadHeap("+expr.toString()+")";
    }

}

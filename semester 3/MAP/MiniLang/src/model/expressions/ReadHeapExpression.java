package model.expressions;

import exceptions.DictException;
import exceptions.ModelException;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
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
        if (!(exprValue instanceof RefValue)) {
            throw new ModelException("Expression is not a reference.");
        }
        RefValue refValue = (RefValue) exprValue;
        int address = refValue.getAddress();
        if (!heap.getHeap().containsKey(address)) {
            throw new ModelException("invalid heap address " + address);
        }
        return heap.read(address);
    }

    @Override
    public String toString(){
        return "ReadHeap("+expr.toString()+")";
    }

}

package model.expressions;

import exceptions.ModelException;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.types.Type;
import model.values.Value;
import exceptions.DictException;
public interface Expression {
    Value evaluate(MyDictionaryI<String,Value> table, MyHeapI heap) throws ModelException,DictException;
    Type typeCheck(MyDictionaryI<String, Type> typeEnv) throws ModelException;
}

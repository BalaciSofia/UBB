package model.expressions;

import exceptions.modelExceptions.ModelException;
import model.adts.dictionaryADT.MyDictionaryI;
import model.adts.heapADT.MyHeapI;
import model.types.Type;
import model.values.Value;
import exceptions.adtExceptions.DictException;
public interface Expression {
    Value evaluate(MyDictionaryI<String,Value> table, MyHeapI heap) throws ModelException,DictException;
    Type typeCheck(MyDictionaryI<String, Type> typeEnv) throws ModelException;
}

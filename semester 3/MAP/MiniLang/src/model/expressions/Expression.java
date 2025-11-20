package model.expressions;

import exceptions.ModelException;
import model.adts.dictionaryADT.MyDictionaryI;
import model.values.Value;
import exceptions.DictException;
public interface Expression {
    Value evaluate(MyDictionaryI<String,Value> table) throws ModelException,DictException;
}

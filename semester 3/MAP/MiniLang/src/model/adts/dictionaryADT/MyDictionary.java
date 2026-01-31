package model.adts.dictionaryADT;
import exceptions.adtExceptions.DictException;

import java.util.Collection;
import java.util.HashMap;
import java.util.Set;

public class MyDictionary<K,V> implements MyDictionaryI<K,V>, Cloneable {

    private HashMap<K,V> dictionary;

    public MyDictionary(){
        this.dictionary = new HashMap<K,V>();
    }

    @Override
    public void add(K key, V value)throws DictException{
        if(this.dictionary.containsKey(key))
            throw new DictException("Key already exists in dictionary" + key);
        this.dictionary.put(key,value);
    }

    @Override
    public void remove(K key) throws DictException {
        if(!this.dictionary.containsKey(key))throw new DictException("Key not found in dictionary");
        this.dictionary.remove(key);
    }

    @Override
    public V get(K key){
        return this.dictionary.get(key);
    }

    @Override
    public void set(K key, V value)throws DictException{
        if(!this.dictionary.containsKey(key))
            throw new DictException("Key not found in dictionary");
        this.dictionary.put(key,value);
    }

    @Override
    public boolean containsKey(K key){
        return this.dictionary.containsKey(key);
    }

    @Override
    public boolean  containsValue(V value){
        return this.dictionary.containsValue(value);
    }

    @Override
    public boolean isEmpty(){
        return this.dictionary.isEmpty();
    }

    @Override
    public int size(){
        return this.dictionary.size();
    }

    @Override
    public String toString() {
        StringBuilder result =new StringBuilder();
        for(K key: dictionary.keySet()){
                result.append(key).append(" -> ").append(dictionary.get(key).toString()).append("\n");
        }
        return result.toString();
    }

    @Override
    public Set<K> keySet(){
        return this.dictionary.keySet();
    }

    @Override
    public MyDictionaryI<K,V> deepCopy(){
        MyDictionary<K,V> newDict = new MyDictionary<>();
        for(K key: this.dictionary.keySet()){
            newDict.dictionary.put(key,this.dictionary.get(key));
        }
        return newDict;
    }

    @Override
    public HashMap<K,V> getDictionary(){
        return this.dictionary;
    }

    @Override
    public Collection<V> values(){
        return this.dictionary.values();
    }

    @Override
    public MyDictionaryI<K,V> clone(){
        try {
            MyDictionary<K,V> copy = (MyDictionary<K,V>) super.clone();
            copy.dictionary = (HashMap<K,V>) this.dictionary.clone();
            return copy;
        } catch (CloneNotSupportedException e) {
            throw new RuntimeException("Clone not supported", e);
        }
    }
}

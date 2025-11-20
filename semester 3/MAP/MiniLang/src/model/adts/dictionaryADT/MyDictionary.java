package model.adts.dictionaryADT;
import exceptions.DictException;

import java.util.HashMap;
import java.util.Set;

public class MyDictionary<K,V> implements MyDictionaryI<K,V>{

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

}

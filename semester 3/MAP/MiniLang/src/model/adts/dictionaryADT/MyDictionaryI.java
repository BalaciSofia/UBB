package model.adts.dictionaryADT;

import exceptions.DictException;

import java.util.Set;

public interface MyDictionaryI<K,V>{
    void add(K key, V value)throws DictException;
    void set(K key, V value)throws DictException;
    void remove(K key)throws DictException;
    V get(K key);
    boolean containsKey(K key);
    boolean containsValue(V value);
    boolean isEmpty();
    int size();
    Set<K> keySet();
    //MyDictionaryI<K,V> clone();
    MyDictionaryI<K,V> deepCopy();
}

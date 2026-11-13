#pragma once
#include <iostream>

template<typename T>
class DynamicArray {
private:
    int length, capacity;
    T* data;

    void resize();
    void shrink();
public:
    DynamicArray();
    DynamicArray(const DynamicArray& other);
    ~DynamicArray();
    void append(T value);
    void remove_index(int index);
    int getSize() const;
    int getCapacity() const;
    T& operator[](int index);
    DynamicArray& operator=(const DynamicArray& other);
};

//constructor
template<typename T>
DynamicArray<T>::DynamicArray() {
    this->capacity = 1;
    this->length = 0;
    this->data = new T[capacity];
}


//destructor
template<typename T>
DynamicArray<T>::~DynamicArray() {
    delete [] data;
}


template<typename T>
void DynamicArray<T>::resize() {
    this->capacity *= 2;
    T* temp = new T[this->capacity];
    for(int i = 0; i < this->length; i++) temp[i] = this->data[i];
    delete [] this->data;
    this->data = temp;
}

template<typename T>
void DynamicArray<T>::shrink() {
    T* temp = new T[capacity / 2];
    for(int i=0; i<this->length; i++) temp[i] = this->data[i];
    delete [] this->data;
    this->data = temp;
}

template<typename T>
void DynamicArray<T>::append(T value) {
    /*
     *adds an element to the dynamic vector
     *param:element of type T
     */
    if(this->length == this->capacity) resize();
    this->data[this->length++] = value;
}

template<typename T>
void DynamicArray<T>::remove_index(const int index) {
    /*
     *removes the element on position index from the dynamic array
     *param:the index
     */
    for(int i=index; i<this->length-1; i++) this->data[i] = this->data[i+1];
    --this->length;
    if(this->length < this->capacity / 2 ) shrink();
}

template<typename T>
int DynamicArray<T>::getSize() const {
    return this->length;
}

template<typename T>
int DynamicArray<T>::getCapacity() const {
    return this->capacity;
}

template<typename T>
T& DynamicArray<T>::operator[](int index) {
    return this->data[index];
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &other) {
    this->capacity = other.capacity;
    this->length = other.length;
    this->data = new T[this->capacity];

    for (int i = 0; i < this->length; i++)
        this->data[i] = other.data[i];
}


template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
    if (this == &other)  // Check for self-assignment
        return *this;

    delete[] this->data; // Free old memory

    this->capacity = other.capacity;
    this->length = other.length;
    this->data = new T[this->capacity];

    for (int i = 0; i < this->length; i++)
        this->data[i] = other.data[i];

    return *this;
}

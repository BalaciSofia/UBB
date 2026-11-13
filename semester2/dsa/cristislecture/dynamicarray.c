#include "dynamicarray.h"

#include <stdlib.h>

DynamicArray* create_dynamic_array() {
    DynamicArray *arr = malloc(sizeof(DynamicArray));
    arr->length = 0;
    arr->cap = 1;
    return arr;
}

void double_size(DynamicArray *arr) {
    arr->cap *= 2;      // double the capacity and reallocate
    arr->data = (void**)realloc(arr->data, arr->cap * sizeof(void *));
    // realloc(pointer, new size)
}

void shrink(DynamicArray *arr) {
    arr->cap /= 2;      // halve the capacity and reallocate
    arr->data = (void**)realloc(arr->data, arr->cap * sizeof(void *));
}

void append(DynamicArray *arr, void *item) {
    // add element to end of array
    // if the length is equal to the capacity, we need to resize
    if (arr->length == arr->cap) double_size(arr);
    arr->data[arr->length++] = item;
}

void remove_index(DynamicArray *arr, int index) {
    // remove element from specific index
    // free the pointer data[index]
    free(arr->data[index]);
    for (int i=index; i<arr->length-1; i++)
        arr->data[i] = arr->data[i+1];
    arr->length--;
    // if length is half the maximum capacity we can resize the array
    if (arr->length == arr->cap / 2) shrink(arr);
}

void destroy_dynamic_array(DynamicArray *arr) {
    for (int i=0; i<arr->length; i++)
        free(arr->data[i]);
    free(arr->data);
    free(arr);
}
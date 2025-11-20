#pragma once

typedef struct {
    int length;         // length of array
    int cap;            // maximum capacity of array
    void **data;        // elements of array
    // Estates *data
} DynamicArray;

DynamicArray* create_dynamic_array();
void double_size(DynamicArray *arr);
void shrink(DynamicArray *arr);
void append(DynamicArray *arr, void *item);
void remove_index(DynamicArray *arr, int index);
void destroy_dynamic_array(DynamicArray *arr);
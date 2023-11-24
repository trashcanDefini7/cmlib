#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct __vector {
    size_t _size;
    size_t _capacity;
    size_t _element_size;
    size_t _last_index;
    void** data;
} _vector, *vector;

#ifdef VECTOR_IMPL
#undef VECTOR_IMPL

void vector_reserve(vector vec, size_t new_capacity);
void vector_resize(vector vec, size_t new_size);

vector vector_alloc();
vector vector_new(size_t element_size);
vector vector_free(vector vec);
void vector_clear(vector vec);

size_t vector_max_size();
size_t vector_calculate_growth(vector vec, size_t new_size);

size_t vector_size(vector vec);
size_t vector_capacity(vector vec);

void vector_push_back(vector vec, const void* value);
void vector_pop_back(vector vec);

#endif

void vector_reserve(vector vec, size_t new_capacity) {
    void** temp = vec->data;

    if (vec->data)
        vec->data = realloc(vec->data, new_capacity * vec->_element_size);
    else
        vec->data = malloc(new_capacity * vec->_element_size);

    if (vec->data)
        vec->_capacity = new_capacity;
    else
        vec->data = temp;
}

void vector_resize(vector vec, size_t new_size) {
    vec->_size = new_size;
    if (new_size > vec->_capacity)
        vec->_capacity = new_size;

    vector_reserve(vec, vec->_capacity);
}

vector vector_alloc() {
    return (vector)malloc(sizeof(_vector));
}

vector vector_new(size_t element_size) {
    vector vec = vector_alloc();

    vec->_element_size = element_size;
    vec->_size = vec->_capacity = 0;
    vec->_last_index = -1;
    vec->data = NULL;

    return vec;
}

vector vector_free(vector vec) {
    free(vec->data);
    free(vec);
}

void vector_clear(vector vec) {
    size_t i = vec->_size;

    do {
        vec->data[--i] = NULL;
    } while (i != 0);
    
    vec->_last_index = 0;
    vec->_size = 0;
}

size_t vector_max_size() {
    return (size_t)pow(2.0, (double)(64 - sizeof(size_t))) - 1;
}

size_t vector_calculate_growth(vector vec, size_t new_size) {
    size_t old_capacity = vec->_capacity;
    size_t max_size = vector_max_size();

    if (old_capacity > max_size - old_capacity / 2) {
        return max_size;
    }

    size_t geometric = old_capacity + old_capacity / 2;

    if (geometric < new_size) {
        return new_size;
    }

    return geometric;
}

size_t vector_size(vector vec) {
    return vec->_size;
}

size_t vector_capacity(vector vec) {
    return vec->_capacity;
}

void vector_push_back(vector vec, const void* value) {
    if (vec->_last_index == vec->_size - 1) {
        if (vec->_size == vec->_capacity) {
            size_t new_capacity = vector_calculate_growth(vec, vec->_size + 1);
            vector_reserve(vec, new_capacity);
        }
        vec->data[++vec->_last_index] = value;
        vec->_size++;
    } else {
        size_t new_size = vec->_last_index + 2;

        vec->_size = new_size;
        vec->_last_index = new_size - 1;
        vec->data[vec->_last_index] = value;
    }
}

void vector_pop_back(vector vec) {
    vec->_size--;
    vec->data[vec->_last_index--] = NULL;
}

#endif

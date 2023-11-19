#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct __list_node {
    void* value;
    struct __list_node* prev;
    struct __list_node* next;
} _list_node, *list_node;

typedef struct __list {
    size_t _size;
    list_node _begin;
    list_node _end;
} _list, *list;

#define _ALLOC(object) (object*)malloc(sizeof(object))

list_node list_node_alloc();
list list_alloc();

list_node list_node_new(const void* value, list_node prev, list_node next);
list list_new();

void list_push_back(list l, const void* value);
void list_push_front(list l, const void* value);

void list_pop_back(list l);
void list_pop_front(list l);

void list_insert(list l, const void* value, size_t where);
void list_erase(list l, size_t start, size_t end);

bool list_empty(list l);
size_t list_size(list l);

void list_clear(list l);

list_node list_begin(list l);
list_node list_end(list l);

bool list_last(list_node node);

#ifdef LIST_IMPL
#undef LIST_IMPL

list_node list_node_alloc() {
    return _ALLOC(_list_node);
}

list list_alloc() {
    return _ALLOC(_list);
}

list_node list_node_new(const void* value, list_node prev, list_node next) {
    list_node node = list_node_alloc();

    node->value = value;
    node->prev = prev;
    node->next = next;

    return node;
}

list list_new() {
    list l = list_alloc();

    l->_begin = NULL;
    l->_end = NULL;
    l->_size = 0;

    return l;
}

void list_push_back(list l, const void* value) {
    list_node node = list_node_new(value, NULL, NULL);

    if (l->_begin == NULL) {
        l->_begin = node;
        l->_end = l->_begin;
    } else {
        node->prev = l->_end;
        l->_end->next = node;
        l->_end = node;
    }

    l->_size++;
}

void list_push_front(list l, const void* value) {
    if (l->_begin == NULL) {
        list_push_back(l, value);
    } else {
        list_node node = list_node_new(value, NULL, l->_begin);
        l->_begin->prev = node;
        l->_begin = node;
    }

    l->_size++;
}

void list_pop_back(list l) {
    l->_end = l->_end->prev;
    free(l->_end->next);
    l->_end->next = NULL;
    l->_size--;
}

void list_pop_front(list l) {
    l->_begin = l->_begin->next;
    free(l->_begin->prev);
    l->_begin->prev = NULL;
    l->_size--;
}

void list_insert(list l, const void* value, size_t where) {
    if (where == 0) {
        list_push_front(l, value);
        return;
    }

    if (where == l->_size) {
        list_push_back(l, value);
        return;
    }

    list_node cur = l->_begin;

    for (size_t i = 0; i < where - 1; i++) {
        cur = cur->next;
    }

    list_node node = list_node_new(value, cur, cur->next);
    cur->next->prev = node;
    cur->next = node;
    l->_size++;
}

void list_erase(list l, size_t start, size_t end) {
    list_node node_start = l->_begin;
    list_node node_end = l->_end;

    size_t i;

    for (i = 0; i < start; i++) {
        node_start = node_start->next;
    }

    node_end = node_start;
    for (; i < end; i++) {
        node_end = node_end->next;
    }

    node_start->prev->next = node_end;
    node_end->prev = node_start->prev;

    while (node_start != node_end) {
        list_node next = node_start->next;
        free(node_start);
        node_start = next;
    }

    l->_size -= end - start;
}

bool list_empty(list l) {
    return l->_size == 0;
}

size_t list_size(list l) {
    return l->_size;
}

void list_clear(list l) {
    list_node node = l->_begin;

    while (node->next != NULL) {
        node = node->next;
        free(node->prev);
        node->prev = NULL;
    }

    if (l->_begin != NULL) {
        free(l->_begin);
        l->_begin = NULL;
    }

    if (l->_end != NULL) {
        free(l->_end);
        l->_end = NULL;
    }

    l->_size = 0;
}

list_node list_begin(list l) {
    return l->_begin;
}

list_node list_end(list l) {
    return l->_end;
}

bool list_last(list_node node) {
    return node->next == NULL;
}

#endif

#endif

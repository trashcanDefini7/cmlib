#ifndef STACK_H
#define STACK_H

#define LIST_IMPL
#include "list.h"

typedef list stack;

stack stack_new();

void stack_push(stack stk, const void* value);
void stack_pop(stack stk);

size_t stack_size(stack stk);
bool stack_empty(stack stk);

void* stack_top(stack stk);

#ifdef STACK_IMPL
#undef STACK_IMPL

stack stack_new() {
    return list_new();
}

void stack_push(stack stk, const void* value) {
    list_push_back(stk, value);
}

void stack_pop(stack stk) {
    list_pop_back(stk);
}

size_t stack_size(stack stk) {
    return list_size(stk);
}

bool stack_empty(stack stk) {
    return list_empty(stk);
}

void* stack_top(stack stk) {
    return list_end(stk)->value;
}

#endif

#endif
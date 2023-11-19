#include <stdio.h>

#define STACK_IMPL
#include "../include/stack.h"

int main() {
    stack stk = stack_new();
    
    stack_push(stk, 53);
    stack_push(stk, 52);
    
    int val = stack_top(stk);
    stack_pop(stk);

    return 0;
}

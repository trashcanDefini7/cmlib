#include <stdio.h>

#define LIST_IMPL
#include "../include/list.h"

int main() {
    list l = list_new();

    list_push_back(l, 5);
    list_push_front(l, 10);
    list_push_back(l, 4123);
    list_push_back(l, 20);
    list_push_back(l, 50);
    list_push_back(l, 60);

    list_erase(l, 1, 4);

    list_clear(l);

    return 0;
}

#include <stdio.h>
#include <time.h>

#define VECTOR_IMPL
#include "../include/vector.h"

int main() {
    vector vec = vector_new(sizeof(int));

    srand(time(NULL));

    /*do
	{
        vector_push_back(vec, rand());
        printf("Capacity: %i, size: %i\n", vec->_capacity, vec->_size);
        for (int i = 0; i < vec->_size; i++) printf("%i ", vec->data[i]);
		printf("\n\n");
	} while (getchar());*/

    vector_resize(vec, 100);
    for (int i = 0; i < vector_size(vec); i++) {
        vec->data[i] = rand();
    }

    vector_clear(vec);

    printf("Capacity: %i, size: %i, last index: %i\n", vec->_capacity, vec->_size, vec->_last_index);
    for (size_t i = 0; i < 100; i++) {
        printf("%i ", vec->data[i]);
    }

    /*do
	{
        vector_pop_back(vec);
        printf("Capacity: %i, size: %i\n", vec->_capacity, vec->_size);
        for (int i = 0; i < vec->_size; i++) printf("%i ", vec->data[i]);
		printf("\n\n");
	} while (getchar());*/

    return 0;
}

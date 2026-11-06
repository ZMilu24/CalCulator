#include <stdlib.h>

int* newMemoryAllocate(int* input, int newCapacity) {
    
    int *temp = realloc(input, newCapacity * sizeof(int));

    if (temp == NULL) {
        free(input);
        return NULL;
    }

    return(temp);
}
#include "vec.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int capacity;
    unsigned int count;
    size_t elementSize;
} vec_info;

void vec_init(void* _refVec, unsigned int _capacity, size_t _elementSize) {
    vec_info* info = malloc(sizeof(vec_info) + (_capacity * _elementSize));

    if (info == NULL) {
        printf("Failed to init vector!");
        exit(1);
    }

    *(void**)_refVec = info + 1;

    info->capacity = _capacity;
    info->count = 0;
    info->elementSize = _elementSize;
}

void vec_free(void* _refList) {
    vec_info* info = *(vec_info**)_refList - 1;

    free(info);
    *((void**)_refList) = NULL;
}

void vec_clear(void* _refList) {
    vec_info* info = *(vec_info**)_refList - 1;

    info->count = 0;
}

void vec_add(void* _refVec, void* _value) {
    vec_info* info = *(vec_info**)_refVec - 1;

    // check if vec needs to grow
    if (info->count >= info->capacity) {
        info->capacity = info->capacity * 2;

        info = realloc( info, sizeof(vec_info) + (info->capacity * info->elementSize));

        if (info == NULL) {
            printf("Failed to resize vector!");
            exit(1);
        }

        *(void**)_refVec = info + 1;
    }

    memcpy(
        *(char**)_refVec + (info->count * info->elementSize),
        _value,
        info->elementSize
    );

    info->count++;
}

unsigned int vec_count(void* _refList) {
    vec_info* info = *(vec_info**)_refList - 1;

    return info->count;
}
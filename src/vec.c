#include "vec.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int capacity;
    unsigned int count;
    size_t elementSize;
} vec_info;

void vec_init(void* _refList, unsigned int _capacity, size_t _elementSize) {
    vec_info* info = malloc( sizeof(vec_info) + (_capacity * _elementSize));

    *((void**)_refList) = info + 1;

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

void vec_add(void* _refList, const void* _value) {
    vec_info* info = ((vec_info*)(*((void**)_refList))) - 1;

    if (info->count >= info->capacity)
    {
        info->capacity = info->capacity * 2;

        info = realloc( info,
            sizeof(vec_info) + (info->capacity * info->elementSize)
        );

        if (info == NULL)
        {
            printf("vec failed to realloc\n");
        }

        // if realloc moved the memory then we need to change where the _refList is pointing
        *((void**)_refList) = info + 1;
    }

    memcpy(
        (*(char**)_refList + (info->count * info->elementSize)),
        _value,
        info->elementSize
    );

    info->count++;
}

unsigned int vec_count(void* _refList) {
    vec_info* info = *(vec_info**)_refList - 1;

    return info->count;
}

int vec_find(void* _refList, void* _value) {
    vec_info* info = *(vec_info**)_refList - 1;

    for (int i = 0; i < info->count; i++)
        if (memcmp(*(char**)_refList + (i * info->elementSize), _value, info->elementSize) == 0)
            return i;

    return -1;
}

void* vec_end(void* _refList) {
    vec_info* info = *(vec_info**)_refList - 1;

    return *(char**)_refList + (info->count * info->elementSize);
}

void vec_bubble_sort(void* _refList, bool (*_compareFunc)(void*, void*)) {
    vec_info* info = *(vec_info**)_refList - 1;

    void* begin = *((void**)_refList);
    void* end = *(char**)_refList + (info->count * info->elementSize);
    bool swapped = true;
    char* temp = malloc(info->elementSize * sizeof(char));
    void* current = NULL;
    void* next = NULL;

    while(swapped) {
        swapped = false;
        current = begin;
        while(current != end) {
            next = (char*)current + info->elementSize;
            if (next != end) {
                if (_compareFunc(current, next)) {
                    swapped = true;
                    memcpy( temp, current, info->elementSize);
                    memcpy( current, next, info->elementSize);
                    memcpy( next, temp, info->elementSize);
                }
            }

            current = next;
        }
    }

    free(temp);
}

void vec_selection_sort(void* _refList, bool (*_compareFunc)(void*, void*)) {
    vec_info* info = (vec_info*)(*((void**)_refList)) - 1;

    char* temp = malloc(info->elementSize * sizeof(char));
    char* charList = *(char**)_refList;
    void* current = NULL;
    void* next = NULL;

    int i, j, minIdx;
    for (i = 0; i < info->count - 1; i++) {
        minIdx = i;
        for (j = i + 1; j < info->count; j++) {
            next = charList + (j * info->elementSize);
            current = charList + (minIdx * info->elementSize);
            if (_compareFunc(current, next)) {
                minIdx = j;
            }
        }

        if (minIdx != i) {
            current = charList + (i * info->elementSize);
            next = charList + (minIdx * info->elementSize);
            memcpy( temp, current, info->elementSize);
            memcpy( current, next, info->elementSize);
            memcpy( next, temp, info->elementSize);
        }
    }

    free(temp);
}

void vec_merge_sort(void* _refList, bool (*_compareFunc)(void*, void*)) {
    vec_info* info = *(vec_info**)_refList - 1;

    if (info->count < 2)
        return;

    unsigned int begin = 0;
    unsigned int end = info->count - 1;
    unsigned int mid = begin + (end - begin) / 2;

    _vec_merge_sort(_refList, begin, mid, _compareFunc);
    _vec_merge_sort(_refList, mid + 1, end, _compareFunc);
    _vec_merge(_refList, begin, mid, end, _compareFunc);
}

void _vec_merge_sort(void* _refList, int _begin, int _end, bool (*_compareFunc)(void*, void*)) {
    if (_begin >= _end)
        return;

    unsigned int mid = _begin + (_end - _begin) * 0.5;

    _vec_merge_sort(_refList, _begin, mid, _compareFunc);
    _vec_merge_sort(_refList, mid + 1, _end, _compareFunc);
    _vec_merge(_refList, _begin, mid, _end, _compareFunc);
}

void _vec_merge(void* _refList, int _left, int _mid, int _right, bool (*_compareFunc)(void*, void*)) {
    vec_info* info = *(vec_info**)_refList - 1;

    int const subArrayOneSize = _mid - _left + 1;
    int const subArrayTwoSize = _right - _mid;

    // Create temp arrays
    char* leftArray = malloc(info->elementSize * subArrayOneSize);
    char* rightArray = malloc(info->elementSize * subArrayTwoSize);

    // Copy data to temp arrays leftArray[] and rightArray[]
    memcpy( leftArray, *(char**)_refList + (_left * info->elementSize), subArrayOneSize * info->elementSize);
    memcpy( rightArray, *(char**)_refList + ((_mid+1) * info->elementSize), subArrayTwoSize * info->elementSize);

    int indexOfSubArrayOne = 0;
    int indexOfSubArrayTwo = 0;
    int indexOfMergedArray = _left;

    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOneSize && indexOfSubArrayTwo < subArrayTwoSize) {
        if (!_compareFunc(leftArray + (indexOfSubArrayOne * info->elementSize), rightArray + (indexOfSubArrayTwo * info->elementSize))) {
            memcpy(
                *(char**)_refList + (indexOfMergedArray * info->elementSize),
                leftArray + (indexOfSubArrayOne * info->elementSize),
                info->elementSize
            );
            indexOfSubArrayOne++;
        }
        else {
            memcpy(
                *(char**)_refList + (indexOfMergedArray * info->elementSize),
                rightArray + (indexOfSubArrayTwo * info->elementSize),
                info->elementSize
            );
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOneSize) {
        memcpy(
            *(char**)_refList + (indexOfMergedArray * info->elementSize),
            leftArray + (indexOfSubArrayOne * info->elementSize),
            info->elementSize
        );
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwoSize) {
        memcpy(
            *(char**)_refList + (indexOfMergedArray * info->elementSize),
            rightArray + (indexOfSubArrayTwo * info->elementSize),
            info->elementSize
        );
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }

    free(leftArray);
    free(rightArray);
}

bool DoubleAscending(void* a, void *b) {
    return *(double*)a > *(double*)b;
}

bool DoubleDescending(void* a, void *b) {
    return *(double*)a < *(double*)b;
}

bool FloatAscending(void* a, void *b) {
    return *(float*)a > *(float*)b;
}

bool FloatDescending(void* a, void *b) {
    return *(float*)a < *(float*)b;
}

bool IntAscending(void* a, void *b) {
    return *(int*)a > *(int*)b;
}

bool IntDescending(void* a, void *b) {
    return *(int*)a < *(int*)b;
}

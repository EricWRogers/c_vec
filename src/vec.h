#pragma once
#include <string.h>
#include <stdbool.h>

extern void vec_init(void* _refList, unsigned int _capacity, size_t _elementSize);
extern void vec_free(void* _refList);
extern void vec_clear(void* _refList);
extern void vec_add(void* _refList, const void* _value);
extern unsigned int vec_count(void* _refList);
extern int vec_find(void* _refList, void* _value);
extern void* vec_end(void* _refList);
extern void vec_grow(void* _refList);

extern void vec_bubble_sort(void* _refList, bool (*_compareFunc)(void*, void*));
extern void vec_selection_sort(void* _refList, bool (*_compareFunc)(void*, void*));
extern void MergeSort(void* _refList, bool (*_compareFunc)(void*, void*));

extern void _MergeSort(void* _refList, int _begin, int _end, bool (*_compareFunc)(void*, void*));
extern void _Merge(void* _refList, int _begin, int _mid, int _right, bool (*_compareFunc)(void*, void*));

// compare functions
extern bool DoubleAscending(void* a, void *b);
extern bool DoubleDescending(void* a, void *b);
extern bool FloatAscending(void* a, void *b);
extern bool FloatDescending(void* a, void *b);
extern bool IntAscending(void* a, void *b);
extern bool IntDescending(void* a, void *b);

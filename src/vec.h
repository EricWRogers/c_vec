#pragma once
#include <string.h>
#include <stdbool.h>

extern void vec_init(void* _refVec, unsigned int _capacity, size_t _elementSize);
extern void vec_free(void* _refVec);
extern void vec_clear(void* _refVec);
extern void vec_add(void* _refVec, void* _value);
extern void vec_remove_at(void* _refVec, unsigned int _index);
extern unsigned int vec_count(void* _refVec);
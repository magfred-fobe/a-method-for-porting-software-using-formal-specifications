//
// This library should be built into a a static lib that can be tested by the test code.
//
#pragma once
#include "../../test/lib_impl/LinkedListLib.h"
#include <vector>

extern "C" {
int32_t clib_init_list();
int32_t clib_empty(uint32_t identifier);
int32_t clib_next(uint32_t identifier, uint32_t index);
int32_t clib_insert_after(uint32_t identifier, uint32_t index, int value);
int32_t clib_head(uint32_t identifier);
int32_t clib_value_at_index(uintptr_t identifier, uintptr_t index);
int32_t clib_remove_after(uintptr_t identifier, uintptr_t index);
int32_t clib_remove(uintptr_t identifier, uintptr_t index);
int32_t clib_insert_head(uintptr_t identifier, int32_t value);
int32_t clib_swap(uintptr_t identifier_list_1, uintptr_t identifier_list_2);
int32_t clib_concatenate(uintptr_t identifier_list_1, uintptr_t identifier_list_2);
int32_t clib_remove_head(uintptr_t identifier);
int32_t clib_foreach_sum(uintptr_t identifier_list_1);
int32_t clib_foreach_from_sum(uintptr_t identifier_list_1, uintptr_t index_from);
}

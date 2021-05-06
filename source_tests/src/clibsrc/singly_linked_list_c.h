//
// Created by kali on 5/4/21.
//
#pragma once
extern "C" uintptr_t clib_init_list();
extern "C" int32_t clib_empty(uintptr_t identifier);
extern "C" int32_t clib_next(uintptr_t identifier, uintptr_t index);
extern "C" int32_t clib_insert_after(uintptr_t identifier, uintptr_t index, int value);
extern "C" int32_t clib_head(uintptr_t identifier);
extern "C" int32_t clib_value_at_index(uintptr_t identifier, uintptr_t index);
extern "C" int32_t clib_remove_after(uintptr_t identifier, uintptr_t index);
extern "C" int32_t clib_remove(uintptr_t identifier, uintptr_t index);
extern "C" int32_t clib_insert_head(uintptr_t identifier, int32_t value);
extern "C" int32_t clib_swap(uintptr_t identifier_list_1, uintptr_t identifier_list_2);
extern "C" int32_t clib_concatenate(uintptr_t identifier_list_1, uintptr_t identifier_list_2);
extern "C" int32_t clib_remove_head(uintptr_t identifier_list_1);
extern "C" int32_t clib_foreach_sum(uintptr_t identifier_list_1);
extern "C" int32_t clib_foreach_from_sum(uintptr_t identifier_list_1, uintptr_t index_from);
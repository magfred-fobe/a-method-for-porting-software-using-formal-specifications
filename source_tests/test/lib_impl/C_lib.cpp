//
// Created by Magnus on 5/4/21.
// This file implements the native API functions so that they can be used in the test.
//

#include "C_lib.h"

int32_t Clib::init_lib()  {
    return 0;
}

int32_t Clib::init_list() {
    return clib_init_list();
}

int32_t Clib::empty(uintptr_t identifier) {
    return clib_empty(identifier);
}

int32_t Clib::head(uintptr_t identifier) {
    return clib_head(identifier);
}

int32_t Clib::insert_head(uintptr_t identifier, int32_t value) {
    return clib_insert_head(identifier, value);
}

int32_t Clib::insert_after(uintptr_t identifier, uintptr_t index, int value) {
    return clib_insert_after(identifier, index, value);
}

int32_t Clib::next(uintptr_t identifier, uintptr_t index) {
    return clib_next(identifier, index);
}

int32_t Clib::value_at_index(uintptr_t identifier, uintptr_t index) {
  return clib_value_at_index(identifier, index);
}

int32_t Clib::remove_after(uintptr_t identifier, uintptr_t index) {
    return clib_remove_after(identifier, index);
}

int32_t Clib::remove(uintptr_t identifier, uintptr_t index) {
    return clib_remove(identifier, index);
}

int32_t Clib::swap(uintptr_t identifier_list_1, uintptr_t identifier_list_2) {
    return clib_swap(identifier_list_1, identifier_list_2);
}

int32_t Clib::concatenate(uintptr_t identifier_list_1, uintptr_t identifier_list_2) {
    return clib_concatenate(identifier_list_1, identifier_list_2);
}

int32_t Clib::remove_head(uintptr_t identifier) {
    clib_remove_head(identifier);
}

int32_t Clib::foreach_sum(uintptr_t identifier) {
    return clib_foreach_sum(identifier);
}

int32_t Clib::foreach_from_sum(uintptr_t identifier, uintptr_t index_from) {
    return clib_foreach_from_sum(identifier, index_from);
}

#include "LinkedListLib.h"
#include "rust_lib.h"

int32_t RustLib_Uns::init_lib()  {
    return rlib_uns_init_lib();
}

int32_t RustLib_Uns::init_list() {
    return rlib_uns_init_list();
}

int32_t RustLib_Uns::empty(uintptr_t identifier) {
    return rlib_uns_empty(identifier);
}

int32_t RustLib_Uns::head(uintptr_t identifier) {
    return rlib_uns_head(identifier);
}

int32_t RustLib_Uns::insert_head(uintptr_t identifier, int32_t value) {
    return rlib_uns_insert_head(identifier, value);
}

int32_t RustLib_Uns::insert_after(uintptr_t identifier, uintptr_t index, int32_t value) {
    return rlib_uns_insert_after(identifier, index, value);
}

int32_t RustLib_Uns::value_at_index(uintptr_t identifier, uintptr_t index) {
    return rlib_uns_value_at_index(identifier, index);
};

int32_t RustLib_Uns::remove(uintptr_t identifier, uintptr_t index) {
    return rlib_uns_remove(identifier, index);
}

int32_t RustLib_Uns::next(uintptr_t identifier, uintptr_t index) {
    return rlib_uns_next(identifier, index);
}

int32_t RustLib_Uns::remove_after(uintptr_t identifier, uintptr_t index) {
    return rlib_uns_remove_after(identifier, index);
}

int32_t RustLib_Uns::swap(uintptr_t identifier_list_1, uintptr_t identifier_list_2) {
    return rlib_uns_swap(identifier_list_1, identifier_list_2);
}

int32_t RustLib_Uns::concatenate(uintptr_t identifier_list_1, uintptr_t identifier_list_2) {
    return rlib_uns_concatenate(identifier_list_1, identifier_list_2);
}

int32_t RustLib_Uns::remove_head(uintptr_t identifier) {
    return rlib_uns_remove_head(identifier);
}

int32_t RustLib_Uns::foreach_sum(uintptr_t identifier) {
    return rlib_uns_foreach_sum(identifier);
}

int32_t RustLib_Uns::foreach_from_sum(uintptr_t identifier, uintptr_t index_from) {
    return rlib_uns_foreach_from_sum(identifier, index_from);
}

int32_t RustLib_Uns::print_list(uintptr_t identifier) {
    return rlib_uns_print_list(identifier);
}
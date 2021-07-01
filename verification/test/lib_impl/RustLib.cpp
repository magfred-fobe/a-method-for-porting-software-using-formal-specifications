#include "LinkedListLib.h"
#include "rust_lib.h"

int32_t RustLib::init_lib()  {
    return rlib_init_lib();
}

int32_t RustLib::init_list() {
    return rlib_init_list();
}

int32_t RustLib::empty(uintptr_t identifier) {
    return rlib_empty(identifier);
}


int32_t RustLib::head(uintptr_t identifier) {
    return rlib_head(identifier);
}

int32_t RustLib::insert_head(uintptr_t identifier, int32_t value) {
    return rlib_insert_head(identifier, value);
}

int32_t RustLib::insert_after(uintptr_t identifier, uintptr_t index, int32_t value) {
    return rlib_insert_after(identifier, index, value);
}

int32_t RustLib::value_at_index(uintptr_t identifier, uintptr_t index) {
    return rlib_value_at_index(identifier, index);
};

int32_t RustLib::remove(uintptr_t identifier, uintptr_t index) {
    return rlib_remove(identifier, index);
}

int32_t RustLib::next(uintptr_t identifier, uintptr_t index) {
    return rlib_next(identifier, index);
}

int32_t RustLib::remove_after(uintptr_t identifier, uintptr_t index) {
    return rlib_remove_after(identifier, index);
}

int32_t RustLib::swap(uintptr_t identifier_list_1, uintptr_t identifier_list_2) {
    return rlib_swap(identifier_list_1, identifier_list_2);
}

int32_t RustLib::concatenate(uintptr_t identifier_list_1, uintptr_t identifier_list_2) {
    return rlib_concatenate(identifier_list_1, identifier_list_2);
}

int32_t RustLib::remove_head(uintptr_t identifier) {
    return rlib_remove_head(identifier);
}

int32_t RustLib::foreach_sum(uintptr_t identifier) {
    return rlib_foreach_sum(identifier);
}

int32_t RustLib::foreach_from_sum(uintptr_t identifier, uintptr_t index_from) {
    return rlib_foreach_from_sum(identifier, index_from);
};
int32_t RustLib::print_list(uintptr_t identifier) {
    return rlib_print_list(identifier);
};
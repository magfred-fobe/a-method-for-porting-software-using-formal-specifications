#include "LinkedListLib.h"
#include "rust_lib.h"

int32_t RustLib::init_lib()  {
    return 0;
}

int32_t RustLib::init_list() {
    return rlib_init_list();
}

int32_t RustLib::empty(uint32_t identifier) {
    return rlib_empty(identifier);
}

int32_t RustLib::head(uint32_t identifier) {
    return rlib_head(identifier);
}

int32_t RustLib::insert_head(uint32_t identifier, int32_t value) {
    return rlib_insert_head(identifier, value);
}

int32_t RustLib::insert_after(uint32_t identifier, uintptr_t index, int32_t value) {
    return rlib_insert_after(identifier, index, value);
}

int32_t RustLib::value_at_index(uintptr_t identifier, uintptr_t index) {
    return rlib_value_at_index(identifier, index);
};

int32_t RustLib::remove(uintptr_t identifier, uintptr_t index) {
    return rlib_remove(identifier, index);
};


#include "LinkedListLib.h"
#include "rust_lib.h"
int32_t RustLib::init_lib() {
    return 0;
}
int32_t RustLib::init_list() {
    return rlib_init_list();
}

int32_t RustLib::insert_head(uint32_t identifier, int32_t value) {
    return rlib_insert_head(identifier, value);
}
int32_t RustLib::insert_after(uint32_t identifier, uintptr_t index, int32_t value) {
    return rlib_insert_after(identifier, index, value);
}



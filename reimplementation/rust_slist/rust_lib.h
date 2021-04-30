#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <new>

extern "C" {

int32_t rlib_init_list();

int32_t rlib_empty(uint32_t identifier);

///TODO: head()/first() should be implemented
int32_t rlib_head(uint32_t identifier);

int32_t rlib_insert_head(uint32_t identifier, int32_t value);

int32_t rlib_insert_after(uint32_t identifier, uintptr_t index, int32_t value);

int32_t rlib_remove(uint32_t identifier, uintptr_t index);

int32_t rlib_remove_after(uint32_t identifier, uintptr_t index);

int32_t rlib_remove_head(uint32_t identifier);

///TODO: yeah, what to do?
int32_t rlib_remove_prevptr(uint32_t identifier, uint32_t index);

int32_t rlib_swap(uint32_t identifier_list_1, uint32_t identifier_list2);

int32_t rlib_concatenate(uint32_t identifier_list_1, uint32_t identifier_list2);

///TODO: yeah, what to do?
int32_t rlib_foreach(uint32_t identifier_list_1);

///TODO: yeah, what to do?
int32_t rlib_foreach_from(uint32_t identifier_list_1);

} // extern "C"

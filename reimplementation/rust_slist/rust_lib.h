#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <new>

extern "C" {

int32_t rlib_init_list();

int32_t rlib_empty(uintptr_t identifier);

///TODO: head()/first() should be implemented
int32_t rlib_head(uintptr_t identifier);

int32_t rlib_insert_head(uintptr_t identifier, int32_t value);

int32_t rlib_insert_after(uintptr_t identifier, uintptr_t index, int32_t value);

int32_t rlib_remove(uintptr_t identifier, uintptr_t index);

///TODO: use actual remove_after impl when done
int32_t rlib_remove_after(uintptr_t identifier, uintptr_t index);

int32_t rlib_remove_head(uintptr_t identifier);

///TODO: yeah, what to do?
int32_t rlib_remove_prevptr(uintptr_t identifier, uintptr_t index);

int32_t rlib_swap(uintptr_t identifier_list_1, uintptr_t identifier_list_2);

int32_t rlib_concatenate(uintptr_t identifier_list_1, uintptr_t identifier_list_2);

int32_t rlib_value_at_index(uintptr_t identifier, uintptr_t index);

///TODO: yeah, what to do?
int32_t rlib_foreach_sum(uintptr_t identifier_list_1);

int32_t rlib_foreach_from_sum(uintptr_t identifier_list_1);

} // extern "C"

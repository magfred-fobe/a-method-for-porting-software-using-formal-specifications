#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <new>

extern "C" {

int32_t rlib_init_list();

int32_t rlib_insert_head(uint32_t identifier, int32_t value);

int32_t rlib_insert_after(uint32_t identifier, uintptr_t index, int32_t value);

} // extern "C"

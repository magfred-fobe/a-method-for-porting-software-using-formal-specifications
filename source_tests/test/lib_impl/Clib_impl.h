//
// This library should be built into a a static lib that can be tested by the test code.
//
#pragma once
#include "../../test/lib_impl/LinkedListLib.h";
#include <vector>


class Clib : public LinkedListLib {

public:
    int32_t init_lib() override;
    int32_t init_list() override;
    int32_t insert_head(uint32_t identifier, int32_t value) override;
    int32_t empty(uint32_t identifier) override;
    int32_t head(uint32_t identifier) override;
    int32_t insert_after(uint32_t identifier, uintptr_t index, int32_t value) override;
};


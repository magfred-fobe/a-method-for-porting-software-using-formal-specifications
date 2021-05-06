//
// Created by kali on 4/29/21.
//
/**
 * Each native library must implement this class
 */
#pragma once
#include <cstdint>
class LinkedListLib {
public:
    virtual int32_t init_lib() = 0;
    virtual int32_t init_list() = 0;
    virtual int32_t insert_head(uint32_t identifier, int32_t value) = 0;
    virtual int32_t empty(uint32_t identifier) = 0;
    virtual int32_t head(uint32_t identifier) = 0;
    virtual int32_t insert_after(uint32_t identifier, uintptr_t index, int32_t value) = 0;
    virtual int32_t value_at_index(uintptr_t identifier, uintptr_t index) = 0;
    int32_t list_index;
};

class RustLib : public LinkedListLib {
public:
    int32_t init_lib() override;
    int32_t init_list() override;
    int32_t insert_head(uint32_t identifier, int32_t value) override;
    int32_t empty(uint32_t identifier) override;
    int32_t head(uint32_t identifier) override;
    int32_t insert_after(uint32_t identifier, uintptr_t index, int32_t value) override;
    int32_t value_at_index(uintptr_t identifier, uintptr_t index) override;
};

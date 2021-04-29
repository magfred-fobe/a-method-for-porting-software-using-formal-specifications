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
    virtual int32_t insert_after(uint32_t identifier, uintptr_t index, int32_t value) = 0;
};

class RustLib : public LinkedListLib {
public:
    virtual int32_t init_lib();
    virtual int32_t init_list();
    virtual int32_t insert_head(uint32_t identifier, int32_t value);
    virtual int32_t insert_after(uint32_t identifier, uintptr_t index, int32_t value);
};

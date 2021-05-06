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
    virtual int32_t empty(uintptr_t identifier) = 0;
    virtual int32_t next(uintptr_t identifier, uintptr_t index) = 0;
    virtual int32_t insert_after(uintptr_t identifier, uintptr_t index, int value) = 0;
    virtual int32_t head(uintptr_t identifier) = 0;
    virtual int32_t value_at_index(uintptr_t identifier, uintptr_t index) = 0;
    virtual int32_t remove_after(uintptr_t identifier, uintptr_t index) = 0;
    virtual int32_t remove(uintptr_t identifier, uintptr_t index) = 0;
    virtual int32_t insert_head(uintptr_t identifier, int32_t value) = 0;
    virtual int32_t swap(uintptr_t identifier_list_1, uintptr_t identifier_list_2) = 0;
    virtual int32_t concatenate(uintptr_t identifier_list_1, uintptr_t identifier_list_2) = 0;
    virtual int32_t remove_head(uintptr_t identifier) = 0;
    virtual int32_t foreach_sum(uintptr_t identifier) = 0;
    virtual int32_t foreach_from_sum(uintptr_t identifier, uintptr_t index_from) = 0;
    int32_t list_index;
};

class RustLib : public LinkedListLib {
public:
    int32_t init_lib() override;
    int32_t init_list() override;
    int32_t empty(uintptr_t identifier) override;
    int32_t next(uintptr_t identifier, uintptr_t index) override;
    int32_t insert_after(uintptr_t identifier, uintptr_t index, int value) override;
    int32_t head(uintptr_t identifier) override;
    int32_t value_at_index(uintptr_t identifier, uintptr_t index) override;
    int32_t remove_after(uintptr_t identifier, uintptr_t index) override;
    int32_t remove(uintptr_t identifier, uintptr_t index) override;
    int32_t insert_head(uintptr_t identifier, int32_t value) override;
    int32_t swap(uintptr_t identifier_list_1, uintptr_t identifier_list_2) override;
    int32_t concatenate(uintptr_t identifier_list_1, uintptr_t identifier_list_2) override;
    int32_t remove_head(uintptr_t identifier) override;
    int32_t foreach_sum(uintptr_t identifier) override;
    int32_t foreach_from_sum(uintptr_t identifier, uintptr_t index_from) override;
};

class Clib : public LinkedListLib {
public:
    int32_t init_lib() override;
    int32_t init_list() override;
    int32_t empty(uintptr_t identifier) override;
    int32_t next(uintptr_t identifier, uintptr_t index) override;
    int32_t insert_after(uintptr_t identifier, uintptr_t index, int value) override;
    int32_t head(uintptr_t identifier) override;
    int32_t value_at_index(uintptr_t identifier, uintptr_t index) override;
    int32_t remove_after(uintptr_t identifier, uintptr_t index) override;
    int32_t remove(uintptr_t identifier, uintptr_t index) override;
    int32_t insert_head(uintptr_t identifier, int32_t value) override;
    int32_t swap(uintptr_t identifier_list_1, uintptr_t identifier_list_2) override;
    int32_t concatenate(uintptr_t identifier_list_1, uintptr_t identifier_list_2) override;
    int32_t remove_head(uintptr_t identifier) override;
    int32_t foreach_sum(uintptr_t identifier) override;
    int32_t foreach_from_sum(uintptr_t identifier_list_1, uintptr_t index_from) override;
};
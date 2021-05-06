//
// Created by kali on 5/4/21.
//

#include <vector>
#include "../queue_impl.h"
#include "singly_linked_list_c.h"
#include <iostream>
std::vector<mySinglyLinkedListHead*> lists;

//LEFT:
//void SLIST_REMOVE_PREVPTR_impl(IntegerSLISTEntry**, IntegerSLISTEntry*);
//IntegerSLISTEntry* SLIST_END_impl(mySinglyLinkedListHead*);

uintptr_t clib_init_list() {
    auto index = lists.size();
    auto head = new mySinglyLinkedListHead();
    SLIST_INIT_impl(head);
    lists.push_back(head);
    return index;
}

int32_t clib_empty(uintptr_t identifier) {
    auto head = lists.at(identifier);
    return SLIST_EMPTY_impl(head);
}

int32_t clib_next(uintptr_t identifier, uintptr_t index) {
    auto head = lists.at(identifier);
    auto prev = SLIST_FIRST_impl(head);
    if(prev->entries.sle_next == nullptr) {
        return -1;
    }
    return prev->entries.sle_next->data;
}

int32_t clib_insert_after(uintptr_t identifier, uintptr_t index, int value) {
    auto head = lists.at(identifier);
    auto element_before_insertion = SLIST_FIRST_impl(head);
    for(int i = 0; i < index; i++)
        element_before_insertion = SLIST_NEXT_impl(element_before_insertion);

    auto element_to_be_inserted = new IntegerSLISTEntry();
    element_to_be_inserted->data = value;
    SLIST_INSERT_AFTER_impl(element_before_insertion, element_to_be_inserted);
};

int32_t clib_head(uintptr_t identifier)  {
    auto list = lists.at(identifier);
    return SLIST_FIRST_impl(list)->data;
};

int32_t clib_value_at_index(uintptr_t identifier, uintptr_t index)  {
    auto head = lists.at(identifier);
    auto element = SLIST_FIRST_impl(head);
    for(int i = 0; i < index; i++) {
        if(element == nullptr) {
            return -1;
        }
        element = SLIST_NEXT_impl(element);

    }
    if (element == nullptr) {
        return -1;
    }
    return element->data;
};

int32_t clib_remove_after(uintptr_t identifier, uintptr_t index) {
    auto head = lists.at(identifier);
    auto element_before_removal = SLIST_FIRST_impl(head);
    for(int i = 0; i < index; i++){
        if(element_before_removal == nullptr) {
            return -1;
        }
        element_before_removal = SLIST_NEXT_impl(element_before_removal);
    }
    if (element_before_removal == nullptr || element_before_removal->entries.sle_next == nullptr) {
        return -1;
    }
    SLIST_REMOVE_AFTER_impl(element_before_removal);
    return 0;
}

int32_t clib_remove(uintptr_t identifier, uintptr_t index) {
    auto head = lists.at(identifier);
    auto element_before_removal = SLIST_FIRST_impl(head);
    for(int i = 0; i < index; i++)
        element_before_removal = SLIST_NEXT_impl(element_before_removal);
    if (element_before_removal == nullptr) {
        return -1;
    }
    SLIST_REMOVE_impl(head, element_before_removal);
    return 0;
}

int32_t clib_insert_head(uintptr_t identifier, int32_t value) {
    auto head = lists.at(identifier);
    auto element = new IntegerSLISTEntry();
    element->data = value;
    SLIST_INSERT_HEAD_impl(head, element);
    return 0;
}

int32_t clib_swap(uintptr_t identifier_list_1, uintptr_t identifier_list_2) {
    auto head_1 = lists.at(identifier_list_1);
    auto head_2 = lists.at(identifier_list_2);
    SLIST_SWAP_impl(head_1, head_2);
    return 0;
}

int32_t clib_concatenate(uintptr_t identifier_list_1, uintptr_t identifier_list_2) {
    auto head_1 = lists.at(identifier_list_1);
    auto head_2 = lists.at(identifier_list_2);
    SLIST_CONCAT_impl(head_1, head_2);
    return 0;
}

int32_t clib_remove_head(uintptr_t identifier) {
    auto head = lists.at(identifier);
    SLIST_REMOVE_HEAD_impl(head);
    return 0;
}

int32_t clib_foreach_sum(uintptr_t identifier_list_1) {
    auto head = lists.at(identifier_list_1);
    IntegerSLISTEntry *entry;
    int sum = 0;
    SLIST_FOREACH(entry, head, entries) {
        sum += entry->data;
    }
    return sum;
}

int32_t clib_foreach_from_sum(uintptr_t identifier_list_1, uintptr_t index_from) {
    auto head = lists.at(identifier_list_1);
    IntegerSLISTEntry *entry = SLIST_FIRST_impl(head);
    for (int current_index = 0; current_index <  index_from; current_index++) {
        entry = entry->entries.sle_next;
    }
    int sum = 0;
    SLIST_FOREACH_FROM(entry, head, entries) {
        sum += entry->data;
    }
    return sum;
}
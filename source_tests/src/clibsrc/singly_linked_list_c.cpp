//
// Created by kali on 5/4/21.
//

#include <vector>
#include "../queue_impl.h"
#include <iostream>
#include "../queue_impl.h";
std::vector<mySinglyLinkedListHead*> lists;

uint32_t clib_init_list() {
    auto index = lists.size();
    auto head = new mySinglyLinkedListHead();
    SLIST_INIT_impl(head);
    lists.push_back(head);
    std::cout << "a new List should be created!";
    return index;
}
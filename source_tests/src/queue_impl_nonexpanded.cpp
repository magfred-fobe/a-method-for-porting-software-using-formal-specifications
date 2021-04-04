#include "queue_impl.h"

//We want to get metrics on coverage, but macros themselves can tell us about coverage
//Inline functions would be more like a macro. Can easily be done, but not when separate definition declaration

void STAILQ_INIT_impl(mySTAILQueueHead* head) {
    STAILQ_INIT(head);
}

bool STAILQ_EMPTY_impl(mySTAILQueueHead *head) {
    return STAILQ_EMPTY(head);
}

void STAILQ_INSERT_HEAD_impl(mySTAILQueueHead* head, IntegerSTAILQueueNode* entry) {
    STAILQ_INSERT_HEAD(head, entry, links);
}

void STAILQ_REMOVE_HEAD_impl(mySTAILQueueHead* head) {
    STAILQ_REMOVE_HEAD(head, links);
}

void STAILQ_SWAP_impl(mySTAILQueueHead* head1,mySTAILQueueHead* head2) {
    STAILQ_SWAP(head1, head2, IntegerSTAILQueueNode);
}

//LIST
void SLIST_INIT_impl(mySinglyLinkedListHead* head) {
    SLIST_INIT(head);
}
IntegerSLISTEntry* SLIST_FIRST_impl(mySinglyLinkedListHead* head) {
    return SLIST_FIRST(head);
}

void SLIST_CONCAT_impl(mySinglyLinkedListHead* head1, mySinglyLinkedListHead* head2) {
    SLIST_CONCAT(head1, head2, IntegerSLISTEntry, entries);
}

bool SLIST_EMPTY_impl(mySinglyLinkedListHead* head) {
    return SLIST_EMPTY(head);
}

void SLIST_INSERT_AFTER_impl(IntegerSLISTEntry* slistelm, IntegerSLISTEntry* elm) {
    SLIST_INSERT_AFTER(slistelm, elm, entries);
}

void SLIST_INSERT_HEAD_impl(mySinglyLinkedListHead* head,IntegerSLISTEntry* elm) {
    SLIST_INSERT_HEAD(head, elm, entries);
}

void SLIST_REMOVE_impl(mySinglyLinkedListHead* head, IntegerSLISTEntry* elm) {
    SLIST_REMOVE(head, elm, IntegerSLISTEntry, entries);
}

void SLIST_REMOVE_AFTER_impl(IntegerSLISTEntry* elm) {
    SLIST_REMOVE_AFTER(elm, entries);
}

void SLIST_REMOVE_HEAD_impl(mySinglyLinkedListHead* head) {
    SLIST_REMOVE_HEAD(head, entries);
}

void SLIST_REMOVE_PREVPTR_impl(IntegerSLISTEntry** prevp, IntegerSLISTEntry* elm) {
    SLIST_REMOVE_PREVPTR(prevp, elm, entries);
}
void SLIST_SWAP_impl(mySinglyLinkedListHead* head1,mySinglyLinkedListHead* head2) {
    SLIST_SWAP(head1, head2, IntegerSLISTEntry);
}

mySinglyLinkedListHead* SLIST_END_impl(mySinglyLinkedListHead *head) {
    return SLIST_END(head);
}


//FIELD == entries
//TYPE = IntegerSLISTEntry
//elm = IntegerSLISTEntry
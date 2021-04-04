//
// Created by Magnus on 3/31/21.
//
//#include "queue.h"
#include "queue_impl.h"
#include <cstddef>


void STAILQ_INIT_impl(mySTAILQueueHead* head) {
    do { (((head))->stqh_first) = NULL; (head)->stqh_last = &(((head))->stqh_first); } while (0);
}

bool STAILQ_EMPTY_impl(mySTAILQueueHead *head) {
    return ((head)->stqh_first == NULL);
}

void STAILQ_INSERT_HEAD_impl(mySTAILQueueHead* head, IntegerSTAILQueueNode* entry) {
    do { if (((((entry))->links.stqe_next) = (((head))->stqh_first)) == NULL) (head)->stqh_last = &(((entry))->links.stqe_next); (((head))->stqh_first) = (entry); } while (0);
}

void STAILQ_REMOVE_HEAD_impl(mySTAILQueueHead* head) {
    do { if (((((head))->stqh_first) = (((((head))->stqh_first))->links.stqe_next)) == NULL) (head)->stqh_last = &(((head))->stqh_first); } while (0);
}

void STAILQ_SWAP_impl(mySTAILQueueHead* head1,mySTAILQueueHead* head2) {
    do { IntegerSTAILQueueNode *swap_first = ((head1)->stqh_first); IntegerSTAILQueueNode **swap_last = (head1)->stqh_last; ((head1)->stqh_first) = ((head2)->stqh_first); (head1)->stqh_last = (head2)->stqh_last; ((head2)->stqh_first) = swap_first; (head2)->stqh_last = swap_last; if (((head1)->stqh_first == NULL)) (head1)->stqh_last = &((head1)->stqh_first); if (((head2)->stqh_first == NULL)) (head2)->stqh_last = &((head2)->stqh_first); } while (0);
}

//LIST
void SLIST_INIT_impl(mySinglyLinkedListHead* head) {
    do { (((head))->slh_first) = NULL; } while (0);
}
IntegerSLISTEntry* SLIST_FIRST_impl(mySinglyLinkedListHead* head) {
    return ((head)->slh_first);
}

void SLIST_CONCAT_impl(mySinglyLinkedListHead* head1, mySinglyLinkedListHead* head2) {
    do { IntegerSLISTEntry *curelm = ((head1)->slh_first); if (curelm == NULL) { if ((((head1)->slh_first) = ((head2)->slh_first)) != NULL) do { (((head2))->slh_first) = NULL; } while (0); } else if (((head2)->slh_first) != NULL) { while (((curelm)->entries.sle_next) != NULL) curelm = ((curelm)->entries.sle_next); ((curelm)->entries.sle_next) = ((head2)->slh_first); do { (((head2))->slh_first) = NULL; } while (0); } } while (0);
}

bool SLIST_EMPTY_impl(mySinglyLinkedListHead* head) {
    return ((head)->slh_first == NULL);
}

void SLIST_INSERT_AFTER_impl(IntegerSLISTEntry* slistelm, IntegerSLISTEntry* elm) {
    do { (((elm))->entries.sle_next) = (((slistelm))->entries.sle_next); (((slistelm))->entries.sle_next) = (elm); } while (0);
}

void SLIST_INSERT_HEAD_impl(mySinglyLinkedListHead* head,IntegerSLISTEntry* elm) {
    do { (((elm))->entries.sle_next) = (((head))->slh_first); (((head))->slh_first) = (elm); } while (0);
}

void SLIST_REMOVE_impl(mySinglyLinkedListHead* head, IntegerSLISTEntry* elm) {
    do { ; if ((((head))->slh_first) == (elm)) { do { ((((head)))->slh_first) = ((((((head)))->slh_first))->entries.sle_next); } while (0); } else { IntegerSLISTEntry *curelm = ((head)->slh_first); while (((curelm)->entries.sle_next) != (elm)) curelm = ((curelm)->entries.sle_next); do { ((curelm)->entries.sle_next) = ((((curelm)->entries.sle_next))->entries.sle_next); } while (0); } ; } while (0);
}

void SLIST_REMOVE_AFTER_impl(IntegerSLISTEntry* elm) {
    do { ((elm)->entries.sle_next) = ((((elm)->entries.sle_next))->entries.sle_next); } while (0);
}

void SLIST_REMOVE_HEAD_impl(mySinglyLinkedListHead* head) {
    do { (((head))->slh_first) = (((((head))->slh_first))->entries.sle_next); } while (0);
}

void SLIST_REMOVE_PREVPTR_impl(IntegerSLISTEntry** prevp, IntegerSLISTEntry* elm) {
    do { ; *(prevp) = ((elm)->entries.sle_next); ; } while (0);
}
void SLIST_SWAP_impl(mySinglyLinkedListHead* head1,mySinglyLinkedListHead* head2) {
    do { IntegerSLISTEntry *swap_first = ((head1)->slh_first); ((head1)->slh_first) = ((head2)->slh_first); ((head2)->slh_first) = swap_first; } while (0);
}

mySinglyLinkedListHead* SLIST_END_impl(mySinglyLinkedListHead *head) {
    return NULL;
}

//
// Created by Magnus on 3/31/21.
//
//#include "queue.h"
#include "queue_impl.h"
#include <cstddef>

//Singly linked list
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

//Singly Linked Tail Queue
mySTAILQueueHead STAILQ_HEAD_INITIALIZER_impl(mySTAILQueueHead* head){
    return { NULL, &(*head).stqh_first };
}

void STAILQ_CONCAT_impl(mySTAILQueueHead* head1,mySTAILQueueHead* head2){
    do { if (!(((head2))->stqh_first == NULL)) { *(head1)->stqh_last = (head2)->stqh_first; (head1)->stqh_last = (head2)->stqh_last; do { ((((head2)))->stqh_first) = NULL; ((head2))->stqh_last = &((((head2)))->stqh_first); } while (0); } } while (0);
}

bool STAILQ_EMPTY_impl(mySTAILQueueHead *head) {
    return ((head)->stqh_first == NULL);
}

IntegerSTAILQueueNode* STAILQ_FIRST_impl(mySTAILQueueHead *head){
    return ((head)->stqh_first);
}

void STAILQ_INIT_impl(mySTAILQueueHead* head) {
    do { (((head))->stqh_first) = NULL; (head)->stqh_last = &(((head))->stqh_first); } while (0);
}

void STAILQ_INSERT_AFTER_impl(mySTAILQueueHead* head, IntegerSTAILQueueNode* tqelm,IntegerSTAILQueueNode* elm){
    do { if (((((elm))->entries.stqe_next) = (((tqelm))->entries.stqe_next)) == NULL) (head)->stqh_last = &(((elm))->entries.stqe_next); (((tqelm))->entries.stqe_next) = (elm); } while (0);
}

void STAILQ_INSERT_HEAD_impl(mySTAILQueueHead* head, IntegerSTAILQueueNode* elm){
    do { if (((((elm))->entries.stqe_next) = (((head))->stqh_first)) == NULL) (head)->stqh_last = &(((elm))->entries.stqe_next); (((head))->stqh_first) = (elm); } while (0);
}

void STAILQ_INSERT_TAIL_impl(mySTAILQueueHead* head,IntegerSTAILQueueNode* elm){
    do { (((elm))->entries.stqe_next) = NULL; *(head)->stqh_last = (elm); (head)->stqh_last = &(((elm))->entries.stqe_next); } while (0);
}

IntegerSTAILQueueNode* STAILQ_LAST_impl(mySTAILQueueHead* head, IntegerSTAILQueueNode){
    return ((((head))->stqh_first == NULL) ? NULL : ({ const volatile __typeof(((IntegerSTAILQueueNode *)0)->entries.stqe_next) *__x = ((head)->stqh_last); ((IntegerSTAILQueueNode *)(uintptr_t)(const volatile void *)((const volatile char *)__x - __builtin_offsetof(IntegerSTAILQueueNode, entries.stqe_next)));}));
}

IntegerSTAILQueueNode* STAILQ_NEXT_impl(IntegerSTAILQueueNode* elm){
    return ((elm)->entries.stqe_next);
}

void STAILQ_REMOVE_impl(mySTAILQueueHead* head,IntegerSTAILQueueNode* elm, IntegerSTAILQueueNode){
    do { ; if ((((head))->stqh_first) == (elm)) { do { if ((((((head)))->stqh_first) = ((((((head)))->stqh_first))->entries.stqe_next)) == NULL) ((head))->stqh_last = &((((head)))->stqh_first); } while (0); } else { IntegerSTAILQueueNode *curelm = ((head)->stqh_first); while (((curelm)->entries.stqe_next) != (elm)) curelm = ((curelm)->entries.stqe_next); do { if ((((curelm)->entries.stqe_next) = ((((curelm)->entries.stqe_next))->entries.stqe_next)) == NULL) (head)->stqh_last = &(((curelm))->entries.stqe_next); } while (0); } ; } while (0);
}

void STAILQ_REMOVE_AFTER_impl(mySTAILQueueHead* head,IntegerSTAILQueueNode* elm){
    do { if ((((elm)->entries.stqe_next) = ((((elm)->entries.stqe_next))->entries.stqe_next)) == NULL) (head)->stqh_last = &(((elm))->entries.stqe_next); } while (0);
}

void STAILQ_REMOVE_HEAD_impl(mySTAILQueueHead* head) {
    do { if (((((head))->stqh_first) = (((((head))->stqh_first))->entries.stqe_next)) == NULL) (head)->stqh_last = &(((head))->stqh_first); } while (0);
}

void STAILQ_SWAP_impl(mySTAILQueueHead* head1,mySTAILQueueHead* head2, IntegerSTAILQueueNode) {
    do { IntegerSTAILQueueNode *swap_first = ((head1)->stqh_first); IntegerSTAILQueueNode **swap_last = (head1)->stqh_last; ((head1)->stqh_first) = ((head2)->stqh_first); (head1)->stqh_last = (head2)->stqh_last; ((head2)->stqh_first) = swap_first; (head2)->stqh_last = swap_last; if (((head1)->stqh_first == NULL)) (head1)->stqh_last = &((head1)->stqh_first); if (((head2)->stqh_first == NULL)) (head2)->stqh_last = &((head2)->stqh_first); } while (0);
}

IntegerSTAILQueueNode* STAILQ_END_impl(mySTAILQueueHead* head){
    return NULL;
}


//Doubly linked list
void LIST_CONCAT_impl(myLISTHead* head1, myLISTHead* head2) {
    do { IntegerLISTEntry *curelm = ((head1)->lh_first); if (curelm == NULL) { if ((((head1)->lh_first) = ((head2)->lh_first)) != NULL) { ((head2)->lh_first)->links.le_prev = &(((head1))->lh_first); do { (((head2))->lh_first) = NULL; } while (0); } } else if (((head2)->lh_first) != NULL) { while (((curelm)->links.le_next) != NULL) curelm = ((curelm)->links.le_next); ((curelm)->links.le_next) = ((head2)->lh_first); ((head2)->lh_first)->links.le_prev = &((curelm)->links.le_next); do { (((head2))->lh_first) = NULL; } while (0); } } while (0);
}

bool LIST_EMPTY_impl(myLISTHead* head) {
    return ((head)->lh_first == NULL);
}

IntegerLISTEntry* LIST_FIRST_impl(myLISTHead* head) {
    return ((head)->lh_first);
}

void LIST_INIT_impl(myLISTHead* head) {
    do { (((head))->lh_first) = NULL; } while (0);
}
void LIST_INSERT_AFTER_impl(IntegerLISTEntry* listelm, IntegerLISTEntry* elm) {
    do { ; if (((((elm))->links.le_next) = (((listelm))->links.le_next)) != NULL) (((listelm))->links.le_next)->links.le_prev = &(((elm))->links.le_next); (((listelm))->links.le_next) = (elm); (elm)->links.le_prev = &(((listelm))->links.le_next); } while (0);
}
void LIST_INSERT_BEFORE_impl(IntegerLISTEntry* listelm, IntegerLISTEntry* elm) {
    do { ; (elm)->links.le_prev = (listelm)->links.le_prev; (((elm))->links.le_next) = (listelm); *(listelm)->links.le_prev = (elm); (listelm)->links.le_prev = &(((elm))->links.le_next); } while (0);
}
void LIST_INSERT_HEAD_impl(myLISTHead* head,IntegerLISTEntry* elm) {
    do { ; if (((((elm))->links.le_next) = (((head))->lh_first)) != NULL) (((head))->lh_first)->links.le_prev = &(((elm))->links.le_next); (((head))->lh_first) = (elm); (elm)->links.le_prev = &(((head))->lh_first); } while (0);
}

IntegerLISTEntry* LIST_NEXT_impl(IntegerLISTEntry* elm) {
    return ((elm)->links.le_next);
}

IntegerLISTEntry* LIST_PREV_impl(IntegerLISTEntry* elm, myLISTHead* head) {
    return ((elm)->links.le_prev == &(((head))->lh_first) ? NULL : ({ const volatile __typeof(((IntegerLISTEntry *)0)->links.le_next) *__x = ((elm)->links.le_prev); ((IntegerLISTEntry *)(uintptr_t)(const volatile void *)((const volatile char *)__x - __builtin_offsetof(IntegerLISTEntry, links.le_next)));}));
}

void LIST_REMOVE_impl(IntegerLISTEntry* elm) {
    do { ; ; ; ; if ((((elm))->links.le_next) != NULL) (((elm))->links.le_next)->links.le_prev = (elm)->links.le_prev; *(elm)->links.le_prev = (((elm))->links.le_next); ; ; } while (0);
}
void LIST_SWAP_impl(myLISTHead* head1, myLISTHead* head2) {
    do { IntegerLISTEntry *swap_tmp = ((head1)->lh_first); (((head1))->lh_first) = (((head2))->lh_first); (((head2))->lh_first) = swap_tmp; if ((swap_tmp = (((head1))->lh_first)) != NULL) swap_tmp->links.le_prev = &(((head1))->lh_first); if ((swap_tmp = (((head2))->lh_first)) != NULL) swap_tmp->links.le_prev = &(((head2))->lh_first); } while (0);
}

IntegerLISTEntry* LIST_END_impl(myLISTHead* head) {
    return NULL;
}




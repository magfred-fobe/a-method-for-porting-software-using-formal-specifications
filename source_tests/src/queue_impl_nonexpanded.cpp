#include "queue_impl.h"

//We want to get metrics on coverage, but macros themselves can tell us about coverage
//Inline functions would be more like a macro. Can easily be done, but not when separate definition declaration


//Singly linked list
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

//Singly Linked Tail Queue
mySTAILQueueHead STAILQ_HEAD_INITIALIZER_impl(mySTAILQueueHead* head){
    return STAILQ_HEAD_INITIALIZER(*head);
}

void STAILQ_CONCAT_impl(mySTAILQueueHead* head1,mySTAILQueueHead* head2){
    STAILQ_CONCAT(head1, head2);
}

bool STAILQ_EMPTY_impl(mySTAILQueueHead *head) {
    return STAILQ_EMPTY(head);
}

IntegerSTAILQueueNode* STAILQ_FIRST_impl(mySTAILQueueHead *head){
    return STAILQ_FIRST(head);
}

void STAILQ_INIT_impl(mySTAILQueueHead* head) {
    STAILQ_INIT(head);
}

void STAILQ_INSERT_AFTER_impl(mySTAILQueueHead* head, IntegerSTAILQueueNode* tqelm,IntegerSTAILQueueNode* elm){
    STAILQ_INSERT_AFTER(head, tqelm, elm, entries);
}

void STAILQ_INSERT_HEAD_impl(mySTAILQueueHead* head, IntegerSTAILQueueNode* elm){
    STAILQ_INSERT_HEAD(head, elm, entries);
}

void STAILQ_INSERT_TAIL_impl(mySTAILQueueHead* head,IntegerSTAILQueueNode* elm){
    STAILQ_INSERT_TAIL(head, elm, entries);
}

IntegerSTAILQueueNode* STAILQ_LAST_impl(mySTAILQueueHead* head, IntegerSTAILQueueNode){
    return STAILQ_LAST(head, IntegerSTAILQueueNode, entries);
}

IntegerSTAILQueueNode* STAILQ_NEXT_impl(IntegerSTAILQueueNode* elm){
    return STAILQ_NEXT(elm, entries);
}

void STAILQ_REMOVE_impl(mySTAILQueueHead* head,IntegerSTAILQueueNode* elm, IntegerSTAILQueueNode){
    STAILQ_REMOVE(head, elm, IntegerSTAILQueueNode, entries);
}

void STAILQ_REMOVE_AFTER_impl(mySTAILQueueHead* head,IntegerSTAILQueueNode* elm){
    STAILQ_REMOVE_AFTER(head, elm, entries);
}

void STAILQ_REMOVE_HEAD_impl(mySTAILQueueHead* head) {
    STAILQ_REMOVE_HEAD(head, entries);
}

void STAILQ_SWAP_impl(mySTAILQueueHead* head1,mySTAILQueueHead* head2, IntegerSTAILQueueNode) {
    STAILQ_SWAP(head1, head2, IntegerSTAILQueueNode);
}

IntegerSTAILQueueNode* STAILQ_END_impl(mySTAILQueueHead* head){
    return STAILQ_END(head);
}


void STAILQ_END_impl(mySTAILQueueHead* head){
    STAILQ_END(head);
}

//Doubly linked list
void LIST_CONCAT_impl(myLISTHead* head1, myLISTHead* head2) {
    LIST_CONCAT(head1, head2, IntegerLISTEntry, entries);
}

bool LIST_EMPTY_impl(myLISTHead* head) {
    return LIST_EMPTY(head);
}

IntegerLISTEntry* LIST_FIRST_impl(myLISTHead* head) {
    return LIST_FIRST(head);
}

void LIST_INIT_impl(myLISTHead* head) {
    LIST_INIT(head);
}

void LIST_INSERT_AFTER_impl(IntegerLISTEntry* listelm, IntegerLISTEntry* elm) {
    LIST_INSERT_AFTER(listelm, elm, entries);
}

void LIST_INSERT_BEFORE_impl(IntegerLISTEntry* listelm, IntegerLISTEntry* elm) {
    LIST_INSERT_BEFORE(listelm, elm, entries);
}

void LIST_INSERT_HEAD_impl(myLISTHead* head,IntegerLISTEntry* elm) {
    LIST_INSERT_HEAD(head, elm, entries);
}

IntegerLISTEntry* LIST_NEXT_impl(IntegerLISTEntry* elm) {
    return LIST_NEXT(elm, entries);
}

IntegerLISTEntry* LIST_PREV_impl(IntegerLISTEntry* elm, myLISTHead* head) {
    return LIST_PREV(elm, head, IntegerLISTEntry, entries);
}

void LIST_REMOVE_impl(IntegerLISTEntry* elm) {
    LIST_REMOVE(elm, entries);
}

void LIST_SWAP_impl(myLISTHead* head1, myLISTHead* head2) {
    LIST_SWAP(head1, head2, IntegerLISTEntry, entries);
}

IntegerLISTEntry* LIST_END_impl(myLISTHead* head) {
    return LIST_END(head);
}

//TAILQ, doubly linked tail queue
void TAILQ_CONCAT_impl(myTAILQueueHead* head1,myTAILQueueHead* head2) {
    TAILQ_CONCAT(head1, head2, entries);
}

bool TAILQ_EMPTY_impl(myTAILQueueHead* head) {
    return TAILQ_EMPTY(head);
}

IntegerTAILQueueNode* TAILQ_FIRST_impl(myTAILQueueHead *head) {
    return TAILQ_FIRST(head);
}

void TAILQ_INIT_impl(myTAILQueueHead* head) {
    TAILQ_INIT(head);
}

void TAILQ_INSERT_AFTER_impl(myTAILQueueHead* head,IntegerTAILQueueNode* listelm, IntegerTAILQueueNode* elm) {
    TAILQ_INSERT_AFTER(head, listelm, elm, entries);
}

void TAILQ_INSERT_BEFORE_impl(IntegerTAILQueueNode* listelm, IntegerTAILQueueNode* elm) {
    TAILQ_INSERT_BEFORE(listelm, elm, entries);
}

void TAILQ_INSERT_HEAD_impl(myTAILQueueHead* head, IntegerTAILQueueNode* elm) {
    TAILQ_INSERT_HEAD(head, elm, entries);
}

void TAILQ_INSERT_TAIL_impl(myTAILQueueHead* head, IntegerTAILQueueNode* elm) {
    TAILQ_INSERT_TAIL(head, elm, entries);
}

IntegerTAILQueueNode* TAILQ_LAST_impl(myTAILQueueHead* head) {
    return TAILQ_LAST(head, myTAILQueueHead);
}

IntegerTAILQueueNode* TAILQ_LAST_FAST_impl(myTAILQueueHead* head) {
    return TAILQ_LAST_FAST(head, IntegerTAILQueueNode, entries);
}

IntegerTAILQueueNode* TAILQ_NEXT_impl(IntegerTAILQueueNode* elm) {
    return TAILQ_NEXT(elm, entries);
}

IntegerTAILQueueNode* TAILQ_PREV_impl(IntegerTAILQueueNode* elm) {
    return TAILQ_PREV(elm, myTAILQueueHead, entries);
}

IntegerTAILQueueNode* TAILQ_PREV_FAST_impl(IntegerTAILQueueNode* elm, myTAILQueueHead* head ) {
    return TAILQ_PREV_FAST(elm, head,  IntegerTAILQueueNode, entries);
}

void TAILQ_REMOVE_impl(myTAILQueueHead* head, IntegerTAILQueueNode* elm) {
    TAILQ_REMOVE(head, elm, entries);
}
void TAILQ_SWAP_impl(myTAILQueueHead* head1, myTAILQueueHead* head2) {
    TAILQ_SWAP(head1, head2, IntegerTAILQueueNode, entries);
}

IntegerTAILQueueNode* TAILQ_END_impl(myTAILQueueHead* head) {
    return TAILQ_END(head);
}

//FIELD == entries
//TYPE = IntegerSLISTEntry
//elm = IntegerSLISTEntry
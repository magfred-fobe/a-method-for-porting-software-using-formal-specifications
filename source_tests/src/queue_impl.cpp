//
// Created by Magnus on 3/31/21.
//
//#include "queue.h"
#include "queue_impl.h"



void STAILQ_INIT_impl(mySTAILQueueHead* head) {
    do { (((head))->stqh_first) = 0; (head)->stqh_last = &(((head))->stqh_first); } while (0);
}

bool STAILQ_EMPTY_impl(mySTAILQueueHead *head) {
    return ((head)->stqh_first == 0);
}

void STAILQ_INSERT_HEAD_impl(mySTAILQueueHead* head, IntegerSTAILQueueNode* entry) {
    do { if (((((entry))->links.stqe_next) = (((head))->stqh_first)) == 0) (head)->stqh_last = &(((entry))->links.stqe_next); (((head))->stqh_first) = (entry); } while (0);
}

void STAILQ_REMOVE_HEAD_impl(mySTAILQueueHead* head) {
    do { if (((((head))->stqh_first) = (((((head))->stqh_first))->links.stqe_next)) == 0) (head)->stqh_last = &(((head))->stqh_first); } while (0);
}

void STAILQ_SWAP_impl(void* head1,void* head2,void* type) {
}




void SLIST_CONCAT_impl(mySinglyLinkedListHead* head1, mySinglyLinkedListHead* head2) {
    do { IntegerSLISTEntry *curelm = ((head1)->slh_first); if (curelm == 0) { if ((((head1)->slh_first) = ((head2)->slh_first)) != 0) do { (((head2))->slh_first) = 0; } while (0); } else if (((head2)->slh_first) != 0) { while (((curelm)->entries.sle_next) != 0) curelm = ((curelm)->entries.sle_next); ((curelm)->entries.sle_next) = ((head2)->slh_first); do { (((head2))->slh_first) = 0; } while (0); } } while (0);
}

bool SLIST_EMPTY_impl(mySinglyLinkedListHead* head) {
    return ((head)->slh_first == 0);
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


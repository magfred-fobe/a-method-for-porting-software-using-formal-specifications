//
// Created by Magnus on 3/31/21.
//
//#include "queue.h"
#include "queue_impl.h"
void STAILQ_INIT_impl(mySTAILQueue* head) {
    do { ((((mySTAILQueue*)head))->stqh_first) = 0; ((mySTAILQueue*)head)->stqh_last = &((((mySTAILQueue*)head))->stqh_first); } while (0);
}

bool STAILQ_EMPTY_impl(mySTAILQueue *head) {
    return ((head)->stqh_first == 0);
}

void STAILQ_INSERT_HEAD_impl(mySTAILQueue* head, IntegerSTAILQueueType* entry) {
    do { if (((((entry))->links.stqe_next) = (((head))->stqh_first)) == 0) (head)->stqh_last = &(((entry))->links.stqe_next); (((head))->stqh_first) = (entry); } while (0);
}

void STAILQ_REMOVE_HEAD_impl(mySTAILQueue* head) {
    do { if (((((head))->stqh_first) = (((((head))->stqh_first))->links.stqe_next)) == 0) (head)->stqh_last = &(((head))->stqh_first); } while (0);
}
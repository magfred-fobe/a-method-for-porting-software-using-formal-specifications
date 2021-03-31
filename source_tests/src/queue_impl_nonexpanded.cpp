#include "queue_impl.h"
void STAILQ_INIT_impl(mySTAILQueue* head) {
    STAILQ_INIT(head);
}

bool STAILQ_EMPTY_impl(mySTAILQueue *head) {
    return STAILQ_EMPTY(head);
}

void STAILQ_INSERT_HEAD_impl(mySTAILQueue* head, IntegerSTAILQueueType* entry) {
    STAILQ_INSERT_HEAD(head, entry, links);
}

void STAILQ_REMOVE_HEAD_impl(mySTAILQueue* head) {
    STAILQ_REMOVE_HEAD(head, links);
}

void STAILQ_SWAP_impl(int head1,int head2,int type) {
    STAILQ_SWAP(head1, head2, type)
}
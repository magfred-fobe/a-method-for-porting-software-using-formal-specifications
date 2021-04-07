//
// Created by Magnus on 3/31/21.
//
//#include "queue.h"
#include "queue_impl.h"
#include <cstddef>

//Singly linked list
void SLIST_INIT_impl(mySinglyLinkedListHead *head) {
    do { (((head))->slh_first) = NULL; } while (0);
}

IntegerSLISTEntry *SLIST_FIRST_impl(mySinglyLinkedListHead *head) {
    return ((head)->slh_first);
}

void SLIST_CONCAT_impl(mySinglyLinkedListHead *head1, mySinglyLinkedListHead *head2) {
    do {
        IntegerSLISTEntry *curelm = ((head1)->slh_first);
        if (curelm == NULL) {
            if ((((head1)->slh_first) = ((head2)->slh_first)) != NULL)
                do { (((head2))->slh_first) = NULL; } while (0);
        } else if (((head2)->slh_first) != NULL) {
            while (((curelm)->entries.sle_next) != NULL)
                curelm = ((curelm)->entries.sle_next);
            ((curelm)->entries.sle_next) = ((head2)->slh_first);
            do { (((head2))->slh_first) = NULL; } while (0);
        }
    } while (0);
}

bool SLIST_EMPTY_impl(mySinglyLinkedListHead *head) {
    return ((head)->slh_first == NULL);
}

void SLIST_INSERT_AFTER_impl(IntegerSLISTEntry *slistelm, IntegerSLISTEntry *elm) {
    do {
        (((elm))->entries.sle_next) = (((slistelm))->entries.sle_next);
        (((slistelm))->entries.sle_next) = (elm);
    } while (0);
}

void SLIST_INSERT_HEAD_impl(mySinglyLinkedListHead *head, IntegerSLISTEntry *elm) {
    do {
        (((elm))->entries.sle_next) = (((head))->slh_first);
        (((head))->slh_first) = (elm);
    } while (0);
}

void SLIST_REMOVE_impl(mySinglyLinkedListHead *head, IntegerSLISTEntry *elm) {
    do { ;
        if ((((head))->slh_first) ==
            (elm)) { do { ((((head)))->slh_first) = ((((((head)))->slh_first))->entries.sle_next); } while (0); }
        else {
            IntegerSLISTEntry *curelm = ((head)->slh_first);
            while (((curelm)->entries.sle_next) != (elm)) curelm = ((curelm)->entries.sle_next);
            do { ((curelm)->entries.sle_next) = ((((curelm)->entries.sle_next))->entries.sle_next); } while (0);
        };
    } while (0);
}

void SLIST_REMOVE_AFTER_impl(IntegerSLISTEntry *elm) {
    do { ((elm)->entries.sle_next) = ((((elm)->entries.sle_next))->entries.sle_next); } while (0);
}

void SLIST_REMOVE_HEAD_impl(mySinglyLinkedListHead *head) {
    do { (((head))->slh_first) = (((((head))->slh_first))->entries.sle_next); } while (0);
}

void SLIST_REMOVE_PREVPTR_impl(IntegerSLISTEntry **prevp, IntegerSLISTEntry *elm) {
    do { ;
        *(prevp) = ((elm)->entries.sle_next);;
    } while (0);
}

void SLIST_SWAP_impl(mySinglyLinkedListHead *head1, mySinglyLinkedListHead *head2) {
    do {
        IntegerSLISTEntry *swap_first = ((head1)->slh_first);
        ((head1)->slh_first) = ((head2)->slh_first);
        ((head2)->slh_first) = swap_first;
    } while (0);
}

mySinglyLinkedListHead *SLIST_END_impl(mySinglyLinkedListHead *head) {
    return NULL;
}

//Singly Linked Tail Queue
mySTAILQueueHead STAILQ_HEAD_INITIALIZER_impl(mySTAILQueueHead *head) {
    return {NULL, &(*head).stqh_first};
}

void STAILQ_CONCAT_impl(mySTAILQueueHead *head1, mySTAILQueueHead *head2) {
    do {
        if (!(((head2))->stqh_first == NULL)) {
            *(head1)->stqh_last = (head2)->stqh_first;
            (head1)->stqh_last = (head2)->stqh_last;
            do {
                ((((head2)))->stqh_first) = NULL;
                ((head2))->stqh_last = &((((head2)))->stqh_first);
            } while (0);
        }
    } while (0);
}

bool STAILQ_EMPTY_impl(mySTAILQueueHead *head) {
    return ((head)->stqh_first == NULL);
}

IntegerSTAILQueueNode *STAILQ_FIRST_impl(mySTAILQueueHead *head) {
    return ((head)->stqh_first);
}

void STAILQ_INIT_impl(mySTAILQueueHead *head) {
    do {
        (((head))->stqh_first) = NULL;
        (head)->stqh_last = &(((head))->stqh_first);
    } while (0);
}

void STAILQ_INSERT_AFTER_impl(mySTAILQueueHead *head, IntegerSTAILQueueNode *tqelm, IntegerSTAILQueueNode *elm) {
    do {
        if (((((elm))->entries.stqe_next) = (((tqelm))->entries.stqe_next)) == NULL)
            (head)->stqh_last = &(((elm))->entries.stqe_next);
        (((tqelm))->entries.stqe_next) = (elm);
    } while (0);
}

void STAILQ_INSERT_HEAD_impl(mySTAILQueueHead *head, IntegerSTAILQueueNode *elm) {
    do {
        if (((((elm))->entries.stqe_next) = (((head))->stqh_first)) == NULL)
            (head)->stqh_last = &(((elm))->entries.stqe_next);
        (((head))->stqh_first) = (elm);
    } while (0);
}

void STAILQ_INSERT_TAIL_impl(mySTAILQueueHead *head, IntegerSTAILQueueNode *elm) {
    do {
        (((elm))->entries.stqe_next) = NULL;
        *(head)->stqh_last = (elm);
        (head)->stqh_last = &(((elm))->entries.stqe_next);
    } while (0);
}

IntegerSTAILQueueNode *STAILQ_LAST_impl(mySTAILQueueHead *head) {
    return ((((head))->stqh_first == NULL) ? NULL : ({
        const volatile __typeof(((IntegerSTAILQueueNode *) 0)->entries.stqe_next) *__x = ((head)->stqh_last);
        ((IntegerSTAILQueueNode *) (uintptr_t) (const volatile void *) ((const volatile char *) __x -
                                                                        __builtin_offsetof(IntegerSTAILQueueNode,
                                                                                           entries.stqe_next)));
    }));
}

IntegerSTAILQueueNode *STAILQ_NEXT_impl(IntegerSTAILQueueNode *elm) {
    return ((elm)->entries.stqe_next);
}

void STAILQ_REMOVE_impl(mySTAILQueueHead *head, IntegerSTAILQueueNode *elm) {
    do { ;
        if ((((head))->stqh_first) == (elm)) {
            do {
                if ((((((head)))->stqh_first) = ((((((head)))->stqh_first))->entries.stqe_next)) == NULL)
                    ((head))->stqh_last = &((((head)))->stqh_first);
            } while (0);
        } else {
            IntegerSTAILQueueNode *curelm = ((head)->stqh_first);
            while (((curelm)->entries.stqe_next) != (elm)) curelm = ((curelm)->entries.stqe_next);
            do {
                if ((((curelm)->entries.stqe_next) = ((((curelm)->entries.stqe_next))->entries.stqe_next)) == NULL)
                    (head)->stqh_last = &(((curelm))->entries.stqe_next);
            } while (0);
        };
    } while (0);
}

void STAILQ_REMOVE_AFTER_impl(mySTAILQueueHead *head, IntegerSTAILQueueNode *elm) {
    do {
        if ((((elm)->entries.stqe_next) = ((((elm)->entries.stqe_next))->entries.stqe_next)) == NULL)
            (head)->stqh_last = &(((elm))->entries.stqe_next);
    } while (0);
}

void STAILQ_REMOVE_HEAD_impl(mySTAILQueueHead *head) {
    do {
        if (((((head))->stqh_first) = (((((head))->stqh_first))->entries.stqe_next)) == NULL)
            (head)->stqh_last = &(((head))->stqh_first);
    } while (0);
}

void STAILQ_SWAP_impl(mySTAILQueueHead *head1, mySTAILQueueHead *head2) {
    do {
        IntegerSTAILQueueNode *swap_first = ((head1)->stqh_first);
        IntegerSTAILQueueNode **swap_last = (head1)->stqh_last;
        ((head1)->stqh_first) = ((head2)->stqh_first);
        (head1)->stqh_last = (head2)->stqh_last;
        ((head2)->stqh_first) = swap_first;
        (head2)->stqh_last = swap_last;
        if (((head1)->stqh_first == NULL)) (head1)->stqh_last = &((head1)->stqh_first);
        if (((head2)->stqh_first == NULL)) (head2)->stqh_last = &((head2)->stqh_first);
    } while (0);
}

IntegerSTAILQueueNode *STAILQ_END_impl(mySTAILQueueHead *head) {
    return NULL;
}


//Doubly linked list
void LIST_CONCAT_impl(myLISTHead *head1, myLISTHead *head2) {
    do {
        IntegerLISTEntry *curelm = ((head1)->lh_first);
        if (curelm == NULL) {
            if ((((head1)->lh_first) = ((head2)->lh_first)) != NULL) {
                ((head2)->lh_first)->entries.le_prev = &(((head1))->lh_first);
                do { (((head2))->lh_first) = NULL; } while (0);
            }
        } else if (((head2)->lh_first) != NULL) {
            while (((curelm)->entries.le_next) != NULL)
                curelm = ((curelm)->entries.le_next);
            ((curelm)->entries.le_next) = ((head2)->lh_first);
            ((head2)->lh_first)->entries.le_prev = &((curelm)->entries.le_next);
            do { (((head2))->lh_first) = NULL; } while (0);
        }
    } while (0);
}

bool LIST_EMPTY_impl(myLISTHead *head) {
    return ((head)->lh_first == NULL);
}

IntegerLISTEntry *LIST_FIRST_impl(myLISTHead *head) {
    return ((head)->lh_first);
}

void LIST_INIT_impl(myLISTHead *head) {
    do { (((head))->lh_first) = NULL; } while (0);
}

void LIST_INSERT_AFTER_impl(IntegerLISTEntry *listelm, IntegerLISTEntry *elm) {
    do { ;
        if (((((elm))->entries.le_next) = (((listelm))->entries.le_next)) != NULL)
            (((listelm))->entries.le_next)->entries.le_prev = &(((elm))->entries.le_next);
        (((listelm))->entries.le_next) = (elm);
        (elm)->entries.le_prev = &(((listelm))->entries.le_next);
    } while (0);
}

void LIST_INSERT_BEFORE_impl(IntegerLISTEntry *listelm, IntegerLISTEntry *elm) {
    do { ;
        (elm)->entries.le_prev = (listelm)->entries.le_prev;
        (((elm))->entries.le_next) = (listelm);
        *(listelm)->entries.le_prev = (elm);
        (listelm)->entries.le_prev = &(((elm))->entries.le_next);
    } while (0);
}

void LIST_INSERT_HEAD_impl(myLISTHead *head, IntegerLISTEntry *elm) {
    do { ;
        if (((((elm))->entries.le_next) = (((head))->lh_first)) != NULL)
            (((head))->lh_first)->entries.le_prev = &(((elm))->entries.le_next);
        (((head))->lh_first) = (elm);
        (elm)->entries.le_prev = &(((head))->lh_first);
    } while (0);
}

IntegerLISTEntry *LIST_NEXT_impl(IntegerLISTEntry *elm) {
    return ((elm)->entries.le_next);
}

IntegerLISTEntry *LIST_PREV_impl(IntegerLISTEntry *elm, myLISTHead *head) {
    return ((elm)->entries.le_prev == &(((head))->lh_first) ? NULL : ({
        const volatile __typeof(((IntegerLISTEntry *) 0)->entries.le_next) *__x = ((elm)->entries.le_prev);
        ((IntegerLISTEntry *) (uintptr_t) (const volatile void *) ((const volatile char *) __x -
                                                                   __builtin_offsetof(IntegerLISTEntry,
                                                                                      entries.le_next)));
    }));
}

void LIST_REMOVE_impl(IntegerLISTEntry *elm) {
    do { ;;;;
        if ((((elm))->entries.le_next) != NULL) (((elm))->entries.le_next)->entries.le_prev = (elm)->entries.le_prev;
        *(elm)->entries.le_prev = (((elm))->entries.le_next);;;
    } while (0);
}

void LIST_SWAP_impl(myLISTHead *head1, myLISTHead *head2) {
    do {
        IntegerLISTEntry *swap_tmp = ((head1)->lh_first);
        (((head1))->lh_first) = (((head2))->lh_first);
        (((head2))->lh_first) = swap_tmp;
        if ((swap_tmp = (((head1))->lh_first)) != NULL)
            swap_tmp->entries.le_prev = &(((head1))->lh_first);
        if ((swap_tmp = (((head2))->lh_first)) != NULL)
            swap_tmp->entries.le_prev = &(((head2))->lh_first);
    } while (0);
}

IntegerLISTEntry *LIST_END_impl(myLISTHead *head) {
    return NULL;
}

//TAILQ, doubly linked tail queue
void TAILQ_CONCAT_impl(myTAILQueueHead *head1, myTAILQueueHead *head2) {
    do {
        if (!((head2)->tqh_first == NULL)) {
            *(head1)->tqh_last = (head2)->tqh_first;
            (head2)->tqh_first->entries.tqe_prev = (head1)->tqh_last;
            (head1)->tqh_last = (head2)->tqh_last;
            do {
                ((((head2)))->tqh_first) = NULL;
                ((head2))->tqh_last = &((((head2)))->tqh_first);;
            }
            while (0);;;
        }
    }
    while (0);
}

bool TAILQ_EMPTY_impl(myTAILQueueHead *head) {
    return ((head)->tqh_first == NULL);
}

IntegerTAILQueueNode *TAILQ_FIRST_impl(myTAILQueueHead *head) {
    return ((head)->tqh_first);
}

void TAILQ_INIT_impl(myTAILQueueHead *head) {
    do {
        (((head))->tqh_first) = NULL;
        (head)->tqh_last = &(((head))->tqh_first);;
    }
    while (0);
}

void TAILQ_INSERT_AFTER_impl(myTAILQueueHead *head, IntegerTAILQueueNode *listelm, IntegerTAILQueueNode *elm) {
    do { ;
        if (((((elm))->entries.tqe_next) = (((listelm))->entries.tqe_next)) != NULL)
            (((elm))->entries.tqe_next)->entries.tqe_prev = &(((elm))->entries.tqe_next);
        else { (head)->tqh_last = &(((elm))->entries.tqe_next);; }
        (((listelm))->entries.tqe_next) = (elm);
        (elm)->entries.tqe_prev = &(((listelm))->entries.tqe_next);;;
    }
    while (0);
}

void TAILQ_INSERT_BEFORE_impl(IntegerTAILQueueNode *listelm, IntegerTAILQueueNode *elm) {
    do { ;
        (elm)->entries.tqe_prev = (listelm)->entries.tqe_prev;
        (((elm))->entries.tqe_next) = (listelm);
        *(listelm)->entries.tqe_prev = (elm);
        (listelm)->entries.tqe_prev = &(((elm))->entries.tqe_next);;;
    }
    while (0);
}

void TAILQ_INSERT_HEAD_impl(myTAILQueueHead *head, IntegerTAILQueueNode *elm) {
    do { ;
        if (((((elm))->entries.tqe_next) = (((head))->tqh_first)) != NULL)
            (((head))->tqh_first)->entries.tqe_prev = &(((elm))->entries.tqe_next);
        else (head)->tqh_last = &(((elm))->entries.tqe_next);
        (((head))->tqh_first) = (elm);
        (elm)->entries.tqe_prev = &(((head))->tqh_first);;;
    }
    while (0);
}

void TAILQ_INSERT_TAIL_impl(myTAILQueueHead *head, IntegerTAILQueueNode *elm) {
    do { ;
        (((elm))->entries.tqe_next) = NULL;
        (elm)->entries.tqe_prev = (head)->tqh_last;
        *(head)->tqh_last = (elm);
        (head)->tqh_last = &(((elm))->entries.tqe_next);;;
    }
    while (0);
}

IntegerTAILQueueNode *TAILQ_LAST_impl(myTAILQueueHead *head) {
    return (*(((struct myTAILQueueHead *) ((head)->tqh_last))->tqh_last));
}

IntegerTAILQueueNode *TAILQ_LAST_FAST_impl(myTAILQueueHead *head) {
    return (((head)->tqh_first == NULL) ? NULL : ({
        const volatile __typeof(((IntegerTAILQueueNode *) 0)->entries.tqe_next) *__x = ((head)->tqh_last);
        ((IntegerTAILQueueNode *) (uintptr_t) (const volatile void *) ((const volatile char *) __x -
                                                                       __builtin_offsetof(IntegerTAILQueueNode,
                                                                                          entries.tqe_next)));
    }));
}

IntegerTAILQueueNode *TAILQ_NEXT_impl(IntegerTAILQueueNode *elm) {
    return ((elm)->entries.tqe_next);
}

IntegerTAILQueueNode *TAILQ_PREV_impl(IntegerTAILQueueNode *elm) {
    return (*(((struct myTAILQueueHead *) ((elm)->entries.tqe_prev))->tqh_last));
}

IntegerTAILQueueNode *TAILQ_PREV_FAST_impl(IntegerTAILQueueNode *elm, myTAILQueueHead *head) {
    return ((elm)->entries.tqe_prev == &(head)->tqh_first ? NULL : ({
        const volatile __typeof(((IntegerTAILQueueNode *) 0)->entries.tqe_next) *__x = ((elm)->entries.tqe_prev);
        ((IntegerTAILQueueNode *) (uintptr_t) (const volatile void *) ((const volatile char *) __x -
                                                                       __builtin_offsetof(IntegerTAILQueueNode,
                                                                                          entries.tqe_next)));
    }));
}

void TAILQ_REMOVE_impl(myTAILQueueHead *head, IntegerTAILQueueNode *elm) {
    do { ;;;;
        if (((((elm))->entries.tqe_next)) != NULL)
            (((elm))->entries.tqe_next)->entries.tqe_prev = (elm)->entries.tqe_prev;
        else { (head)->tqh_last = (elm)->entries.tqe_prev;; }
        *(elm)->entries.tqe_prev = (((elm))->entries.tqe_next);;;;
    }
    while (0);
}

void TAILQ_SWAP_impl(myTAILQueueHead *head1, myTAILQueueHead *head2) {
    do {
        IntegerTAILQueueNode *swap_first = (head1)->tqh_first;
        IntegerTAILQueueNode **swap_last = (head1)->tqh_last;
        (head1)->tqh_first = (head2)->tqh_first;
        (head1)->tqh_last = (head2)->tqh_last;
        (head2)->tqh_first = swap_first;
        (head2)->tqh_last = swap_last;
        if ((swap_first = (head1)->tqh_first) != NULL)
            swap_first->entries.tqe_prev = &(head1)->tqh_first;
        else (head1)->tqh_last = &(head1)->tqh_first;
        if ((swap_first = (head2)->tqh_first) != NULL)
            swap_first->entries.tqe_prev = &(head2)->tqh_first;
        else (head2)->tqh_last = &(head2)->tqh_first;
    }
    while (0);
}

IntegerTAILQueueNode *TAILQ_END_impl(myTAILQueueHead *head) {
    return NULL;
}




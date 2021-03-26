//
// Created by Magnus on 3/26/21.
//

#pragma once

struct IntegerSlistType {
    int data;
    SLIST_ENTRY(IntegerSlistType) entries;             /* Singly linked list */
};

SLIST_HEAD(mySinglyLinkedList, IntegerSlistType);

struct IntegerSTAILQueueType {
    int val;
    STAILQ_ENTRY(IntegerSTAILQueueType) links;
};
STAILQ_HEAD(mySTAILQueue, IntegerSTAILQueueType);

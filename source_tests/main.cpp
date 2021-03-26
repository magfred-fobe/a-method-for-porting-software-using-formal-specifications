#include <iostream>
#include "queue.h"


struct myListType {
    int data;
    SLIST_ENTRY(myListType) entries;             /* Singly linked list */
};

SLIST_HEAD(mySinglyLinkedList, myListType);

struct myQueueType {
    int val;
    STAILQ_ENTRY(myQueueType) links;
};
STAILQ_HEAD(myqueue, myQueueType);

int main() {
    struct myQueueType entry;
    myqueue head;
    STAILQ_INIT(&head);
    std::cout << "queue is "  << (STAILQ_EMPTY(&head) ? "" : "not ") << "empty " <<std::endl; //Queue is empty
    STAILQ_INSERT_HEAD(&head, &entry, links);
    std::cout << "queue is "  << (STAILQ_EMPTY(&head) ? "" : "not ") << "empty " <<std::endl; //Queue is not empty
    STAILQ_REMOVE_HEAD(&head, links);
    std::cout << "queue is "  << (STAILQ_EMPTY(&head) ? "" : "not ") << "empty " <<std::endl; //Queue is empty
    return 0;
}

#include <iostream>
#include "src/queue.h"
#include "gtest/gtest.h"
#include "integerlists.h"

//Example test case
TEST(queueTest, isInitiallyEmpty) {
    struct IntegerSTAILQueueType entry;
    mySTAILQueue head;
    STAILQ_INIT(&head);
    std::cout << "queue is " << (STAILQ_EMPTY(&head) ? "" : "not ") << "empty " << std::endl; //Queue is empty
    EXPECT_EQ (true, STAILQ_EMPTY(&head));
}

TEST(queueTest, isNotemptyWhenOneElement) {
    struct IntegerSTAILQueueType entry;
    mySTAILQueue head;
    STAILQ_INIT(&head);
    STAILQ_INSERT_HEAD(&head, &entry, links);
    std::cout << "queue is "  << (STAILQ_EMPTY(&head) ? "" : "not ") << "empty " << std::endl; //Queue is not empty
    EXPECT_EQ (false, STAILQ_EMPTY(&head));
}

TEST(queueTest, becomesEmptyWhenElementRemoved) {
    struct IntegerSTAILQueueType entry;
    mySTAILQueue head;
    STAILQ_INIT(&head);
    STAILQ_INSERT_HEAD(&head, &entry, links);
    STAILQ_REMOVE_HEAD(&head, links);
    std::cout << "queue is "  << (STAILQ_EMPTY(&head) ? "" : "not ") << "empty " << std::endl; //Queue is empty
    EXPECT_EQ (true, STAILQ_EMPTY(&head));
}
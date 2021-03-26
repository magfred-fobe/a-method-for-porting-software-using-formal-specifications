#include <iostream>
#include "src/queue.h"
#include "gtest/gtest.h"
#include "integerlists.h"
#include <gtest/gtest.h>
#include "rapidcheck/include/rapidcheck.h"
#include "rapidcheck/extras/gtest/include/rapidcheck/gtest.h"
//#include <rapidcheck/gtest.h>
//Example rapdtest_gtest cases

RC_GTEST_PROP(MyTestCase,
        copyOfStringIsIdenticalToOriginal,
(const std::string &str)) {
const auto strCopy = str;
RC_ASSERT(strCopy == str);
}

//Example gtest cases
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
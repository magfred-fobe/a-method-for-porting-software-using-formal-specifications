#include <iostream>
#include <string>
#include "../src/queue_impl.h"
#include "gtest/gtest.h"
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>


//Example rapdtest_gtest property based test
RC_GTEST_PROP(MyTestCase,
        copyOfStringIsIdenticalToOriginal,
(const std::string &str)) {
const auto strCopy = str;
RC_ASSERT(strCopy == str);
};

//Example gtest cases
TEST(queueTest, isInitiallyEmpty) {
    mySTAILQueue head;
    STAILQ_INIT_impl(&head);
    EXPECT_EQ (true, STAILQ_EMPTY_impl(&head));
}

TEST(queueTest, isNotemptyWhenOneElement) {
    struct IntegerSTAILQueueType entry;
    mySTAILQueue head;
    STAILQ_INIT_impl(&head);
    STAILQ_INSERT_HEAD_impl(&head, &entry);
    EXPECT_EQ (false, STAILQ_EMPTY_impl(&head));
}

TEST(queueTest, becomesEmptyWhenElementRemoved) {
    struct IntegerSTAILQueueType entry;
    mySTAILQueue head;
    STAILQ_INIT_impl(&head);
    STAILQ_INSERT_HEAD_impl(&head, &entry);
    STAILQ_REMOVE_HEAD_impl(&head);
    EXPECT_EQ (true, STAILQ_EMPTY_impl(&head));
}
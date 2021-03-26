#include <iostream>
#include <string>
#include "src/queue.h"
#include "gtest/gtest.h"
#include "integerlists.h"
#include <rapidcheck.h>
//Unfortunate, likely a bug in Clion makes it not able can't handle the include path
//symlinking it solves it and gives syntax highlighting...
#include <rapidcheck_gtest.h>

//Example rapdtest_gtest property based test
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
    EXPECT_EQ (true, STAILQ_EMPTY(&head));
}

TEST(queueTest, isNotemptyWhenOneElement) {
    struct IntegerSTAILQueueType entry;
    mySTAILQueue head;
    STAILQ_INIT(&head);
    STAILQ_INSERT_HEAD(&head, &entry, links);
    EXPECT_EQ (false, STAILQ_EMPTY(&head));
}

TEST(queueTest, becomesEmptyWhenElementRemoved) {
    struct IntegerSTAILQueueType entry;
    mySTAILQueue head;
    STAILQ_INIT(&head);
    STAILQ_INSERT_HEAD(&head, &entry, links);
    STAILQ_REMOVE_HEAD(&head, links);
    EXPECT_EQ (true, STAILQ_EMPTY(&head));
}
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


template <>
struct rc::Arbitrary<IntegerSLISTEntry> {
    static Gen<IntegerSLISTEntry> arbitrary() {
        return gen::build<IntegerSLISTEntry>(
                gen::set(&IntegerSLISTEntry::data, gen::arbitrary<int>()));
    }
};

void createList(mySinglyLinkedListHead &head,std::vector<IntegerSLISTEntry> &ents) {
    if(ents.empty()) {
        head.slh_first = nullptr;
        return;
    }
        for (std::size_t i = 0; i < ents.size()-1; i++) {
        ents.at(i).entries.sle_next = &(ents.at(i+1));
    }
        ents.at(ents.size()-1).entries.sle_next = nullptr;
        head.slh_first = &ents.at(0);
}

//rc::gen:.arbitrary should have an implicit size argument, which should start at 0
//and increase until configured maximum.
RC_GTEST_PROP(SLIST,
              concatenatingListsEmptiesSecondList,
              (std::vector<IntegerSLISTEntry> a,std::vector<IntegerSLISTEntry> b)){
    mySinglyLinkedListHead headA{NULL};
    createList(headA, a);
    mySinglyLinkedListHead headB{NULL};
    createList(headB, b);
    SLIST_CONCAT_impl(&headA, &headB);
    RC_ASSERT(nullptr == headB.slh_first);
}

RC_GTEST_PROP(SLIST,
              concatenatingListsMakesHeadALastNextHeadBFirst,
              (std::vector<IntegerSLISTEntry> a,std::vector<IntegerSLISTEntry> b)){

    RC_SUCCEED_IF(a.empty() || b.empty());
    RC_ASSERT(!(a.empty() || b.empty()));
    mySinglyLinkedListHead headA{NULL};
    createList(headA, a);
    mySinglyLinkedListHead headB{NULL};
    createList(headB, b);
    SLIST_CONCAT_impl(&headA, &headB);
    RC_ASSERT(a.at(a.size()-1).entries.sle_next == &b.at(0));
}

RC_GTEST_PROP(SLIST,
              concatenatingListsYieldsCorrectSizeOnList1,
              (std::vector<IntegerSLISTEntry> a,std::vector<IntegerSLISTEntry> b)){
    mySinglyLinkedListHead headA{nullptr};
    createList(headA, a);
    mySinglyLinkedListHead headB{nullptr};
    createList(headB, b);
    int expectedSize = a.size() + b.size();

    SLIST_CONCAT_impl(&headA, &headB);

    IntegerSLISTEntry *entry;
    int actualSize = 0;
    SLIST_FOREACH(entry, &headA, entries) {
        actualSize++;
    }
    RC_ASSERT(expectedSize == actualSize);
    RC_ASSERT(headB.slh_first == nullptr);
}

RC_GTEST_PROP(SLIST,
              concatenatingWithHead1EmptyPutsHeadAFirstOnHeadB,
              (std::vector<IntegerSLISTEntry> b)){
    RC_SUCCEED_IF(b.empty());
    mySinglyLinkedListHead headA{nullptr};
    mySinglyLinkedListHead headB{nullptr};
    createList(headB, b);
    IntegerSLISTEntry* headBFirst = &b.at(0) ;
    SLIST_CONCAT_impl(&headA, &headB);
    RC_ASSERT(headBFirst == headA.slh_first);
}

RC_GTEST_PROP(SLIST,
              concatenatingWithHeadBEmptyPutsHeadAFirstOnHeadA,
              (std::vector<IntegerSLISTEntry> a)){
    RC_SUCCEED_IF(a.empty());
    mySinglyLinkedListHead headA{nullptr};
    mySinglyLinkedListHead headB{nullptr};
    createList(headA, a);
    IntegerSLISTEntry* headAFirst = &a.at(0) ;
    SLIST_CONCAT_impl(&headA, &headB);
    RC_ASSERT(headAFirst == headA.slh_first);
}

RC_GTEST_PROP(SLIST,
              concatenatingListsPreservesOrder,
              (std::vector<IntegerSLISTEntry> a, std::vector<IntegerSLISTEntry> b)){
    mySinglyLinkedListHead headA{nullptr};
    createList(headA, a);
    mySinglyLinkedListHead headB{nullptr};
    createList(headB, b);
    SLIST_CONCAT_impl(&headA, &headB);
    IntegerSLISTEntry *entry;
    int temp = 0;

    SLIST_FOREACH(entry, &headA, entries) {
        IntegerSLISTEntry  &shouldPointTo = temp < a.size() ? a.at(temp) : b.at(temp - a.size());
        RC_ASSERT(&shouldPointTo == entry);
        temp++;
    }
}

//Example gtest cases
TEST(queueTest, isInitiallyEmpty) {
    mySTAILQueueHead head;
    STAILQ_INIT_impl(&head);
    EXPECT_EQ (true, STAILQ_EMPTY_impl(&head));
}

TEST(queueTest, isNotemptyWhenOneElement) {
    struct IntegerSTAILQueueNode entry;
    mySTAILQueueHead head;
    STAILQ_INIT_impl(&head);
    STAILQ_INSERT_HEAD_impl(&head, &entry);
    EXPECT_EQ (false, STAILQ_EMPTY_impl(&head));
}

TEST(queueTest, becomesEmptyWhenElementRemoved) {
    struct IntegerSTAILQueueNode entry;
    mySTAILQueueHead head;
    STAILQ_INIT_impl(&head);
    STAILQ_INSERT_HEAD_impl(&head, &entry);
    STAILQ_REMOVE_HEAD_impl(&head);
    EXPECT_EQ (true, STAILQ_EMPTY_impl(&head));
}
//
// Created by fredrik on 2021-04-04.
//
#include "../src/queue_impl.h"
#include "gtest/gtest.h"
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>
#include <algorithm>
#include <cstdlib>
#include <random>

template<>
struct rc::Arbitrary<IntegerSTAILQueueNode> {
    static Gen<IntegerSTAILQueueNode> arbitrary() {
        return gen::build<IntegerSTAILQueueNode>(
                gen::set(&IntegerSTAILQueueNode::val, gen::arbitrary<int>()));
    }
};

void createList(mySTAILQueueHead &head,std::vector<IntegerSTAILQueueNode> &ents) {
    if(ents.empty()) {
        head.stqh_first = nullptr;
        *head.stqh_last = nullptr;
        return;
    }
//    for (std::size_t i = 0; i < ents.size()-1; i++) {
//        ents.at(i).links.stqe_next = &(ents.at(i+1));
//    }
//
//    ents.at(ents.size()-1).links.stqe_next = nullptr;
//    head.stqh_first = &ents.at(0);
//    *head.stqh_last = &ents.at(ents.size()-1);
}


TEST(STAILQ, isInitializedCorrectly) {
    mySTAILQueueHead head;
    head = STAILQ_HEAD_INITIALIZER_impl(&head);
    EXPECT_EQ (true, STAILQ_EMPTY_impl(&head));
    EXPECT_EQ(head.stqh_first, *head.stqh_last);
}

RC_GTEST_PROP(STAILQ,
              concatenatingSTAILQLists,
              (std::vector<IntegerSTAILQueueNode> a, std::vector<IntegerSTAILQueueNode> b)){
      mySTAILQueueHead headA;
      STAILQ_INIT_impl(&headA);
      createList(headA, a);
      mySTAILQueueHead headB;
      STAILQ_INIT_impl(&headB);
      createList(headB, b);
      STAILQ_CONCAT_impl(&headA, &headB);
      EXPECT_EQ(nullptr, headB.stqh_first);
}


TEST(STAILQ, isInitiallyEmptyAndFirstAndLastAreSame) {
    mySTAILQueueHead head;
    STAILQ_INIT_impl(&head);
    EXPECT_EQ (true, STAILQ_EMPTY_impl(&head));
    EXPECT_EQ(head.stqh_first, *head.stqh_last);
}

TEST(STAILQ, isNotemptyWhenOneElement) {
    struct IntegerSTAILQueueNode entry;
    mySTAILQueueHead head;
    STAILQ_INIT_impl(&head);
    STAILQ_INSERT_HEAD_impl(&head, &entry);
    EXPECT_EQ (false, STAILQ_EMPTY_impl(&head));
}

TEST(STAILQ, becomesEmptyWhenElementRemoved) {
    struct IntegerSTAILQueueNode entry;
    mySTAILQueueHead head;
    STAILQ_INIT_impl(&head);
    STAILQ_INSERT_HEAD_impl(&head, &entry);
    STAILQ_REMOVE_HEAD_impl(&head);
    EXPECT_EQ (true, STAILQ_EMPTY_impl(&head));
}

RC_GTEST_PROP(STAILQ,
              testtesttesst,
              ()){
    mySTAILQueueHead headA{nullptr, nullptr};
    STAILQ_INIT_impl(&headA);
    EXPECT_EQ(headA.stqh_first, *headA.stqh_last);
}

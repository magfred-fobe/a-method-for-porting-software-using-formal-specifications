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

    STAILQ_INIT_impl(&head);

    if(ents.empty()) {
        return;
    }

    STAILQ_INSERT_HEAD_impl(&head, &ents.at(0));
    for (std::size_t i = 1; i < ents.size(); i++) {
        STAILQ_INSERT_AFTER_impl(&head, &ents.at(i-1),&ents.at(i));
    }

    STAILQ_INSERT_TAIL_impl(&head, &ents.at(ents.size()-1));
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
      createList(headA, a);
      mySTAILQueueHead headB;
      createList(headB, b);
      IntegerSTAILQueueNode* temp;
      IntegerSTAILQueueNode* first = STAILQ_FIRST_impl(&headA);
      unsigned int actualSize = 0;
      unsigned int expectedSize = a.size() + b.size();

      STAILQ_CONCAT_impl(&headA, &headB);

   //   STAILQ_FOREACH(temp, &headA, entries) {
     //       actualSize++;
     // }

      EXPECT_EQ(true, STAILQ_EMPTY_impl(&headB));
//      EXPECT_EQ(first, headA.stqh_first);
    //  EXPECT_EQ(expectedSize, actualSize);
}


TEST(STAILQ, isInitiallyEmptyAndFirstAndLastAreSame) {
    mySTAILQueueHead head;
    STAILQ_INIT_impl(&head);
    EXPECT_EQ (true, STAILQ_EMPTY_impl(&head));
    EXPECT_EQ(head.stqh_first, *head.stqh_last);
}

//TEST(STAILQ, isNotemptyWhenOneElement) {
//    struct IntegerSTAILQueueNode entry;
//    mySTAILQueueHead head;
//    STAILQ_INIT_impl(&head);
//    STAILQ_INSERT_HEAD_impl(&head, &entry);
//    EXPECT_EQ (false, STAILQ_EMPTY_impl(&head));
//}
//
//TEST(STAILQ, becomesEmptyWhenElementRemoved) {
//    struct IntegerSTAILQueueNode entry;
//    mySTAILQueueHead head;
//    STAILQ_INIT_impl(&head);
//    STAILQ_INSERT_HEAD_impl(&head, &entry);
//    STAILQ_REMOVE_HEAD_impl(&head);
//    EXPECT_EQ (true, STAILQ_EMPTY_impl(&head));
//}
//
//RC_GTEST_PROP(STAILQ,
//              testtesttesst,
//              ()){
//    mySTAILQueueHead headA{nullptr, nullptr};
//    STAILQ_INIT_impl(&headA);
//    EXPECT_EQ(headA.stqh_first, *headA.stqh_last);
//}

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
                gen::set(&IntegerSTAILQueueNode::data, gen::arbitrary<int>()));
    }
};

void createList(mySTAILQueueHead &head,std::vector<IntegerSTAILQueueNode> &ents) {

    STAILQ_INIT_impl(&head);

    if(ents.empty()) {
        return;
    }

    STAILQ_INSERT_HEAD_impl(&head, &ents.at(0));

    for (std::size_t i = 1; i < ents.size(); i++) {
        STAILQ_INSERT_TAIL_impl(&head, &ents.at(i));
    }
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
      IntegerSTAILQueueNode* second = STAILQ_FIRST_impl(&headB);
      unsigned int actualSize = 0;
      unsigned int expectedSize = a.size() + b.size();

      STAILQ_CONCAT_impl(&headA, &headB);

      STAILQ_FOREACH(temp, &headA, entries) {
            actualSize++;
      }

      EXPECT_EQ(true, STAILQ_EMPTY_impl(&headB));
      EXPECT_EQ(expectedSize, actualSize);
      if(a.size() > 0) EXPECT_EQ(first, STAILQ_FIRST_impl(&headA));
      else EXPECT_EQ(second, STAILQ_FIRST_impl(&headA));
}


TEST(STAILQ, isInitiallyEmpty) {
    mySTAILQueueHead head;
    STAILQ_INIT_impl(&head);
    EXPECT_EQ (true, STAILQ_EMPTY_impl(&head));
}

RC_GTEST_PROP(STAILQ, returnsFirstElement, (std::vector<IntegerSTAILQueueNode> a)) {

    mySTAILQueueHead head;
    createList(head, a);
    IntegerSTAILQueueNode* first = STAILQ_FIRST_impl(&head);

    if(!STAILQ_EMPTY_impl(&head)) EXPECT_EQ (first, &a.at(0));
}

TEST(STAILQ, initWorksCorrectly) {
    mySTAILQueueHead head;
    STAILQ_INIT_impl(&head);
    EXPECT_EQ (true, STAILQ_EMPTY_impl(&head));
    EXPECT_EQ(head.stqh_first, *head.stqh_last);
}

RC_GTEST_PROP(STAILQ, isInsertedAfter, (std::vector<IntegerSTAILQueueNode> a)) {

    mySTAILQueueHead head;
    IntegerSTAILQueueNode after;
    int index;
    createList(head, a);

    if (a.size() > 0) {
        index = std::rand() % a.size();
        STAILQ_INSERT_AFTER_impl(&head, &a.at(index), &after);
        EXPECT_EQ (a.at(index).entries.stqe_next, &after);
    }
}

RC_GTEST_PROP(STAILQ, headIsInserted, (std::vector<IntegerSTAILQueueNode> a)) {

    mySTAILQueueHead head;
    IntegerSTAILQueueNode newHead;
    createList(head, a);

    STAILQ_INSERT_HEAD_impl(&head, &newHead);

    EXPECT_EQ (&newHead, STAILQ_FIRST_impl(&head));
}

RC_GTEST_PROP(STAILQ, tailIsInserted, (std::vector<IntegerSTAILQueueNode> a)) {

    mySTAILQueueHead head;
    IntegerSTAILQueueNode tail;
    createList(head, a);

    STAILQ_INSERT_TAIL_impl(&head, &tail);

    EXPECT_EQ (&tail, STAILQ_LAST_impl(&head));
}

RC_GTEST_PROP(STAILQ, nextElementIsCorrect, (std::vector<IntegerSTAILQueueNode> a)) {

    mySTAILQueueHead head;
    IntegerSTAILQueueNode* next;
    createList(head, a);
    int index = 1;

    STAILQ_FOREACH(next, &head, entries){
        if (next && index < a.size())EXPECT_EQ (STAILQ_NEXT_impl(next), &a.at(index));
        index++;
    }


}

TEST(STAILQ, becomesEmptyWhenElementRemoved) {
    IntegerSTAILQueueNode entry;
    mySTAILQueueHead head;
    STAILQ_INIT_impl(&head);
    STAILQ_INSERT_HEAD_impl(&head, &entry);
    STAILQ_REMOVE_impl(&head, &entry);
    EXPECT_EQ (true, STAILQ_EMPTY_impl(&head));
}

RC_GTEST_PROP(STAILQ, elementIsRemoved, (std::vector<IntegerSTAILQueueNode> a)) {

    mySTAILQueueHead head;
    IntegerSTAILQueueNode* temp;
    int index;
    int actualSize = 0;
    createList(head, a);

    if (a.size() > 0) {
        index = std::rand() % a.size();

        STAILQ_REMOVE_impl(&head, &a.at(index));

        STAILQ_FOREACH(temp, &head, entries) {
            actualSize++;
        }
        EXPECT_EQ(a.size(), actualSize + 1);
    }
}

RC_GTEST_PROP(STAILQ, elementAfterIsRemoved, (std::vector<IntegerSTAILQueueNode> a)) {

    mySTAILQueueHead head;
    IntegerSTAILQueueNode* temp;
    int actualSize = 0;
    createList(head, a);

    if (a.size() > 2) {
        STAILQ_REMOVE_AFTER_impl(&head, &a.at(0));

        STAILQ_FOREACH(temp, &head, entries) {
            actualSize++;
        }
        EXPECT_EQ(head.stqh_first->entries.stqe_next, &a.at(2));
        EXPECT_EQ(a.size(), actualSize + 1);
    }
}

RC_GTEST_PROP(STAILQ, removesHead, (std::vector<IntegerSTAILQueueNode> a)) {

    mySTAILQueueHead head;
    createList(head, a);

    if(a.size() > 0)STAILQ_REMOVE_HEAD_impl(&head);
    if(a.size() > 1)EXPECT_EQ(STAILQ_FIRST_impl(&head), &a.at(1));
    else if (a.size() == 1) RC_ASSERT(STAILQ_EMPTY_impl(&head));
}


RC_GTEST_PROP(STAILQ, doubleSwappingSTAILQAlwaysGivesInitialLists, (std::vector<IntegerSTAILQueueNode> a, std::vector<IntegerSTAILQueueNode> b)){
    mySTAILQueueHead headA;
    createList(headA, a);
    mySTAILQueueHead headB;
    createList(headB, b);
    IntegerSTAILQueueNode* var;
    unsigned int size = 0;
    STAILQ_FOREACH(var, &headA, entries) {
        RC_ASSERT(var->data == a.at(size).data);
        EXPECT_EQ(var, &a.at(size));
        size++;
    }
    EXPECT_EQ(size, a.size());

    size = 0;
    STAILQ_FOREACH(var, &headB, entries) {
        RC_ASSERT(var->data == b.at(size).data);
        EXPECT_EQ(var, &b.at(size));
        size++;
    }
    EXPECT_EQ(size, b.size());
}


RC_GTEST_PROP(STAILQ, endIsAlwaysNull,
              (std::vector<IntegerSTAILQueueNode> a)) {
    mySTAILQueueHead head;
    createList(head, a);
    EXPECT_EQ(STAILQ_END_impl(&head), nullptr);
}
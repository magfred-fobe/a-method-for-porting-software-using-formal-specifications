#include <iostream>
#include <string>
#include "../src/queue_impl.h"
#include "gtest/gtest.h"
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>
#include <algorithm>
#include <cstdlib>
#include <random>

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
    unsigned int expectedSize = a.size() + b.size();

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

RC_GTEST_PROP(SLIST,
              nonemptyListIsAlwaysEmptyAfterNonRemovingOperation,
              (std::vector<IntegerSLISTEntry> a, std::vector<IntegerSLISTEntry> b)){
    mySinglyLinkedListHead headA{nullptr};
    createList(headA, a);
    mySinglyLinkedListHead headB{nullptr};
    createList(headB, b);
    RC_SUCCEED_IF(true);
}

TEST(SLIST, emptyListAlwaysReturnsNullAsFirst) {
    mySinglyLinkedListHead head;
    SLIST_INIT_impl(&head);
    EXPECT_EQ (nullptr, head.slh_first);
}

RC_GTEST_PROP(SLIST,
              foreachSummingaShouldYieldCorectSum,
              (std::vector<IntegerSLISTEntry> a, std::vector<IntegerSLISTEntry> b)){
    ///TODO: This test may invoke undefined behaviour. fix
    mySinglyLinkedListHead headA{nullptr};
    createList(headA, a);
    mySinglyLinkedListHead headB{nullptr};
    createList(headB, b);
    int expectedSum = 0;
    int actualSum = 0;
    for (auto &el : a) {
        expectedSum += el.data;
    }
    for (auto &el : b) {
        expectedSum += el.data;
    }
    IntegerSLISTEntry* var;
    SLIST_FOREACH(var, &headA, entries) {
        actualSum+=var->data;
    }
    SLIST_FOREACH(var, &headB, entries) {
        actualSum+=var->data;
    }
    RC_ASSERT(actualSum == expectedSum);
}


RC_GTEST_PROP(SLIST,
              addingElementsInForEachDoublesListSize,
              (std::vector<IntegerSLISTEntry> a)){
    mySinglyLinkedListHead headA{nullptr};
    createList(headA, a);
    IntegerSLISTEntry* var;
    std::vector<IntegerSLISTEntry> newEntries;
    newEntries.reserve(a.size());
    SLIST_FOREACH(var, &headA, entries) {
        if(var != &a.at(0)) {
            IntegerSLISTEntry entry = *rc::gen::arbitrary<IntegerSLISTEntry>();
            entry.entries.sle_next = nullptr;
            newEntries.push_back(entry);
            IntegerSLISTEntry* toInsert = &newEntries.back();
            SLIST_INSERT_HEAD_impl(&headA, toInsert);
        }
    }
    unsigned expectedSize = std::max((int)(a.size()*2-1), 0);
    unsigned int actualSize = 0;
    SLIST_FOREACH(var, &headA, entries) {
            actualSize++;
    }
    RC_ASSERT(actualSize == expectedSize);
}


RC_GTEST_PROP(SLIST,
              foreachSafeShouldHandleRemovalDuringTraversal,
              (std::vector<IntegerSLISTEntry> a)){
    mySinglyLinkedListHead headA{nullptr};
    createList(headA, a);
    IntegerSLISTEntry* var;
    IntegerSLISTEntry* tvar;
    SLIST_FOREACH_SAFE(var, &headA, entries, tvar) {
        SLIST_REMOVE_impl(&headA, var);
    }
    unsigned int actualSize = 0;
    unsigned int expectedSize = 0;
    SLIST_FOREACH(var, &headA, entries) {
        actualSize++;
    }
    RC_ASSERT(actualSize == expectedSize);
}


RC_GTEST_PROP(SLIST,
              insertingAfterIntoNonEmptyListShouldIncreaseSizeBy1,
              (std::vector<IntegerSLISTEntry> a)){
    RC_SUCCEED_IF(a.empty());
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, a.size()-1);
    mySinglyLinkedListHead headA{nullptr};
    createList(headA, a);

    IntegerSLISTEntry* var;
    unsigned int expectedSize = 1;
    SLIST_FOREACH(var, &headA, entries) {
        expectedSize++;
    }

    auto insertAfterThis = &a.at(distribution(generator));
    auto toInsert = *rc::gen::arbitrary<IntegerSLISTEntry>();
    SLIST_INSERT_AFTER_impl(insertAfterThis, &toInsert);
    unsigned int actualSize = 0;
    SLIST_FOREACH(var, &headA, entries) {
        actualSize++;
    }
    RC_ASSERT(actualSize == expectedSize);
}

RC_GTEST_PROP(SLIST,
              insertingElementWithVal1ShouldIncreaseSumBy1,
              (std::vector<IntegerSLISTEntry> a)){
    RC_SUCCEED_IF(a.empty());
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, a.size()-1);
    mySinglyLinkedListHead headA{nullptr};
    createList(headA, a);

    IntegerSLISTEntry* var;
    unsigned int expectedSum = 1;
    SLIST_FOREACH(var, &headA, entries) {
        expectedSum+= var->data;
    }

    auto insertAfterThis = &a.at(distribution(generator));
    auto toInsert = IntegerSLISTEntry{1, nullptr};
    SLIST_INSERT_AFTER_impl(insertAfterThis, &toInsert);
    unsigned int actualSum = 0;
    SLIST_FOREACH(var, &headA, entries) {
        actualSum+=var->data;
    }
    RC_ASSERT(actualSum == expectedSum);
}

RC_GTEST_PROP(SLIST,
              insertingAtHeadShouldIncreaseLengthBy1,
              (std::vector<IntegerSLISTEntry> a)){
    mySinglyLinkedListHead headA{nullptr};
    createList(headA, a);

    IntegerSLISTEntry* var;
    unsigned int expectedLength = a.size()+1;

    auto toInsert = IntegerSLISTEntry{1, nullptr};
    SLIST_INSERT_HEAD_impl(&headA, &toInsert);
    unsigned int actualLength = 0;
    SLIST_FOREACH(var, &headA, entries) {
        actualLength++;
    }
    RC_ASSERT(SLIST_FIRST_impl(&headA) == &toInsert);
    RC_ASSERT(actualLength == expectedLength);
}


RC_GTEST_PROP(SLIST,
              insertingHeadFromList2IntoList2ShouldMakeThemEqual,
              (std::vector<IntegerSLISTEntry> a, std::vector<IntegerSLISTEntry> b)){
    RC_SUCCEED_IF(b.empty());
    mySinglyLinkedListHead headA{nullptr};
    createList(headA, a);
    mySinglyLinkedListHead headB{nullptr};
    createList(headB, b);
    SLIST_INSERT_HEAD_impl(&headA, headB.slh_first);

    RC_ASSERT(SLIST_FIRST_impl(&headA) == SLIST_FIRST_impl(&headB));
}

RC_GTEST_PROP(SLIST,
              removingFromListWith1ElementShouldMakeEmpty,
              ()){
    mySinglyLinkedListHead headA{nullptr};

    auto a = std::vector<IntegerSLISTEntry>{*rc::gen::arbitrary<IntegerSLISTEntry>()};
    createList(headA, a);
    SLIST_REMOVE_impl(&headA, &a.at(0));
    RC_ASSERT(SLIST_FIRST_impl(&headA) == nullptr);
}

RC_GTEST_PROP(SLIST,
              removingFromListShouldEventuallyMakeEmpty,
              (std::vector<IntegerSLISTEntry> a)){
    std::default_random_engine generator;

    mySinglyLinkedListHead headA{nullptr};
    createList(headA, a);
    IntegerSLISTEntry* var;
    std::vector<IntegerSLISTEntry*> pointers;

    for(int i = 0; i < a.size(); i++) {
        pointers.push_back(&a.at(i));
    }

    unsigned prev_size = a.size();
    while(prev_size) {
        std::uniform_int_distribution<int> distribution(0, prev_size-1);
        unsigned int removeIndex = distribution(generator);
        auto elementToRemove = pointers.at(removeIndex);
        SLIST_REMOVE_impl(&headA, elementToRemove);
        pointers.erase(pointers.begin() + removeIndex);
        unsigned new_size = 0;
        SLIST_FOREACH(var, &headA, entries)  {
            new_size++;
        }
        RC_ASSERT(new_size == prev_size-1);
        prev_size = new_size;
    }
}

RC_GTEST_PROP(SLIST,
              removingHeadFromListShouldEventuallyMakeEmpty,
              (std::vector<IntegerSLISTEntry> a)){
    mySinglyLinkedListHead headA{nullptr};
    createList(headA, a);
    IntegerSLISTEntry* var;
    unsigned prev_size = a.size();
    while(headA.slh_first) {
        SLIST_REMOVE_HEAD_impl(&headA);
        unsigned new_size = 0;
        SLIST_FOREACH(var, &headA, entries)  {
            new_size++;
        }
        RC_ASSERT(new_size == prev_size-1);
        prev_size = new_size;
    }
}


RC_GTEST_PROP(SLIST,
              removingHeadShouldYieldCorrectFirstElement,
              (std::vector<IntegerSLISTEntry> a)){
    mySinglyLinkedListHead headA{nullptr};
    RC_SUCCEED_IF(a.empty());
    createList(headA, a);

    auto expectedNextElement = headA.slh_first->entries.sle_next;
    SLIST_REMOVE_impl(&headA, headA.slh_first);
    RC_ASSERT(headA.slh_first == expectedNextElement);
}

RC_GTEST_PROP(SLIST,
              removingElementNotPartOfListShouldNotMutateList,
              (std::vector<IntegerSLISTEntry> a, std::vector<IntegerSLISTEntry> b)){
    RC_SUCCEED_IF(b.size() < 2);
    mySinglyLinkedListHead headA{nullptr};
    createList(headA, a);

    mySinglyLinkedListHead headB{nullptr};
    createList(headB, b);

    SLIST_REMOVE_AFTER_impl(headB.slh_first);
    IntegerSLISTEntry* var;
    unsigned int count  = 0;
    SLIST_FOREACH(var, &headA, entries) {
        RC_ASSERT(&(a.at(count)) == var);
        count++;
    }
}


RC_GTEST_PROP(SLIST,
              afterRemovingElementPrevNextNextShouldBePrevNextNext,
              (std::vector<IntegerSLISTEntry> a)){
    mySinglyLinkedListHead headA{nullptr};
    RC_SUCCEED_IF(a.size() <= 1);
    std::default_random_engine generator;
    createList(headA, a);

    std::uniform_int_distribution<int> distribution(0, a.size()-1);
    unsigned int removeIndex = distribution(generator);
    IntegerSLISTEntry* next;
    if(removeIndex >= a.size()-2)
        next = nullptr;
    else
        next = a.at(removeIndex).entries.sle_next->entries.sle_next;
    SLIST_REMOVE_AFTER_impl(&a.at(removeIndex));
    RC_ASSERT(a.at(removeIndex).entries.sle_next == next);

}

/*The behaviour of remove_after is such that removing after when only 1 element exists after is not defined.*/
RC_GTEST_PROP(SLIST,
                consecutivelyRemovingElementsShouldMakeList1ElementLong,
              (std::vector<IntegerSLISTEntry> a)){
    mySinglyLinkedListHead headA{nullptr};
    RC_SUCCEED_IF(a.empty());
    createList(headA, a);
    while(headA.slh_first->entries.sle_next)
        SLIST_REMOVE_AFTER_impl(headA.slh_first);

    RC_ASSERT(headA.slh_first->entries.sle_next == nullptr);
}

RC_GTEST_PROP(SLIST,
              removingHeadShouldYieldCorrectNewHead,
              (std::vector<IntegerSLISTEntry> a)){
    RC_SUCCEED_IF(a.empty());
    mySinglyLinkedListHead headA{nullptr};
    createList(headA, a);
    auto expectedFirst = a.size() > 1 ? &a.at(1) : nullptr;
    SLIST_REMOVE_HEAD_impl(&headA);
    RC_ASSERT(headA.slh_first == expectedFirst);
}

RC_GTEST_PROP(SLIST,
              removePrevPtr,
              (std::vector<IntegerSLISTEntry> a)){
    RC_SUCCEED_IF(a.size() < 2);
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, a.size()-2);
    unsigned int prevPtrIndex = distribution(generator);
    mySinglyLinkedListHead headA{nullptr};
    createList(headA, a);
    IntegerSLISTEntry *prev = &(a.at(prevPtrIndex));
    auto prevptr = &(prev->entries.sle_next);
    auto expectedNext = a.at(prevPtrIndex+1).entries.sle_next;
    SLIST_REMOVE_PREVPTR_impl(prevptr, &a.at(prevPtrIndex+1));
    RC_ASSERT(prev->entries.sle_next == expectedNext);
}

RC_GTEST_PROP(SLIST,
              swappingShouldSwapHeadsOfAandB,
              (std::vector<IntegerSLISTEntry> a, std::vector<IntegerSLISTEntry> b)){
    mySinglyLinkedListHead headA{nullptr};
    createList(headA, a);
    mySinglyLinkedListHead headB{nullptr};
    createList(headB, b);
    auto prev_headAFirst = headA.slh_first;
    auto prev_headBFirst = headB.slh_first;
    SLIST_SWAP_impl(&headA, &headB);
    RC_ASSERT(prev_headBFirst == headA.slh_first);
    RC_ASSERT(prev_headAFirst == headB.slh_first);
    unsigned int actualBSize = 0;
    IntegerSLISTEntry* var;
    SLIST_FOREACH(var, &headB, entries) {
        actualBSize++;
    }
    RC_ASSERT(actualBSize == a.size());

    unsigned int actualASize = 0;
    SLIST_FOREACH(var, &headA, entries) {
        actualASize++;
    }
    RC_ASSERT(actualASize == b.size());
}

RC_GTEST_PROP(SLIST,
              endIsAlwaysNull,
              (std::vector<IntegerSLISTEntry> a)) {
    mySinglyLinkedListHead headA{nullptr};
    createList(headA, a);
    RC_ASSERT(SLIST_END_impl(&headA) == nullptr);
}


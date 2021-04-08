//
// Created by Magnus on 4/6/21.
//
#include "gtest/gtest.h"
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>
#include <rapidcheck/state.h>
#include <vector>
#include "../src/queue_impl.h"

struct SLIST_model {
    std::vector<int> list;
};

struct SLIST_first: rc::state::Command<SLIST_model, mySinglyLinkedListHead> {
    void run(const SLIST_model &model, mySinglyLinkedListHead &head) const override {
        if(model.list.empty())
            RC_ASSERT(SLIST_FIRST_impl(&head) == nullptr);
        else
            RC_ASSERT(SLIST_FIRST_impl(&head)->data == model.list.at(0));
    }

    void show(std::ostream &os) const override {
        os << "SLIST_FIRST";
    }
};

struct SLIST_insert_head : rc::state::Command<SLIST_model, mySinglyLinkedListHead> {
    int val = *rc::gen::arbitrary<int>();
    void apply(SLIST_model &model) const override {
        model.list.insert(model.list.begin(), 1, val);
        assert(model.list.at(0) == val);
    }

    void run(const SLIST_model &model, mySinglyLinkedListHead &head) const override {
        auto entry = new IntegerSLISTEntry();
        entry->data = val;
        SLIST_INSERT_HEAD_impl(&head, entry);
        RC_ASSERT( SLIST_FIRST_impl(&head)->data == val);
    }

    void show(std::ostream &os) const override {
        os << "SLIST_INSERT_HEAD VALUE: " << val;
    }
};

struct SLIST_insert_after : rc::state::Command<SLIST_model, mySinglyLinkedListHead> {
    unsigned int index = *rc::gen::arbitrary<unsigned int>();
    int val = *rc::gen::arbitrary<int>();

    void checkPreconditions(const SLIST_model &model) const override {
        RC_PRE(!model.list.empty());
    }

    void apply(SLIST_model &model) const override {
        unsigned int insert_index = index%model.list.size();
        if(insert_index == model.list.size() - 1)
            model.list.push_back(val);
        else
            model.list.insert(model.list.begin() + insert_index + 1, 1, val);
    }

    void run(const SLIST_model &model, mySinglyLinkedListHead &head) const override {
        auto element_before_insertion = SLIST_FIRST_impl(&head);
        unsigned int insertion_index = index%model.list.size();
        for(int i = 0; i < insertion_index; i++)
            element_before_insertion = SLIST_NEXT_impl(element_before_insertion);

        auto element_to_be_inserted = new IntegerSLISTEntry();
        element_to_be_inserted->data = val;
        SLIST_INSERT_AFTER_impl(element_before_insertion, element_to_be_inserted);
    }

    void show(std::ostream &os) const override {
        os << "SLIST_INSERT_AFTER INDEX: "<< index << ", VALUE: " << val;
    }
};

struct SLIST_remove_element : rc::state::Command<SLIST_model, mySinglyLinkedListHead> {
    unsigned int index = *rc::gen::arbitrary<unsigned int>();

    void checkPreconditions(const SLIST_model &model) const override {
        RC_PRE(!model.list.empty());
    }

    void apply(SLIST_model &model) const override {
        unsigned int removeIndex = index % model.list.size();
        model.list.erase(model.list.begin() + removeIndex);
    }

    void run(const SLIST_model &model, mySinglyLinkedListHead &head) const override {
        auto elementToRemove = SLIST_FIRST_impl(&head);
        unsigned int insertion_index = index % model.list.size();
        for(int i = 0; i < insertion_index; i++)
            elementToRemove = SLIST_NEXT_impl(elementToRemove);

        SLIST_REMOVE_impl(&head, elementToRemove);
    }

    void show(std::ostream &os) const override {
        os << "SLIST_REMOVE_ELEMENT "<< index;
    }
};

struct SLIST_remove_after : rc::state::Command<SLIST_model, mySinglyLinkedListHead> {
    unsigned int index = *rc::gen::arbitrary<unsigned int>();

    void checkPreconditions(const SLIST_model &model) const override {
        RC_PRE(model.list.size() > 1);
    }

    void apply(SLIST_model &model) const override {
        unsigned int remove_index = index % (model.list.size() - 1);
        model.list.erase(model.list.begin() + remove_index + 1);
    }

    void run(const SLIST_model &model, mySinglyLinkedListHead &head) const override {
        auto elementToRemove = SLIST_FIRST_impl(&head);
        unsigned int remove_index = index % (model.list.size() - 1);
        for(int i = 0; i < remove_index; i++)
            elementToRemove = SLIST_NEXT_impl(elementToRemove);

        SLIST_REMOVE_AFTER_impl(elementToRemove);
    }

    void show(std::ostream &os) const override {
        os << "SLIST_REMOVE_AFTER "<< index;
    }
};

struct SLIST_remove_head : rc::state::Command<SLIST_model, mySinglyLinkedListHead> {
    //For every action, we can override checkPreconditions, to dynamically check if the action is valid
    //given the current state of the SUT
    void checkPreconditions(const SLIST_model &model) const override {
        RC_PRE(!model.list.empty());
    }

    //Important to note that apply(), and and run() receive
    //references to the previous state, so any changes made in apply() are not visible in run().
    void apply(SLIST_model &model) const override {
        int prevVal = model.list.at(0);
        if(model.list.size() > 1)
            prevVal = model.list.at(1);
        model.list.erase(model.list.begin(), model.list.begin() + 1);
        if(!model.list.empty())
            RC_ASSERT(prevVal == model.list.at(0));
    }

    void run(const SLIST_model &model, mySinglyLinkedListHead &head) const override {
        RC_ASSERT(SLIST_FIRST_impl(&head)->data == model.list.at(0));
        IntegerSLISTEntry * previousFirst = SLIST_FIRST_impl(&head);
        SLIST_REMOVE_HEAD_impl(&head);
        delete(previousFirst);
    }

    void show(std::ostream &os) const override {
        os << "SLIST_REMOVE_HEAD";
    }
};

struct SLIST_remove_prevptr : rc::state::Command<SLIST_model, mySinglyLinkedListHead> {
    unsigned int index = *rc::gen::arbitrary<unsigned int>();

    void checkPreconditions(const SLIST_model &model) const override {
        RC_PRE(model.list.size() > 1);
    }

    void apply(SLIST_model &model) const override {
        unsigned int remove_after_index = index % (model.list.size() - 1);
        model.list.erase(model.list.begin() + remove_after_index + 1);
    }

    void run(const SLIST_model &model, mySinglyLinkedListHead &head) const override {
        auto elementToRemove = SLIST_FIRST_impl(&head);
        IntegerSLISTEntry** prevptr;
        unsigned int remove_after = index % (model.list.size() - 1);
        for(int i = 0; i <= remove_after; i++){
            prevptr = &(elementToRemove->entries.sle_next);
            elementToRemove = SLIST_NEXT_impl(elementToRemove);
        }
        SLIST_REMOVE_PREVPTR_impl(prevptr, elementToRemove);
    }

    void show(std::ostream &os) const override {
        os << "SLIST_REMOVE_PREVPTR "<< index;
    }
};

struct SLIST_swap : rc::state::Command<SLIST_model, mySinglyLinkedListHead> {
    std::vector<int> swap_with = *rc::gen::arbitrary<std::vector<int>>();

    void apply(SLIST_model &model) const override {
        model.list = swap_with;
    }

    void run(const SLIST_model &model, mySinglyLinkedListHead &head1) const override {
        auto head2 = new mySinglyLinkedListHead();
        SLIST_INIT_impl(head2);
        IntegerSLISTEntry* prev_entry;
        for(int i = 0; i< swap_with.size(); i++) {
            auto entry = new IntegerSLISTEntry();
            entry->data = swap_with.at(i);
            if(i == 0)
                SLIST_INSERT_HEAD_impl(head2, entry);
            else
                SLIST_INSERT_AFTER_impl(prev_entry, entry);
            prev_entry = entry;
        }
        SLIST_SWAP_impl(&head1, head2);
    }

    void show(std::ostream &os) const override {
        os << "SLIST_SWAP: << ";
        for(auto i: swap_with)
            os << i << ", ";
    }
};

struct SLIST_concatenate : rc::state::Command<SLIST_model, mySinglyLinkedListHead> {
    std::vector<int> concatenate_with = *rc::gen::arbitrary<std::vector<int>>();

    void apply(SLIST_model &model) const override {
        for(auto i: concatenate_with)
        model.list.push_back(i);
    }

    void run(const SLIST_model &model, mySinglyLinkedListHead &head1) const override {
        auto head2 = new mySinglyLinkedListHead();
        SLIST_INIT_impl(head2);
        IntegerSLISTEntry* prev_entry;
        for(int i = 0; i < concatenate_with.size(); i++) {
            auto entry = new IntegerSLISTEntry();
            entry->data = concatenate_with.at(i);
            if(i == 0)
                SLIST_INSERT_HEAD_impl(head2, entry);
            else
                SLIST_INSERT_AFTER_impl(prev_entry, entry);
            prev_entry = entry;
        }
        SLIST_CONCAT_impl(&head1, head2);
    }

    void show(std::ostream &os) const override {
        os << "SLIST_CONCAT: << ";
        for(auto i: concatenate_with)
            os << i << ", ";
    }
};

struct SLIST_empty : rc::state::Command<SLIST_model, mySinglyLinkedListHead> {
    void run(const SLIST_model &model, mySinglyLinkedListHead &head1) const override {
        RC_ASSERT(model.list.empty() == SLIST_EMPTY_impl(&head1));
    }

    void show(std::ostream &os) const override {
        os << "EMPTY";
    }
};

struct SLIST_foreach : rc::state::Command<SLIST_model, mySinglyLinkedListHead> {
    void run(const SLIST_model &model, mySinglyLinkedListHead &head) const override {
        auto entry = SLIST_FIRST_impl(&head);
        for(int i = 0; i < model.list.size(); i++) {
            RC_ASSERT(model.list.at(i) == entry->data);
            entry = entry->entries.sle_next;
        }
        RC_ASSERT(entry == nullptr);
    }

    void show(std::ostream &os) const override {
        os << "FOREACH";
    }
};

struct SLIST_foreach_from : rc::state::Command<SLIST_model, mySinglyLinkedListHead> {
    unsigned int random_index = *rc::gen::arbitrary<unsigned int>();

    void run(const SLIST_model &model, mySinglyLinkedListHead &head) const override {
        unsigned int from_index = model.list.empty() ? 0 : random_index % model.list.size();
        auto entry = SLIST_FIRST_impl(&head);
        for(int i = 0; i < from_index; i++)
            entry = SLIST_NEXT_impl(entry);

        for(unsigned int i = from_index; i < model.list.size(); i++) {
            RC_ASSERT(model.list.at(i) == entry->data);
            entry = entry->entries.sle_next;
        }
        RC_ASSERT(entry == nullptr);
    }

    void show(std::ostream &os) const override {
        os << "FOREACH";
    }
};

//RC will generate a sequence of valid operations based on each operations preconditions.
//The results of the operations can are checked with an assumed to be correct model.
TEST(SLIST_model, SLIST_sequenceTest){
    RC_ASSERT(rc::check([] {
        SLIST_model model;
        mySinglyLinkedListHead head{};
        SLIST_INIT_impl(&head);
        rc::state::check(model,
                         head,
                         rc::state::gen::execOneOfWithArgs<
                                 SLIST_insert_head
                                ,SLIST_first
                                ,SLIST_insert_after
                                ,SLIST_remove_element
                                ,SLIST_remove_after
                                ,SLIST_remove_head
                                ,SLIST_remove_prevptr
                                ,SLIST_swap
                                ,SLIST_concatenate
                                ,SLIST_empty
                                ,SLIST_foreach
                                ,SLIST_foreach_from
                                >());
    }));
};

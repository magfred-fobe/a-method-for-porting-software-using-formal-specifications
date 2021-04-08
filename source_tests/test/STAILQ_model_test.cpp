//
// Created by Magnus on 4/6/21.
//
#include "gtest/gtest.h"
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>
#include <rapidcheck/state.h>
#include <vector>
#include "../src/queue_impl.h"

struct STAILQ_model {
    std::vector<int> list;
};

struct STAILQ_first: rc::state::Command<STAILQ_model, mySTAILQueueHead> {
    void run(const STAILQ_model &model, mySTAILQueueHead &head) const override {
        if(model.list.empty())
            RC_ASSERT(STAILQ_FIRST_impl(&head) == nullptr);
        else
            RC_ASSERT(STAILQ_FIRST_impl(&head)->data == model.list.at(0));
    }

    void show(std::ostream &os) const override {
        os << "STAILQ_FIRST";
    }
};


struct STAILQ_last: rc::state::Command<STAILQ_model, mySTAILQueueHead> {
    void run(const STAILQ_model &model, mySTAILQueueHead &head) const override {
        if(model.list.empty())
            RC_ASSERT(STAILQ_LAST_impl(&head) == nullptr);
        else
            RC_ASSERT(STAILQ_LAST_impl(&head)->data == model.list.back());
    }

    void show(std::ostream &os) const override {
        os << "STAILQ_FIRST";
    }
};

struct STAILQ_insert_head : rc::state::Command<STAILQ_model, mySTAILQueueHead> {
    int val = *rc::gen::arbitrary<int>();
    void apply(STAILQ_model &model) const override {
        model.list.insert(model.list.begin(), 1, val);
        assert(model.list.at(0) == val);
    }

    void run(const STAILQ_model &model, mySTAILQueueHead &head) const override {
        auto entry = new IntegerSTAILQueueNode();
        entry->data = val;
        STAILQ_INSERT_HEAD_impl(&head, entry);
        RC_ASSERT( STAILQ_FIRST_impl(&head)->data == val);
    }

    void show(std::ostream &os) const override {
        os << "STAILQ_INSERT_HEAD VALUE: " << val;
    }
};

struct STAILQ_insert_after : rc::state::Command<STAILQ_model, mySTAILQueueHead> {
    unsigned int index = *rc::gen::arbitrary<unsigned int>();
    int val = *rc::gen::arbitrary<int>();

    void checkPreconditions(const STAILQ_model &model) const override {
        RC_PRE(!model.list.empty());
    }

    void apply(STAILQ_model &model) const override {
        unsigned int insert_index = index%model.list.size();
        if(insert_index == model.list.size() - 1)
            model.list.push_back(val);
        else
            model.list.insert(model.list.begin() + insert_index + 1, 1, val);
    }

    void run(const STAILQ_model &model, mySTAILQueueHead &head) const override {
        auto element_before_insertion = STAILQ_FIRST_impl(&head);
        unsigned int insertion_index = index%model.list.size();
        for(int i = 0; i < insertion_index; i++)
            element_before_insertion = STAILQ_NEXT_impl(element_before_insertion);

        auto element_to_be_inserted = new IntegerSTAILQueueNode();
        element_to_be_inserted->data = val;
        STAILQ_INSERT_AFTER_impl(&head, element_before_insertion, element_to_be_inserted);
    }

    void show(std::ostream &os) const override {
        os << "STAILQ_INSERT_AFTER INDEX: "<< index << ", VALUE: " << val;
    }
};

struct STAILQ_remove_element : rc::state::Command<STAILQ_model, mySTAILQueueHead> {
    unsigned int index = *rc::gen::arbitrary<unsigned int>();

    void checkPreconditions(const STAILQ_model &model) const override {
        RC_PRE(!model.list.empty());
    }

    void apply(STAILQ_model &model) const override {
        unsigned int removeIndex = index % model.list.size();
        model.list.erase(model.list.begin() + removeIndex);
    }

    void run(const STAILQ_model &model, mySTAILQueueHead &head) const override {
        auto elementToRemove = STAILQ_FIRST_impl(&head);
        unsigned int insertion_index = index % model.list.size();
        for(int i = 0; i < insertion_index; i++)
            elementToRemove = STAILQ_NEXT_impl(elementToRemove);

        STAILQ_REMOVE_impl(&head, elementToRemove);
    }

    void show(std::ostream &os) const override {
        os << "STAILQ_REMOVE_ELEMENT "<< index;
    }
};

struct STAILQ_remove_after : rc::state::Command<STAILQ_model, mySTAILQueueHead> {
    unsigned int index = *rc::gen::arbitrary<unsigned int>();

    void checkPreconditions(const STAILQ_model &model) const override {
        RC_PRE(model.list.size() > 1);
    }

    void apply(STAILQ_model &model) const override {
        unsigned int remove_index = index % (model.list.size() - 1);
        model.list.erase(model.list.begin() + remove_index + 1);
    }

    void run(const STAILQ_model &model, mySTAILQueueHead &head) const override {
        auto elementToRemove = STAILQ_FIRST_impl(&head);
        unsigned int remove_index = index % (model.list.size() - 1);
        for(int i = 0; i < remove_index; i++)
            elementToRemove = STAILQ_NEXT_impl(elementToRemove);

        STAILQ_REMOVE_AFTER_impl(&head, elementToRemove);
    }

    void show(std::ostream &os) const override {
        os << "STAILQ_REMOVE_AFTER "<< index;
    }
};

struct STAILQ_remove_head : rc::state::Command<STAILQ_model, mySTAILQueueHead> {
    //For every action, we can override checkPreconditions, to dynamically check if the action is valid
    //given the current state of the SUT
    void checkPreconditions(const STAILQ_model &model) const override {
        RC_PRE(!model.list.empty());
    }

    //Important to note that apply(), and and run() receive
    //references to the previous state, so any changes made in apply() are not visible in run().
    void apply(STAILQ_model &model) const override {
        int prevVal = model.list.at(0);
        if(model.list.size() > 1)
            prevVal = model.list.at(1);
        model.list.erase(model.list.begin(), model.list.begin() + 1);
        if(!model.list.empty())
            RC_ASSERT(prevVal == model.list.at(0));
    }

    void run(const STAILQ_model &model, mySTAILQueueHead &head) const override {
        RC_ASSERT(STAILQ_FIRST_impl(&head)->data == model.list.at(0));
        IntegerSTAILQueueNode * previousFirst = STAILQ_FIRST_impl(&head);
        STAILQ_REMOVE_HEAD_impl(&head);
        delete(previousFirst);
    }

    void show(std::ostream &os) const override {
        os << "STAILQ_REMOVE_HEAD";
    }
};

struct STAILQ_swap : rc::state::Command<STAILQ_model, mySTAILQueueHead> {
    std::vector<int> swap_with = *rc::gen::arbitrary<std::vector<int>>();

    void apply(STAILQ_model &model) const override {
        model.list = swap_with;
    }

    void run(const STAILQ_model &model, mySTAILQueueHead &head1) const override {
        auto head2 = new mySTAILQueueHead();
        STAILQ_INIT_impl(head2);
        IntegerSTAILQueueNode* prev_entry;
        for(int i = 0; i< swap_with.size(); i++) {
            auto entry = new IntegerSTAILQueueNode();
            entry->data = swap_with.at(i);
            if(i == 0)
                STAILQ_INSERT_HEAD_impl(head2, entry);
            else
                STAILQ_INSERT_AFTER_impl(head2, prev_entry, entry);
            prev_entry = entry;
        }
        STAILQ_SWAP_impl(&head1, head2);
    }

    void show(std::ostream &os) const override {
        os << "STAILQ_SWAP: << ";
        for(auto i: swap_with)
            os << i << ", ";
    }
};

struct STAILQ_concatenate : rc::state::Command<STAILQ_model, mySTAILQueueHead> {
    std::vector<int> concatenate_with = *rc::gen::arbitrary<std::vector<int>>();

    void apply(STAILQ_model &model) const override {
        for(auto i: concatenate_with)
        model.list.push_back(i);
    }

    void run(const STAILQ_model &model, mySTAILQueueHead &head1) const override {
        auto head2 = new mySTAILQueueHead();
        STAILQ_INIT_impl(head2);
        IntegerSTAILQueueNode* prev_entry;
        for(int i = 0; i < concatenate_with.size(); i++) {
            auto entry = new IntegerSTAILQueueNode();
            entry->data = concatenate_with.at(i);
            if(i == 0)
                STAILQ_INSERT_HEAD_impl(head2, entry);
            else
                STAILQ_INSERT_AFTER_impl(head2, prev_entry, entry);
            prev_entry = entry;
        }
        STAILQ_CONCAT_impl(&head1, head2);
    }

    void show(std::ostream &os) const override {
        os << "STAILQ_CONCAT: << ";
        for(auto i: concatenate_with)
            os << i << ", ";
    }
};

struct STAILQ_empty : rc::state::Command<STAILQ_model, mySTAILQueueHead> {
    void run(const STAILQ_model &model, mySTAILQueueHead &head1) const override {
        RC_ASSERT(model.list.empty() == STAILQ_EMPTY_impl(&head1));
    }

    void show(std::ostream &os) const override {
        os << "EMPTY";
    }
};

struct STAILQ_foreach : rc::state::Command<STAILQ_model, mySTAILQueueHead> {

    void run(const STAILQ_model &model, mySTAILQueueHead &head) const override {
        auto entry = STAILQ_FIRST_impl(&head);
        for(int i = 0; i < model.list.size(); i++) {
            RC_ASSERT(model.list.at(i) == entry->data);
            entry = entry->entries.stqe_next;
        }
        RC_ASSERT(entry == nullptr);
    }

    void show(std::ostream &os) const override {
        os << "FOREACH";
    }
};

struct STAILQ_foreach_from : rc::state::Command<STAILQ_model, mySTAILQueueHead> {
    unsigned int random_index = *rc::gen::arbitrary<unsigned int>();

    void run(const STAILQ_model &model, mySTAILQueueHead &head) const override {
        unsigned int from_index = model.list.empty() ? 0 : random_index % model.list.size();
        auto entry = STAILQ_FIRST_impl(&head);
        for(int i = 0; i < from_index; i++)
            entry = STAILQ_NEXT_impl(entry);

        for(unsigned int i = from_index; i < model.list.size(); i++) {
            RC_ASSERT(model.list.at(i) == entry->data);
            entry = entry->entries.stqe_next;
        }
        RC_ASSERT(entry == nullptr);
    }

    void show(std::ostream &os) const override {
        os << "FOREACH";
    }
};

//RC will generate a sequence of valid operations based on each operations preconditions.
//The results of the operations can are checked with an assumed to be correct model.
TEST(STAILQ_model, STAILQ_sequenceTest){
    RC_ASSERT(rc::check([] {
        STAILQ_model model;
        mySTAILQueueHead head{};
        STAILQ_INIT_impl(&head);
        rc::state::check(model,
                         head,
                         rc::state::gen::execOneOfWithArgs<
                                 STAILQ_insert_head
                                ,STAILQ_first
                                ,STAILQ_last
                                ,STAILQ_insert_after
                                ,STAILQ_remove_element
                                ,STAILQ_remove_after
                                ,STAILQ_remove_head
                                ,STAILQ_swap
                                ,STAILQ_concatenate
                                ,STAILQ_empty
                                ,STAILQ_foreach
                                ,STAILQ_foreach_from
                                >());
    }));
};

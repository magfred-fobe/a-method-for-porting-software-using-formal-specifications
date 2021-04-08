//
// Created by Magnus on 4/6/21.
//
#include "gtest/gtest.h"
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>
#include <rapidcheck/state.h>
#include <vector>
#include "../src/queue_impl.h"

struct TAILQ_model {
    std::vector<int> list;
};

struct first: rc::state::Command<TAILQ_model, myTAILQueueHead> {
    void run(const TAILQ_model &model, myTAILQueueHead &head) const override {
        if(model.list.empty())
            RC_ASSERT(TAILQ_FIRST_impl(&head) == nullptr);
        else
            RC_ASSERT(TAILQ_FIRST_impl(&head)->data == model.list.at(0));
    }

    void show(std::ostream &os) const override {
        os << "TAILQ_FIRST";
    }
};

struct insert_head : rc::state::Command<TAILQ_model, myTAILQueueHead> {
    int val = *rc::gen::arbitrary<int>();
    void apply(TAILQ_model &model) const override {
        model.list.insert(model.list.begin(), 1, val);
        assert(model.list.at(0) == val);
    }

    void run(const TAILQ_model &model, myTAILQueueHead &head) const override {
        auto entry = new IntegerTAILQueueNode();
        entry->data = val;
        TAILQ_INSERT_HEAD_impl(&head, entry);
        RC_ASSERT( TAILQ_FIRST_impl(&head)->data == val);
    }

    void show(std::ostream &os) const override {
        os << "TAILQ_INSERT_HEAD VALUE: " << val;
    }
};

struct insert_after : rc::state::Command<TAILQ_model, myTAILQueueHead> {
    unsigned int index = *rc::gen::arbitrary<unsigned int>();
    int val = *rc::gen::arbitrary<int>();

    void checkPreconditions(const TAILQ_model &model) const override {
        RC_PRE(!model.list.empty());
    }

    void apply(TAILQ_model &model) const override {
        unsigned int insert_index = index%model.list.size();
        if(insert_index == model.list.size() - 1)
            model.list.push_back(val);
        else
            model.list.insert(model.list.begin() + insert_index + 1, 1, val);
    }

    void run(const TAILQ_model &model, myTAILQueueHead &head) const override {
        auto element_before_insertion = TAILQ_FIRST_impl(&head);
        unsigned int insertion_index = index%model.list.size();
        for(int i = 0; i < insertion_index; i++)
            element_before_insertion = TAILQ_NEXT_impl(element_before_insertion);

        auto element_to_be_inserted = new IntegerTAILQueueNode();
        element_to_be_inserted->data = val;
        TAILQ_INSERT_AFTER_impl(&head, element_before_insertion, element_to_be_inserted);
    }

    void show(std::ostream &os) const override {
        os << "TAILQ_INSERT_AFTER INDEX: "<< index << ", VALUE: " << val;
    }
};

struct remove_element : rc::state::Command<TAILQ_model, myTAILQueueHead> {
    unsigned int index = *rc::gen::arbitrary<unsigned int>();

    void checkPreconditions(const TAILQ_model &model) const override {
        RC_PRE(!model.list.empty());
    }

    void apply(TAILQ_model &model) const override {
        unsigned int removeIndex = index % model.list.size();
        model.list.erase(model.list.begin() + removeIndex);
    }

    void run(const TAILQ_model &model, myTAILQueueHead &head) const override {
        auto elementToRemove = TAILQ_FIRST_impl(&head);
        unsigned int insertion_index = index % model.list.size();
        for(int i = 0; i < insertion_index; i++)
            elementToRemove = TAILQ_NEXT_impl(elementToRemove);

        TAILQ_REMOVE_impl(&head, elementToRemove);
    }

    void show(std::ostream &os) const override {
        os << "TAILQ_REMOVE_ELEMENT "<< index;
    }
};

struct swap : rc::state::Command<TAILQ_model, myTAILQueueHead> {
    std::vector<int> swap_with = *rc::gen::arbitrary<std::vector<int>>();

    void apply(TAILQ_model &model) const override {
        model.list = swap_with;
    }

    void run(const TAILQ_model &model, myTAILQueueHead &head1) const override {
        auto head2 = new myTAILQueueHead();
        TAILQ_INIT_impl(head2);
        IntegerTAILQueueNode* prev_entry;
        for(int i = 0; i< swap_with.size(); i++) {
            auto entry = new IntegerTAILQueueNode();
            entry->data = swap_with.at(i);
            if(i == 0)
                TAILQ_INSERT_HEAD_impl(head2, entry);
            else
                TAILQ_INSERT_AFTER_impl(head2, prev_entry, entry);
            prev_entry = entry;
        }
        TAILQ_SWAP_impl(&head1, head2);
    }

    void show(std::ostream &os) const override {
        os << "TAILQ_SWAP: << ";
        for(auto i: swap_with)
            os << i << ", ";
    }
};

struct concatenate : rc::state::Command<TAILQ_model, myTAILQueueHead> {
    std::vector<int> concatenate_with = *rc::gen::arbitrary<std::vector<int>>();

    void apply(TAILQ_model &model) const override {
        for(auto i: concatenate_with)
        model.list.push_back(i);
    }

    void run(const TAILQ_model &model, myTAILQueueHead &head1) const override {
        auto head2 = new myTAILQueueHead();
        TAILQ_INIT_impl(head2);
        IntegerTAILQueueNode* prev_entry;
        for(int i = 0; i < concatenate_with.size(); i++) {
            auto entry = new IntegerTAILQueueNode();
            entry->data = concatenate_with.at(i);
            if(i == 0)
                TAILQ_INSERT_HEAD_impl(head2, entry);
            else
                TAILQ_INSERT_AFTER_impl(head2, prev_entry, entry);
            prev_entry = entry;
        }
        TAILQ_CONCAT_impl(&head1, head2);
    }

    void show(std::ostream &os) const override {
        os << "TAILQ_CONCAT: << ";
        for(auto i: concatenate_with)
            os << i << ", ";
    }
};

struct empty : rc::state::Command<TAILQ_model, myTAILQueueHead> {
    void run(const TAILQ_model &model, myTAILQueueHead &head1) const override {
        RC_ASSERT(model.list.empty() == TAILQ_EMPTY_impl(&head1));
    }

    void show(std::ostream &os) const override {
        os << "EMPTY";
    }
};

struct foreach : rc::state::Command<TAILQ_model, myTAILQueueHead> {
    void run(const TAILQ_model &model, myTAILQueueHead &head) const override {
        auto entry = TAILQ_FIRST_impl(&head);
        for(int i = 0; i < model.list.size(); i++) {
            RC_ASSERT(model.list.at(i) == entry->data);
            entry = entry->entries.tqe_next;
        }
        RC_ASSERT(entry == nullptr);
    }

    void show(std::ostream &os) const override {
        os << "FOREACH";
    }
};

struct foreach_from : rc::state::Command<TAILQ_model, myTAILQueueHead> {
    unsigned int random_index = *rc::gen::arbitrary<unsigned int>();

    void run(const TAILQ_model &model, myTAILQueueHead &head) const override {
        unsigned int from_index = model.list.empty() ? 0 : random_index % model.list.size();
        auto entry = TAILQ_FIRST_impl(&head);
        for(int i = 0; i < from_index; i++)
            entry = TAILQ_NEXT_impl(entry);

        for(unsigned int i = from_index; i < model.list.size(); i++) {
            RC_ASSERT(model.list.at(i) == entry->data);
            entry = entry->entries.tqe_next;
        }
        RC_ASSERT(entry == nullptr);
    }

    void show(std::ostream &os) const override {
        os << "FOREACH";
    }
};

//RC will generate a sequence of valid operations based on each operations preconditions.
//The results of the operations can are checked with an assumed to be correct model.
TEST(STAILQ_model, sequenceOfOperationsAlwaysResultsInExpectedState){
    RC_ASSERT(rc::check([] {
        TAILQ_model model;
        myTAILQueueHead head{};
        TAILQ_INIT_impl(&head);
        rc::state::check(model,
                         head,
                         rc::state::gen::execOneOfWithArgs<
                                 insert_head
                                ,first
                                ,insert_after
                                ,remove_element
                                ,swap
                                ,concatenate
                                ,empty
                                ,foreach
                                ,foreach_from
                                >());
    }));
};

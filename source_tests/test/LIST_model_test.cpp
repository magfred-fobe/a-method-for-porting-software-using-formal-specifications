//
// Created by Magnus on 4/6/21.
//
#include "gtest/gtest.h"
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>
#include <rapidcheck/state.h>
#include <vector>
#include "../src/queue_impl.h"

struct LIST_model {
    std::vector<int> list;
};

struct LIST_first: rc::state::Command<LIST_model, myLISTHead> {
    void run(const LIST_model &model, myLISTHead &head) const override {
        if(model.list.empty())
            RC_ASSERT(LIST_FIRST_impl(&head) == nullptr);
        else
            RC_ASSERT(LIST_FIRST_impl(&head)->data == model.list.at(0));
    }

    void show(std::ostream &os) const override {
        os << "LIST_FIRST";
    }
};

struct LIST_insert_head : rc::state::Command<LIST_model, myLISTHead> {
    int val = *rc::gen::arbitrary<int>();
    void apply(LIST_model &model) const override {
        model.list.insert(model.list.begin(), 1, val);
        assert(model.list.at(0) == val);
    }

    void run(const LIST_model &model, myLISTHead &head) const override {
        auto entry = new IntegerLISTEntry();
        entry->data = val;
        LIST_INSERT_HEAD_impl(&head, entry);
        RC_ASSERT( LIST_FIRST_impl(&head)->data == val);
    }

    void show(std::ostream &os) const override {
        os << "LIST_INSERT_HEAD VALUE: " << val;
    }
};

struct LIST_insert_after : rc::state::Command<LIST_model, myLISTHead> {
    unsigned int index = *rc::gen::arbitrary<unsigned int>();
    int val = *rc::gen::arbitrary<int>();

    void checkPreconditions(const LIST_model &model) const override {
        RC_PRE(!model.list.empty());
    }

    void apply(LIST_model &model) const override {
        unsigned int insert_index = index%model.list.size();
        if(insert_index == model.list.size() - 1)
            model.list.push_back(val);
        else
            model.list.insert(model.list.begin() + insert_index + 1, 1, val);
    }

    void run(const LIST_model &model, myLISTHead &head) const override {
        auto element_before_insertion = LIST_FIRST_impl(&head);
        unsigned int insertion_index = index%model.list.size();
        for(int i = 0; i < insertion_index; i++)
            element_before_insertion = LIST_NEXT_impl(element_before_insertion);

        auto element_to_be_inserted = new IntegerLISTEntry();
        element_to_be_inserted->data = val;
        LIST_INSERT_AFTER_impl(element_before_insertion, element_to_be_inserted);
    }

    void show(std::ostream &os) const override {
        os << "LIST_INSERT_AFTER INDEX: "<< index << ", VALUE: " << val;
    }
};

struct LIST_remove_element : rc::state::Command<LIST_model, myLISTHead> {
    unsigned int index = *rc::gen::arbitrary<unsigned int>();

    void checkPreconditions(const LIST_model &model) const override {
        RC_PRE(!model.list.empty());
    }

    void apply(LIST_model &model) const override {
        unsigned int removeIndex = index % model.list.size();
        model.list.erase(model.list.begin() + removeIndex);
    }

    void run(const LIST_model &model, myLISTHead &head) const override {
        auto elementToRemove = LIST_FIRST_impl(&head);
        unsigned int insertion_index = index % model.list.size();
        for(int i = 0; i < insertion_index; i++)
            elementToRemove = LIST_NEXT_impl(elementToRemove);

        LIST_REMOVE_impl(elementToRemove);
    }

    void show(std::ostream &os) const override {
        os << "LIST_REMOVE_ELEMENT "<< index;
    }
};

struct LIST_swap : rc::state::Command<LIST_model, myLISTHead> {
    std::vector<int> swap_with = *rc::gen::arbitrary<std::vector<int>>();

    void apply(LIST_model &model) const override {
        model.list = swap_with;
    }

    void run(const LIST_model &model, myLISTHead &head1) const override {
        auto head2 = new myLISTHead();
        LIST_INIT_impl(head2);
        IntegerLISTEntry* prev_entry;
        for(int i = 0; i< swap_with.size(); i++) {
            auto entry = new IntegerLISTEntry();
            entry->data = swap_with.at(i);
            if(i == 0)
                LIST_INSERT_HEAD_impl(head2, entry);
            else
                LIST_INSERT_AFTER_impl(prev_entry, entry);
            prev_entry = entry;
        }
        LIST_SWAP_impl(&head1, head2);
    }

    void show(std::ostream &os) const override {
        os << "LIST_SWAP: << ";
        for(auto i: swap_with)
            os << i << ", ";
    }
};

struct LIST_concatenate : rc::state::Command<LIST_model, myLISTHead> {
    std::vector<int> concatenate_with = *rc::gen::arbitrary<std::vector<int>>();

    void apply(LIST_model &model) const override {
        for(auto i: concatenate_with)
        model.list.push_back(i);
    }

    void run(const LIST_model &model, myLISTHead &head1) const override {
        auto head2 = new myLISTHead();
        LIST_INIT_impl(head2);
        IntegerLISTEntry* prev_entry;
        for(int i = 0; i < concatenate_with.size(); i++) {
            auto entry = new IntegerLISTEntry();
            entry->data = concatenate_with.at(i);
            if(i == 0)
                LIST_INSERT_HEAD_impl(head2, entry);
            else
                LIST_INSERT_AFTER_impl(prev_entry, entry);
            prev_entry = entry;
        }
        LIST_CONCAT_impl(&head1, head2);
    }

    void show(std::ostream &os) const override {
        os << "LIST_CONCAT: << ";
        for(auto i: concatenate_with)
            os << i << ", ";
    }
};

struct LIST_empty : rc::state::Command<LIST_model, myLISTHead> {
    void run(const LIST_model &model, myLISTHead &head1) const override {
        RC_ASSERT(model.list.empty() == LIST_EMPTY_impl(&head1));
    }

    void show(std::ostream &os) const override {
        os << "EMPTY";
    }
};

struct LIST_foreach : rc::state::Command<LIST_model, myLISTHead> {
    void run(const LIST_model &model, myLISTHead &head) const override {
        auto entry = LIST_FIRST_impl(&head);
        for(int i = 0; i < model.list.size(); i++) {
            RC_ASSERT(model.list.at(i) == entry->data);
            entry = entry->entries.le_next;
        }
        RC_ASSERT(entry == nullptr);
    }

    void show(std::ostream &os) const override {
        os << "FOREACH";
    }
};

struct LIST_foreach_from : rc::state::Command<LIST_model, myLISTHead> {
    unsigned int random_index = *rc::gen::arbitrary<unsigned int>();

    void run(const LIST_model &model, myLISTHead &head) const override {
        unsigned int from_index = model.list.empty() ? 0 : random_index % model.list.size();
        auto entry = LIST_FIRST_impl(&head);
        for(int i = 0; i < from_index; i++)
            entry = LIST_NEXT_impl(entry);

        for(unsigned int i = from_index; i < model.list.size(); i++) {
            RC_ASSERT(model.list.at(i) == entry->data);
            entry = entry->entries.le_next;
        }
        RC_ASSERT(entry == nullptr);
    }

    void show(std::ostream &os) const override {
        os << "FOREACH";
    }
};

//RC will generate a sequence of valid operations based on each operations preconditions.
//The results of the operations can are checked with an assumed to be correct model.
TEST(LIST_model, LIST_sequenceTest){
    RC_ASSERT(rc::check([] {
        LIST_model model;
        myLISTHead head{};
        LIST_INIT_impl(&head);
        rc::state::check(model,
                         head,
                         rc::state::gen::execOneOfWithArgs<
                                 LIST_insert_head
                                ,LIST_first
                                ,LIST_insert_after
                                ,LIST_remove_element
                                ,LIST_swap
                                ,LIST_concatenate
                                ,LIST_empty
                                ,LIST_foreach
                                ,LIST_foreach_from
                                >());
    }));
};

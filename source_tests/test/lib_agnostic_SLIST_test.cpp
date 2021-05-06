//
// Created by kali on 4/29/21.
//

#include "gtest/gtest.h"
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>
#include <rapidcheck/state.h>
#include <vector>
#include "lib_impl/LinkedListLib.h"
#include "stdlib.h"

struct SLIST_model {
    std::vector<int> list;
};

//Change this to change what lib is tested
using CurListType = Clib;

///TODO: add check for head value
struct lib_first: rc::state::Command<SLIST_model, LinkedListLib> {
    void run(const SLIST_model &model, LinkedListLib &list) const override {
        if(model.list.empty()) {
            RC_ASSERT(list.empty(list.list_index) == 1);
        }
        else{
            /*RC_ASSERT(list.head(list.list_index) == model.list.at(0));*/
            RC_ASSERT(true);
        }
    }

    void show(std::ostream &os) const override {
        os << "SLIST_FIRST";
    }
};

///TODO: use head/first when it is implemented
struct lib_insert_head : rc::state::Command<SLIST_model, LinkedListLib> {
    int val = *rc::gen::arbitrary<int>();
    void apply(SLIST_model &model) const override {
        model.list.insert(model.list.begin(), 1, val);
        RC_ASSERT(model.list.at(0) == val);
    }

    void run(const SLIST_model &model, LinkedListLib &list) const override {
        list.insert_head(list.list_index, val);
        RC_ASSERT(!list.empty(list.list_index));
        RC_ASSERT( list.head(list.list_index) == val);
    }

    void show(std::ostream &os) const override {
        os << "LIST_INSERT_HEAD VALUE: " << val;
    }
};

struct lib_insert_after : rc::state::Command<SLIST_model, LinkedListLib> {
    unsigned int index = *rc::gen::arbitrary<unsigned int>();
    int val = *rc::gen::arbitrary<int>();

    void checkPreconditions(const SLIST_model &model) const override {
        RC_PRE(!model.list.empty());
    }

    void apply(SLIST_model &model) const override {
        unsigned int insert_index = index % model.list.size();

        if(insert_index == model.list.size() - 1)
            model.list.push_back(val);
        else
            model.list.insert(model.list.begin() + insert_index + 1, 1, val);
    }

    void run(const SLIST_model &model, LinkedListLib &list) const override {
        unsigned int insertion_index = index % model.list.size();
        list.insert_after(list.list_index, insertion_index, val);
        RC_ASSERT(list.value_at_index(list.list_index, insertion_index + 1) == val);
    }

    void show(std::ostream &os) const override {
        os << "SLIST_INSERT_AFTER INDEX: "<< index << ", VALUE: " << val;
    }
};

struct lib_remove_element : rc::state::Command<SLIST_model, LinkedListLib> {
    unsigned int index = *rc::gen::arbitrary<unsigned int>();

    void checkPreconditions(const SLIST_model &model) const override {
        RC_PRE(!model.list.empty());
    }

    void apply(SLIST_model &model) const override {
        unsigned int removeIndex = index % model.list.size();
        model.list.erase(model.list.begin() + removeIndex);
    }

    void run(const SLIST_model &model, LinkedListLib &list) const override {
        unsigned int removeIndex = index % model.list.size();
        int next_val = -1;
        if (model.list.size() > removeIndex + 1) {
            next_val = model.list.at(removeIndex + 1);
        }
        list.remove(list.list_index, removeIndex);
        RC_ASSERT(list.value_at_index(list.list_index, removeIndex) == next_val);
    }

    void show(std::ostream &os) const override {
        os << "SLIST_REMOVE_ELEMENT "<< index;
    }
};

struct lib_remove_after : rc::state::Command<SLIST_model, LinkedListLib> {
    unsigned int index = *rc::gen::arbitrary<unsigned int>();

    void checkPreconditions(const SLIST_model &model) const override {
        RC_PRE(model.list.size() > 1);
    }

    void apply(SLIST_model &model) const override {
        unsigned int remove_index = index % (model.list.size() - 1);
        model.list.erase(model.list.begin() + remove_index + 1);
    }

    void run(const SLIST_model &model, LinkedListLib &list) const override {

        unsigned int remove_index = index % (model.list.size() - 1);

        int next_val = -1;
        if (model.list.size() > remove_index + 2) next_val = model.list.at(remove_index + 2);

        list.remove_after(list.list_index, remove_index);
        RC_ASSERT(list.value_at_index(list.list_index, remove_index + 1) == next_val);
    }

    void show(std::ostream &os) const override {
        os << "SLIST_REMOVE_AFTER "<< index;
    }
};

struct lib_remove_head : rc::state::Command<SLIST_model, LinkedListLib> {
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

    void run(const SLIST_model &model, LinkedListLib &list) const override {
        auto prev_head_val = list.head(list.list_index);
        RC_ASSERT(  prev_head_val == model.list.at(0));
        list.remove_head(list.list_index);
        if (model.list.size() == 1) {
            RC_ASSERT(list.value_at_index(list.list_index, 0) == -1);
        } else {
            auto model_value_after_head = model.list.at(1);
            RC_ASSERT(list.head(list.list_index) == model_value_after_head);
        }
    }

    void show(std::ostream &os) const override {
        os << "SLIST_REMOVE_HEAD";
    }
};

struct lib_swap : rc::state::Command<SLIST_model, LinkedListLib> {
    std::vector<int> swap_with = *rc::gen::arbitrary<std::vector<int>>();

    void apply(SLIST_model &model) const override {
        model.list.clear();
        model.list = swap_with;
    }

    void run(const SLIST_model &model, LinkedListLib &list) const override {
        auto identifier_list_2 = list.init_list();
        for(int i = 0; i< swap_with.size(); i++) {
            if(i == 0)
                list.insert_head(identifier_list_2, swap_with.at(0));
            else
                list.insert_after(identifier_list_2, i-1, swap_with.at(i));
        }
        list.swap(list.list_index, identifier_list_2);
    }

    void show(std::ostream &os) const override {
        os << "SLIST_SWAP: << ";
        for(auto i: swap_with)
            os << i << ", ";
    }
};

struct lib_concatenate : rc::state::Command<SLIST_model, LinkedListLib> {
    std::vector<int> concatenate_with = *rc::gen::arbitrary<std::vector<int>>();

    void apply(SLIST_model &model) const override {
        for(auto i: concatenate_with)
            model.list.push_back(i);
    }

    void run(const SLIST_model &model, LinkedListLib &list1) const override {
        int list2_index = list1.init_list();

        if (!concatenate_with.empty()) {
            list1.insert_head(list2_index, concatenate_with[0]);

            for (int i = 1; i < concatenate_with.size(); i++) {
                list1.insert_after(list2_index, i - 1, concatenate_with.at(i));
            }
        }

        list1.concatenate(list1.list_index, list2_index);

        for (int i = 0; i < model.list.size(); ++i) {
            RC_ASSERT(list1.value_at_index(list1.list_index, i) == model.list[i]);
        }

        if(!concatenate_with.empty()) {
            for (int i = 0; i < concatenate_with.size(); ++i) {
                RC_ASSERT(concatenate_with[i] == list1.value_at_index(list1.list_index, i + model.list.size()));
            }
        }
    }

    void show(std::ostream &os) const override {
        os << "SLIST_CONCAT: << ";
        for(auto i: concatenate_with)
            os << i << ", ";
    }
};

struct lib_empty : rc::state::Command<SLIST_model, LinkedListLib> {
    void run(const SLIST_model &model, LinkedListLib &list) const override {
        RC_ASSERT(model.list.empty() == list.empty(list.list_index));
    }

    void show(std::ostream &os) const override {
        os << "EMPTY";
    }
};

/*
 * Use summing function as proxy for foreach since it is difficult otherwise.
 * For example, nodes of functions would have to be marshalled/referenced between rust and C
 */
struct lib_foreach : rc::state::Command<SLIST_model, LinkedListLib> {
    void run(const SLIST_model &model, LinkedListLib &list) const override {
        auto model_sum = 0;
        for (const auto &value : model.list) {
            model_sum += value;
        }
        auto list_sum = list.foreach_sum(list.list_index);
        RC_ASSERT(model_sum == list_sum);
    }

    void show(std::ostream &os) const override {
        os << "FOREACH";
    }
};

struct lib_foreach_from : rc::state::Command<SLIST_model, LinkedListLib> {

    void checkPreconditions(const SLIST_model &model) const override {
        RC_PRE(!model.list.empty());
    }

    void run(const SLIST_model &model, LinkedListLib &list) const override {
        unsigned int from_index = *rc::gen::arbitrary<unsigned int>() % model.list.size();
        auto model_sum = 0;
        std::for_each(std::begin(model.list) + from_index, std::end(model.list), [&model_sum](int const& value) {
            model_sum += value;
        });

        auto list_sum = list.foreach_from_sum(list.list_index, from_index);
        RC_ASSERT(model_sum == list_sum);
    }

    void show(std::ostream &os) const override {
        os << "FOREACH FROM";
    }
};


TEST(SLIST_model_lib, SLIST_sequenceTest){
    RC_ASSERT(rc::check([] {
        SLIST_model model;
        CurListType list;
        list.list_index = list.init_list();
        rc::state::check(model,
                         list,
                         rc::state::gen::execOneOfWithArgs<
                                 lib_insert_head,
                                 lib_first,
                                 lib_insert_after,
                                 lib_remove_element,
                                 lib_remove_after,
                                 lib_remove_head,
                                 //,SLIST_remove_prevptr
                                 lib_swap,
                                 lib_concatenate,
                                 lib_empty,
                                 lib_foreach,
                                 lib_foreach_from
                         >());
    }));
}
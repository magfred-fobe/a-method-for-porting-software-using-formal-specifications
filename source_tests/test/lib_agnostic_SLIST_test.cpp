//
// Created by kali on 4/29/21.
//

#include "gtest/gtest.h"
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>
#include <rapidcheck/state.h>
#include <vector>

#include "lib_impl/LinkedListLib.h"

struct SLIST_model {
    std::vector<int> list;
};

//Change this to change what lib is tested
using CurListType = RustLib;

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

TEST(SLIST_model_lib, SLIST_sequenceTest){
    RC_ASSERT(rc::check([] {
        SLIST_model model;
        CurListType list;
        list.list_index = list.init_list();
        rc::state::check(model,
                         list,
                         rc::state::gen::execOneOfWithArgs<
                                 lib_insert_head,
                                 lib_first
                                 //,SLIST_insert_after
                                 //,SLIST_remove_element
                                 //,SLIST_remove_after
                                 //,SLIST_remove_head
                                 //,SLIST_remove_prevptr
                                 //,SLIST_swap
                                 //,SLIST_concatenate
                                 //,SLIST_empty
                                 //,SLIST_foreach
                                 //,SLIST_foreach_from
                         >());
    }));
}
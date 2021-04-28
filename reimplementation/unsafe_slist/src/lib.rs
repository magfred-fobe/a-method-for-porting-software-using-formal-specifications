/* Defines external interface for library
 * Fascilitates the language agnostic test suite
 */

use std::sync::Mutex;
use lazy_static::lazy_static;
use std::collections::HashMap;
//Use the crate containing the version to test-
use singly_linked_list_unsafe::singly_linked_list_unsafe_array as list_impl;
use list_impl::LinkedList;
use list_impl::Node;


lazy_static! { static ref LISTS: Mutex<HashMap<i32, LinkedList<i32>>> = Mutex::new(HashMap::new());}

pub fn test() {
    let vector = vec!(1);
    let _test_list = list_impl::linked_list_from(vector);
}

pub fn init_list(identifier: i32) {
    LISTS.lock().unwrap().insert(identifier, LinkedList::new());
}

pub fn insert_head(identifier: i32, value: i32) -> i32 {
    let mut list = LISTS.lock().unwrap();
    match list.get_mut(&identifier) {
        None => -1,
        Some(_val) => {
            let list = list.get_mut(&identifier);
            list.unwrap().insert_head(value);
            0
        }
    }
}

pub fn insert_after(identifier: i32, index: usize, value: i32) -> i32 {
    let mut list = LISTS.lock().unwrap();
    let list = list.get_mut(&identifier);
    if list.is_some() {
        let list  = list.unwrap();
        match list.node_at_index(index) {
            None => -1, 
            Some(node) => {
                list.insert_after(node, value);
                0
            }
        }
    } else {
        -1
    }
}

//extern crate singly_linked_list_unsafe;
//use singly_linked_list_unsafe::*;


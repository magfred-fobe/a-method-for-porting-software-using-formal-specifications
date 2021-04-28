/* Defines external interface for library
 * Fascilitates the language agnostic test suite
 */

use std::sync::Mutex;
use lazy_static::lazy_static;
use std::collections::HashMap;
//Use the crate containing the version to test-
use singly_linked_list_unsafe::singly_linked_list_unsafe as list_impl;
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

pub fn insert_after(identifier: i32, index: i32, value: i32) -> i32 {
    let mut node = LISTS.lock().unwrap();
    let node = node.get_mut(&identifier).unwrap();
    let node = node.head.as_ref();
    
    let mut found_node = node;
    
    let mut list = LISTS.lock().unwrap();
    let list = match list.get_mut(&identifier) {
        None => {return -1},
        Some(val) => val
    };
    
    let node = match node {
        None => {return -1},
        Some(val) => val
    };
    
    
    for _i in 0..index {
        let some = node.next.as_ref().unwrap();
        found_node = Some(some);
    }
    //let y =
    //node.next;
     
    list.insert_after(found_node.unwrap(), value);
    0
}



#[test]
fn test_test() {
    let mut ll: LinkedList<i32> = LinkedList::new();
    ll.insert_head(1);
    ll.insert_head(2);
    let x = ll.get_head_addr();
    ll.insert_after(x, 1);
} 


//extern crate singly_linked_list_unsafe;
//use singly_linked_list_unsafe::*;


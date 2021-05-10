/* Defines external interface for library
 * Fascilitates the language agnostic test suite
 */


mod linked_list_lib {
    use std::mem;
    pub trait BorrowTwoMut<T> {
        fn borrow_two(&mut self, index_1: usize, index_2: usize) -> (Option<&mut T>, Option<&mut T>);
    }
    impl<T> BorrowTwoMut<T> for Vec<T> {
        fn borrow_two(&mut self, mut index_1: usize, mut index_2: usize) -> (Option<&mut T>, Option<&mut T>) {
        if index_1 == index_2 {
            panic!("Can not borrow the same object twice");
        }
        if index_1 > index_2 {
            index_1 = index_1^index_2;
            index_2 = index_1^index_2;
        }
        let (left, right) = self.split_at_mut(index_2);
        let o_1 = left.get_mut(index_1);
        let o_2 = right.get_mut(index_2-index_1);
        (o_1, o_2)
        }
    }

    use std::sync::Mutex;
    use lazy_static::lazy_static;

    //Use the crate containing the version to test-
    use singly_linked_list::singly_linked_list_array as list_impl;
    use list_impl::LinkedList;
    
    lazy_static! { static ref LISTS: Mutex<Vec<LinkedList<i32>>> = Mutex::new(Vec::new());}
    
    #[no_mangle]
    pub extern "C" fn rlib_init_list() -> i32 {
        match LISTS.lock() {
            Ok(mut list) => {
                list.push(LinkedList::new());
                -1 + list.len() as i32
            },
            Err(_) => -1
        }
    }

    #[no_mangle]
    pub extern "C" fn rlib_empty(identifier: usize) -> i32 {
        let list = LISTS.lock().unwrap();
        match list.get(identifier) {
            Some(val) => val.is_empty() as i32,
            None => -1
        }
    }
    
    #[no_mangle]
    ///TODO: head()/first() should be implemented
    pub extern "C" fn rlib_head(identifier: usize) -> i32 {
        let list = LISTS.lock().unwrap();
        match list.get(identifier) {
            Some(list) => match list.head() {
                None => -1,
                Some(head) => head.value 
            }
            None => -1
        }
    }

    #[no_mangle]
    pub extern "C" fn rlib_insert_head(identifier: usize, value: i32) -> i32 {
        let mut list = LISTS.lock().unwrap();
        if let Some(val) = list.get_mut(identifier) {
            val.insert_head(value);
            return 0
        }
        -1
    }
    
    #[no_mangle]
    pub extern "C" fn rlib_insert_after(identifier: usize, index: usize, value: i32) -> i32 {
        let mut list = LISTS.lock().unwrap();
        if let Some(list) = list.get_mut(identifier) {
            if let Ok(Some(node)) = list.node_at_index(index) {        
                return match list.insert_after(node, value) {
                    Ok(_) => 0,
                    _ => -1
                }
            } 
        }
        -1
    }

    #[no_mangle]
    pub extern "C" fn rlib_remove(identifier: usize, index: usize) -> i32 {
        let mut list = LISTS.lock().unwrap();
        if let Some(list) = list.get_mut(identifier) {
            if let Ok(Some(node)) = list.node_at_index(index) {        
                return match list.remove(node) {
                    Ok(_) => 0,
                    _ => -1
                }
            } 
        }
        -1
    }

    #[no_mangle]
    pub extern "C" fn rlib_remove_head(identifier: usize) -> i32 {
        let mut list = LISTS.lock().unwrap();
        if let Some(list) = list.get_mut(identifier+1) {
            if let Ok(_) = list.remove_head() {
                return 0
            }
        }
        -1
    }

    ///TODO: yeah, what to do?
    #[no_mangle]
    pub extern "C" fn rlib_remove_prevptr(identifier: usize, index: usize ) ->  i32 {
        return 0;
    }

    #[no_mangle]
    pub extern "C" fn rlib_swap(identifier_list_1: usize, identifier_list_2: usize ) -> i32 {
        let mut lists = LISTS.lock().unwrap();
        if let (Some(list_1), Some(list_2)) = lists.borrow_two(identifier_list_1, identifier_list_2) {
            LinkedList::swap(list_1, list_2);
            0
        }
        else {
            -1
        }
    }

    #[no_mangle]
    pub extern "C" fn rlib_concatenate(identifier_list_1: usize, identifier_list_2: usize) -> i32 {
        let mut lists = LISTS.lock().unwrap();
        if let (Some(list_1), Some(list_2)) = lists.borrow_two(identifier_list_1, identifier_list_2) {
            LinkedList::concat(list_1, list_2).expect("should work");
            0
        }
        else {
            -1
        }
    }
    
    #[no_mangle]
    pub extern "C" fn rlib_value_at_index(identifier: usize, index: usize) -> i32 {
        let mut lists = LISTS.lock().unwrap();
        match lists.get(identifier) {
            Some(list) => {
                match list.node_at_index(index) {
                    Ok(Some(node)) => node.value,
                    _ => -1
                }
            },
            _ => -1
        }
    }

    #[no_mangle]
    pub extern "C" fn rlib_next(identifier: usize, index: usize) -> i32 {
        let lists = LISTS.lock().unwrap();
        return match lists.get(identifier) {
            Some(list) => {
                match list.node_at_index(index) {
                    Ok(Some(node)) => match list.next(node) {
                        Some(node) => node.value,
                        None => -1
                    },
                    _ => -1
                }
            },
            _ => -1
        }
    }

    pub extern "C" fn rlib_remove_after(identifier: usize, index: usize) -> i32 {
        let mut lists = LISTS.lock().unwrap();
        return match lists.get_mut(identifier) {
            Some(list) => {
                match list.node_at_index(index) {
                    Ok(Some(node)) => match list.remove_after(node) {
                        Ok(_) => 0,
                        _ => -1
                    },
                    _ => -1
                }
            }
            None => -1
        }
    }

    ///TODO: yeah, what to do?
    #[no_mangle]
    pub extern "C" fn rlib_foreach_sum(identifier: usize) -> i32 {
        let mut lists = LISTS.lock().unwrap();
        return match lists.get(identifier) {
            Some(list) => {
                let mut i = 0;
                for x in list.iter() {
                    i += x;
                }
                i
            }
            None => -1
        }
    }

    #[no_mangle]
    pub extern "C" fn rlib_foreach_from_sum(identifier_list_1: usize, index_from: usize) -> i32 {
        return 0;
    }
}

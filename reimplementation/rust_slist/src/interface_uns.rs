/* Defines external interface for library
 * Fascilitates the language agnostic test suite
 */


 mod linked_list_lib {
    use std::fmt::Debug;
    pub trait BorrowTwoMut<T> {
        fn borrow_two(&mut self, index_1: usize, index_2: usize) -> (Option<&mut T>, Option<&mut T>);
    }
    impl<T> BorrowTwoMut<T> for Vec<T> 
    where T: Debug
    {
        fn borrow_two(&mut self, mut index_1: usize, mut index_2: usize) -> (Option<&mut T>, Option<&mut T>) {
        if index_1 == index_2 {
            panic!("Can not borrow the same object twice");
        }
        let mut switch = false;
        if index_1 > index_2 {
            index_1 = index_1^index_2;
            index_2 = index_1^index_2;
            index_1 = index_1^index_2;
            switch = true;
        }
        let (left, right) = self.split_at_mut(index_2);
        let o_1 = left.get_mut(index_1);
        let o_2 = right.get_mut(0);
        
        if switch {
            (o_2, o_1)
        }
        else {
            (o_1, o_2)
        }
        }
    }

    use std::panic;
    use std::sync::Mutex;
    use lazy_static::lazy_static;

    //Use the crate containing the version to test-
    use singly_linked_list::singly_linked_list_unsafe as list_impl;
    use list_impl::LinkedList;
    
    lazy_static! { static ref LISTS: Mutex<Vec<LinkedList<i32>>> = Mutex::new(Vec::new());}
    
    #[no_mangle]
    pub extern "C" fn rlib_uns_init_list() -> i32 {
        match LISTS.lock() {
            Ok(mut list) => {
                list.push(LinkedList::new());
                -1 + list.len() as i32
            },
            Err(_) => -1
        }
    }
        
    #[no_mangle]
    pub extern "C" fn rlib_uns_init_lib() -> i32 {
        match LISTS.lock() {
            Ok(mut list) => {
                list.clear();
                0
            },
            Err(_) => -1
        }
    }

    #[no_mangle]
    pub extern "C" fn rlib_uns_empty(identifier: usize) -> i32 {
        let list = LISTS.lock().unwrap();
        match list.get(identifier) {
            Some(list) => list.is_empty() as i32,
            None => -1
        }
    }
    
    #[no_mangle]
    pub extern "C" fn rlib_uns_head(identifier: usize) -> i32 {
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
    pub extern "C" fn rlib_uns_insert_head(identifier: usize, value: i32) -> i32 {
        let mut list = LISTS.lock().unwrap();
        if let Some(val) = list.get_mut(identifier) {
            val.insert_head(value);
            return 0
        }
        -1
    }
    
    #[no_mangle]
    pub extern "C" fn rlib_uns_insert_after(identifier: usize, index: usize, value: i32) -> i32 {
        let mut list = LISTS.lock().unwrap();
        if let Some(list) = list.get_mut(identifier) {
            if let Ok(node) = list.node_at_index_mut(index) {
                node.insert_after(value); return 0;
            }
            return -1;
        }
        return -1
    }

    #[no_mangle]
    pub extern "C" fn rlib_uns_remove(identifier: usize, index: usize) -> i32 {
        let mut list = LISTS.lock().unwrap();
        if let Some(list) = list.get_mut(identifier) {    
            if let Ok(node) = list.node_at_index(index) {        
                list.remove(node);
                0
            } 
            else {
                -1
            }
        } else {
            -1
        }
    }

    #[no_mangle]
    pub extern "C" fn rlib_uns_remove_head(identifier: usize) -> i32 {
        let mut list = LISTS.lock().unwrap();
        match list.get_mut(identifier) {
             Some(list) => {list.remove_head(); 0},
             None => -1
        }
    }

    ///TODO: implement?
    #[no_mangle]
    pub extern "C" fn rlib_uns_remove_prevptr(identifier: usize, index: usize ) ->  i32 {
        return 0;
    }

    #[no_mangle]
    pub extern "C" fn rlib_uns_swap(identifier_list_1: usize, identifier_list_2: usize ) -> i32 {
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
    pub extern "C" fn rlib_uns_concatenate(identifier_list_1: usize, identifier_list_2: usize) -> i32 {
        let mut lists = LISTS.lock().unwrap();
        if let (Some(list_1), Some(list_2)) = lists.borrow_two(identifier_list_1, identifier_list_2) {
            LinkedList::concat(list_1, list_2);
            0
        } else { -1 }
    }
    
    #[no_mangle]
    pub extern "C" fn rlib_uns_value_at_index(identifier: usize, index: usize) -> i32 {
        let mut lists = LISTS.lock().unwrap();
        match lists.get(identifier) {
            Some(list) => {
                match list.node_at_index(index) {
                    Ok(node) => node.value,
                    _ => -1
                }
            },
            _ => -1
        }
    }

    #[no_mangle]
    pub extern "C" fn rlib_uns_next(identifier: usize, index: usize) -> i32 {
        let lists = LISTS.lock().unwrap();
        return match lists.get(identifier) {
            Some(list) => {
                match list.node_at_index(index) {
                    Ok(node) => match node.next() {
                        Some(node) => node.value,
                        None => -1
                    },
                    _ => -1
                }
            },
            _ => -1
        }
    }

    #[no_mangle]
    pub extern "C" fn rlib_uns_print_list(identifier: usize) -> i32 {
        let mut lists = LISTS.lock().unwrap();
        println!("LIST{}: {:?}", identifier, lists.get(identifier).unwrap());
        0
    }

    #[no_mangle]
    pub extern "C" fn rlib_uns_remove_after(identifier: usize, index: usize) -> i32 {
        let mut lists = LISTS.lock().unwrap();
        return match lists.get_mut(identifier) {
            Some(list) => {
                match list.node_at_index_mut(index) {
                    Ok(node) => {node.remove_after(); 0},
                    _ => -1
                }
            }
            None => -1
        }
    }

    ///TODO: yeah, what to do?
    #[no_mangle]
    pub extern "C" fn rlib_uns_foreach_sum(identifier: usize) -> i32 {
        let lists = LISTS.lock().unwrap();
        return match lists.get(identifier) {
            Some(list) => {
                let mut i = 0;
                for x in list.iter() {
                    i += *x;
                }
                i
            },
            None => -1
        }
    }

    #[no_mangle]
    pub extern "C" fn rlib_uns_foreach_from_sum(identifier: usize, index_from: usize) -> i32 {
        let lists = LISTS.lock().unwrap();
        return match lists.get(identifier) {
            Some(list) => {
                let mut i = 0;
                let mut iter = list.iter();
                for _ in 0..index_from {
                    iter.next();
                }
                for x in iter {
                    i += x;
                }
                i
            },
            None => -1
        }
    }
}

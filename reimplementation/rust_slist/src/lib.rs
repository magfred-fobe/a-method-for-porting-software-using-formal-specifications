/* Defines external interface for library
 * Fascilitates the language agnostic test suite
 */


mod linked_list_lib {

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
    pub extern "C" fn rlib_empty(identifier: u32) -> i32 {
        let list = LISTS.lock().unwrap();
        match list.get(identifier as usize) {
            Some(val) => val.is_empty() as i32,
            None => -1
        }
    }
    
    #[no_mangle]
    ///TODO: head()/first() should be implemented
    pub extern "C" fn rlib_head(identifier: u32) -> i32 {
        let list = LISTS.lock().unwrap();
        match list.get(identifier as usize) {
            Some(list) => match list.head() {
                None => -1,
                Some(head) => head.value 
            }
            None => -1
        }
    }

    #[no_mangle]
    pub extern "C" fn rlib_insert_head(identifier: u32, value: i32) -> i32 {
        let mut list = LISTS.lock().unwrap();
        if let Some(val) = list.get_mut(identifier as usize) {
            val.insert_head(value);
            return 0
        }
        -1
    }
    
    #[no_mangle]
    pub extern "C" fn rlib_insert_after(identifier: u32, index: usize, value: i32) -> i32 {
        let mut list = LISTS.lock().unwrap();
        if let Some(list) = list.get_mut(identifier as usize) {
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
    pub extern "C" fn rlib_remove(identifier: u32, index: usize) -> i32 {
        return 0;
    }

    #[no_mangle]
    pub extern "C" fn rlib_remove_after(identifier: u32, index: usize) -> i32 {
        return 0;
    }

    #[no_mangle]
    pub extern "C" fn rlib_remove_head(identifier: u32) -> i32 {
        return 0;
    }

    ///TODO: yeah, what to do?
    #[no_mangle]
    pub extern "C" fn rlib_remove_prevptr(identifier: u32, index: u32 ) ->  i32{
        return 0;
    }

    #[no_mangle]
    pub extern "C" fn rlib_swap(identifier_list_1: u32, identifier_list2: u32 ) -> i32 {
        return 0;
    }

    #[no_mangle]
    pub extern "C" fn rlib_concatenate(identifier_list_1: u32, identifier_list2: u32 ) -> i32 {
        return 0;
    }
    
    ///TODO: yeah, what to do?
    #[no_mangle]
    pub extern "C" fn rlib_foreach(identifier_list_1: u32 ) -> i32 {
        return 0;
    }

    ///TODO: yeah, what to do?
    #[no_mangle]
    pub extern "C" fn rlib_foreach_from(identifier_list_1: u32 ) -> i32 {
        return 0;
    }
}
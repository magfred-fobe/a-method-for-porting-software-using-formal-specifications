#[allow(dead_code)]
pub mod singly_linked_list_unsafe {

        #[derive(Debug, Clone)]
        pub struct Node<T: Copy> {
            pub value: T,
            pub next: Option<Box<Node<T>>>
        }

        impl <T: Copy> Node<T> {
            pub fn insert_after(mut self, steps_left: i32, val: T){

                match steps_left {
                    0 => {
                    let after_me = Node{next: self.next, value: val};
                    self.next = Some(Box::new(Node{next: Some(Box::new(after_me)), value: val }));
                    },
                    _ => {
                    match self.next {
                        Some(node) => {node.insert_after(steps_left-1, val)},
                        None => {panic!("Can not insert after end of list")}
                    }              
                    } 
                }  
            }
        }


        pub struct LinkedList<T: Copy> {
            pub head: Option<Node<T>>
        }

        impl<T: Copy> LinkedList<T> {
            pub fn get_head_addr(self) -> *const Node<T> {
                let x = self.head.unwrap();
                &x as *const _
            }

            pub fn insert_head(&mut self, val: T) {
                let new_head = match &self.head {
                    Some(h) => Node{value: val, next: Some(Box::new(h.clone()))},
                    None =>  Node{value: val, next: None}
                };
                self.head = Some(new_head); 
            }

            pub fn insert_after(self, index: i32, val: T) {
                    match self.head {
                        None => {panic!("Can not insert after in empty list")},
                        Some(node) => node.insert_after(index, val)
                    }
            }

            pub fn new() -> LinkedList<T> {
                LinkedList{ head: None }
            }
        
    }

        pub fn linked_list_from<T: Copy>(from: Vec<T>) -> LinkedList<T> {
            if from.len() > 0 {
                return LinkedList { head: None }
            } 
            else {
                let mut list = LinkedList{ head: None };
                for val in from.iter().rev(){
                    list.insert_head(*val);
                }
                list
            }
        }


        pub fn init_list<T: Copy>() -> LinkedList<T>{
            LinkedList::new()
        }

    #[cfg(test)]
    //use quickcheck::quickcheck;

    #[allow(dead_code)]
    mod tests {
        use super::*;

        /*  Invariants. These are defined by the model
            and should be true at every step of the algorithm
        */
        fn remove_invariant(_ll: &LinkedList<i32>) -> bool {
            false
        }

        fn valid_list_invariant(_ll: &LinkedList<i32>) -> bool {
            false
        } 

        fn has_last_invariant(_ll : &LinkedList<i32>) -> bool {
            false
        } 

        fn insert_invariant(_ll: &LinkedList<i32>) -> bool {
            false
        }

        fn check_invariants(ll: &LinkedList<i32>) {
            assert!(remove_invariant(ll));
            assert!(valid_list_invariant(ll));
            assert!(has_last_invariant(ll));
        }

        fn prop_insert_head(list: Vec<i32>, new_elem: i32) -> bool {
            let mut linked_list = linked_list_from(list);
            linked_list.insert_head(new_elem);
            let head = linked_list.head;
            assert!(head.is_some());   
            let head = head.unwrap();
            head.value == new_elem
        }



        /*
         * There seems to be a bug in quickcheck
         * if == is used, the number is never given as argument
         * if > is used it is
         * Not actually a bug, the failing function fails fast with a very large number
         * the reason the final failure is 2 is because of shrinkage. 
         */ 

        /**
         * SUCCEEDS
         */
         fn never_fails(num: i32) -> bool {
            print!("never_fails num: {}\n", num);
            num != 2 
        }

        /*
        * FAILS WITH 2
        */
        fn eventually_fails(num: i32) -> bool {
            print!("eventually_fails num: {}\n", num);
            num <= 1
        }

        #[test]
        fn test_linked_list() {}
    }
}


pub mod singly_linked_list_unsafe_array {
    ///TODO: Clean up the messy Ok, Err, Some, None branches. There must be a nicer way.
    use std::fmt::{Debug, Display};
    use std::error::Error;


    #[derive(Debug, Clone)]
    pub struct LinkedListError {
        message: String
    }

    impl Error for LinkedListError {
}

    impl Display for LinkedListError {
        fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
            write!(f, "{}", self.message)
        }
    }

    pub trait LinkedListValue: Debug + Copy + Clone {}
    impl<T> LinkedListValue for T where T: Debug + Copy + Clone {}

    #[derive(Debug, Copy, Clone)]
    pub struct Node<T: LinkedListValue> {
        index: usize, 
        next: Option<usize>,
        pub value: T
    }

    #[derive(Debug)]
    pub struct LinkedList<T: LinkedListValue> {
        nodes: Vec<Node<T>>,
        head: Option<usize>,
        size: usize
    }
    
    impl<T: LinkedListValue> Default for LinkedList<T> {
        fn default() -> Self {
            LinkedList {
                nodes: Vec::new(),
                head: None,
                size: 0,
            }
        }
    }

    impl<T: LinkedListValue> std::fmt::Display for Node<T> {
        fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
            write!(f, "{:?}", self)
        }
    }
    
    impl<T: LinkedListValue> LinkedList<T> {
        pub fn head(&self) -> Option<Node<T>> {
            match self.head {
                None => None,
                Some(index) => Some(self.nodes[index])
            }
        }

        pub fn size(&self) ->  usize {
            self.size
        }

        pub fn next(&self, node: Node<T>) -> Option<Node<T>> {
            match node.next {
                None => None,
                Some(val) => Some(self.nodes[val])
            }
        }

        fn node_at_index(&self, index: usize) -> Result<Option<Node<T>>, LinkedListError> {
            let mut node = match self.head {
                 None => return Err(LinkedListError{message: String::from("Can not find node at index in empty list")}),
                 Some(val) => self.nodes[val] 
            };

            //Use while let instead?
            for _i in 0..index {
                node = match node.next {
                    Some(val) => self.nodes[val],
                    None => return Err(LinkedListError{message: String::from(format!("Unexpected end of list index: {}, size: {}", index, self.size))})
                }
            }
            Ok(Some(node))
        }

        pub fn insert_head(&mut self, val: T) { 
            let old_head = self.head;
            let next_index = self.nodes.len();
            self.nodes.push(Node{next: old_head, value: val, index: next_index});
            self.head = Some(next_index);
            self.size = self.size + 1;
        }

        pub fn insert_after(&mut self, node: Node<T>, val: T) -> Result<(), LinkedListError> {
            if self.size == 0 {
                return Err(LinkedListError{message: String::from("Can not insert into empty list.")});
            } else {

                let mut old_node = self.nodes[node.index];
                let old_node_next = node.next;
                
                let next_index = self.nodes.len();
                old_node.next = Some(next_index);
                self.nodes[old_node.index] = old_node;
                self.nodes.push(Node{next: old_node_next, value: val, index: next_index});
                self.size = self.size + 1;
            }
            Ok(())
        }

        pub fn new() -> Self {
            LinkedList{ nodes: Vec::new(), head: None, ..Default::default()}
        }
    }

    pub fn linked_list_from<T: LinkedListValue>(from: Vec<T>) -> LinkedList<T> {
        if from.len() == 0 {
            return LinkedList::new();
        } 
        else {
            let mut list = LinkedList::new();
            for val in from.iter().rev(){
                list.insert_head(*val);
            }
            list
        }
    }

    #[cfg(test)]
    use quickcheck::quickcheck;
    
    #[allow(dead_code)]
    mod tests {
        use super::*;

        /*  Invariants. These are defined by the model
         *  and should be true at every step of the algorithm
         */
        fn remove_invariant(_ll: &LinkedList<i32>) -> bool {
            true
        }

        fn valid_list_invariant(_ll: &LinkedList<i32>) -> bool {
            true
        } 

        fn has_last_invariant(list : &LinkedList<i32>) -> bool {
            let mut current = list.head();
            for _i in 0..list.size {
                current = match current {
                    Some(node) =>  match node.next {
                        Some(ind) => Some(list.nodes[ind]),
                        None => None
                    },
                    None => return false
                }
            }
            current.is_none()
        } 

        fn insert_invariant(_ll: &LinkedList<i32>) -> bool {
            true
        }

        fn check_invariants(ll: &LinkedList<i32>) -> bool {
            remove_invariant(ll) &&
            valid_list_invariant(ll) &&
            has_last_invariant(ll)
        }

        fn prop_insert_after(list: Vec<i32>, new_elem: i32, index: usize) -> bool {
            if list.len() == 0 {
                return true;
            }
            let mut linked_list = linked_list_from(list);
            let size = linked_list.size();
            let index_in_range = index % size;

            
            if let Ok(Some(node)) =  linked_list.node_at_index(index_in_range)  {
                if let Ok(_) = linked_list.insert_after(node, new_elem) {            
                    if let Ok(Some(node)) = linked_list.node_at_index(index_in_range) {
                            if let Some(node) =  linked_list.next(node) {
                            return node.value == new_elem && check_invariants(&linked_list)                     
                        }
                    }
                }
            }
            false
        } 

        fn prop_insert_head(list: Vec<i32>, new_elem: i32) -> bool {
            let mut linked_list = linked_list_from(list);
            linked_list.insert_head(new_elem);
            if let Some(head_node) = linked_list.head() {
                head_node.value == new_elem
            } else {
                false
            }
        }

        #[test]
        fn test_insert_after_prop() {
            quickcheck(prop_insert_after as fn(Vec<i32>, i32, usize) -> bool);
        }
        #[test]
        fn test_insert_head_prop() {
            quickcheck(prop_insert_head as fn(Vec<i32>, i32) -> bool);
        }
    }
}
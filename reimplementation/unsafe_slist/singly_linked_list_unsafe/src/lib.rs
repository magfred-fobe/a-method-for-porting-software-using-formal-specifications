#[allow(dead_code)]
pub mod singly_linked_list_unsafe {

    #[derive(Debug, Clone)]
    pub struct Node<T: Copy> {
        pub value: T,
        pub next: Option<Box<Node<T>>>
    }

    impl <T: Copy> Node<T> {
        pub fn insert_after(mut self, steps_left: i32, val: T) {
                
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
use quickcheck::quickcheck;

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
    fn test_linked_list() {
        //quickcheck(prop_insert_head as fn(Vec<i32>, i32) -> bool);
        //quickcheck(eventually_fails as fn (i32) -> bool);
        //quickcheck(never_fails as fn (i32) -> bool);

    }
}
}

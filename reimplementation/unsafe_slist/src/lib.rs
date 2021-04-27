mod singly_linked_list {

    #[derive(Debug, Clone)]
    struct Node<T: Copy> {
        value: T,
        next: Option<Box<Node<T>>>
    }


    struct LinkedList<T: Copy> {
    head: Option<Node<T>>
    }

    impl<T: Copy> LinkedList<T> {
        fn InsertHead(&mut self, val: T) {
            let new_head = match &self.head {
                Some(h) => Node{value: val, next: Some(Box::new(h.clone()))},
                None =>  Node{value: val, next: None}
            };
            self.head = Some(new_head); 
        }
    }

#[cfg(test)]
#[macro_use]
use quickcheck::quickcheck;

mod tests {
    use super::*;

    /*  Invariants. These are defined by the model
        and should be true at every step of the algorithm
    */
    fn remove_invariant(ll: &LinkedList<i32>) -> bool{
        false
    }

    fn valid_list_invariant(ll: &LinkedList<i32>) -> bool{
        false
    } 
    
    fn has_last_invariant(ll : &LinkedList<i32>) -> bool {
        false
    } 

    fn insert_invariant(ll: &LinkedList<i32>) -> bool {
        false
    }
    
    fn check_invariants(ll: &LinkedList<i32>) {
        assert!(remove_invariant(ll));
        assert!(valid_list_invariant(ll));
        assert!(has_last_invariant(ll));
    }

    fn linked_list_from<T: Copy>(from: Vec<T>) -> LinkedList<T> {
        if from.len() > 0 {
            return LinkedList {head: None}
        } 
        else {
            let mut list = LinkedList{head: None};
            for val in from.iter().rev(){
                list.InsertHead(*val);
            }
            list
        }
    }

    fn prop_insert_head(list: Vec<i32>, new_elem: i32) {
    }

    #[test]
    fn test_LinkedLlist() {
        quickcheck(prop_insert_head);
    }
}
}
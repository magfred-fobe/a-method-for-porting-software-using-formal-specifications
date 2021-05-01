use std::fmt::Debug;

#[allow(dead_code)]

#[derive(Debug, Clone, PartialEq)]
pub struct Node<T: Copy> {
    pub value: T,
    pub next: Option<Box<Node<T>>>
}

impl <T: Copy> Node<T> {
    pub fn set_value(&mut self, val: T) {
        self.value = val;
    }

    pub fn next_mut(&mut self) -> Option<&mut std::boxed::Box<Node<T>>> {
        self.next.as_mut()
    }
    
    pub fn next(&mut self) -> Option<&std::boxed::Box<Node<T>>> {
        self.next.as_ref()
    }

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

#[derive(Debug, Clone, PartialEq)]
pub struct LinkedList<T: Copy> {
    pub head: Option<Node<T>>
}

impl<T: Copy + Clone + Debug> LinkedList<T> {
    pub fn head_mut(&mut self) -> &mut Option<Node<T>> {
        &mut self.head
    }
    
    pub fn head(&self) -> &Option<Node<T>> {
        &self.head
    }

    pub fn is_empty(&self)-> bool{
        self.head.is_none()
    }


    ///TODO: this one is tricky, is it possible?
    pub fn remove() {}


    fn insert_head(&mut self, value: T) {
        let next = match self.head.clone() {
            None => None,
            Some(val) => Some(Box::new(val)) 
        };
        self.head = Some(Node{ value: value, next: next });
    }

    ///TODO: Should error if empty?
    fn remove_head(&mut self) {
        if let Some(head) = &self.head  {
            self.head = match &head.next {
                Some(next) => Some(*next.clone()),
                None => None
            }
        } 
    }

    fn remove_after(node: &mut Node<T>) {
        node.next = match &node.next {
            Some(val) => val.next.clone(),
            None => None
        };
    }

    fn new() -> LinkedList<T> {
        LinkedList{head: None}
    }
}

pub fn init_list<T: Copy + Clone + Debug>() -> LinkedList<T>{
    LinkedList::new()
}

fn test() {
    let mut list = LinkedList::new();
    list.insert_head(1);
    let mut head = list.head_mut().as_mut().unwrap();
    print!("HEAD VALUE: {}\n", head.value);
    head.value = 6;
    print!("{:?}\n", list);
    let head = list.head().as_ref().unwrap();
    print!("HEAD VALUE: {}\n", head.value);
    list.insert_head(2);
    print!("insert_head(1)\n");
    list.insert_head(1);
    print!("{:?}\n", list);
    let head = list.head_mut().as_mut().unwrap();
    print!("remove_after(head), ({:?})\n", head.clone());
    LinkedList::remove_after(head);
    print!("====\n");
    print!("{:?}\n", list);
    print!("====\n");
    list.remove_head();
    print!("====\n");
    print!("{:?}\n", list);
    print!("====\n");
    list.remove_head();
    print!("====\n");
    print!("{:?}\n", list);
    print!("====\n");
    list.remove_head();
    print!("====\n");
    print!("{:?}\n", list);
    print!("====\n");
}

#[cfg(test)]
//use quickcheck::quickcheck;

#[allow(dead_code)]
mod tests {
    use super::*;

    #[test]
    fn test_node_ref() {
        test();
    }

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



/*
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
*/
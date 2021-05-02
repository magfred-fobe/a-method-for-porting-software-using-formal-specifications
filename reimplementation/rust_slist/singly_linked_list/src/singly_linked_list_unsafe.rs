use std::fmt::Debug;
//use std::sync::Arc;

#[allow(dead_code)]
pub trait LinkedListValue: Debug {}
impl<T> LinkedListValue for T where T: Debug {}

//Box, Rc, or Arc..?
#[derive(Debug, Clone, PartialEq)]
pub struct Node<T: LinkedListValue> {
    pub value: T,
    pub next: Option<Box<Node<T>>>
}

impl <T: LinkedListValue> Node<T> {
    pub fn set_value(&mut self, val: T) {
        self.value = val;
    }

    pub fn insert_after(&mut self, data: T) -> &Node<T> {
        let new_next: Option<Box<Node<T>>>;
        if self.next.is_some() {
           new_next = self.next.take(); 
        } else {
            new_next = None
        }
        let next = &mut self.next;
        *next = Some(Box::new(Node{value: data, next: new_next}));
        next.as_ref().unwrap()
    }

    pub fn next_mut(&mut self) -> Option<&mut std::boxed::Box<Node<T>>> {
        self.next.as_mut()
    }
    
    pub fn next(&self) -> Option<&std::boxed::Box<Node<T>>> {
        self.next.as_ref()
    }

    pub fn insert_before(&mut self, node: *const Self, value: T) -> &Self {
        let next = match &self.next {
            Some(next) => next,
            None => panic!("insertion point not found in list")
        };
        
        if next.as_ref() as *const _ == node {
            self.insert_after(value)
        } else {
            match &mut self.next {
                Some(next) =>  next.insert_before(next.as_ref(), value),
                None => panic!("Insertion point not found in list")
            }
        }
    }

    pub fn size(&self, start: usize) -> usize {
        match &self.next {
            Some(next) => next.size(start+1),
            None => start
        }
    }

    pub fn remove(&mut self, node: *const Self) {
        let next = match &self.next {
            Some(next) => next,
            None => panic!("removal point not found in list")
        };
        
        if next.as_ref() as *const _ == node {
            self.next = match self.next.as_mut() {
                Some(val) => val.next.take(),
                None => None 
            } 
        } else {
            match self.next.as_mut() {
                Some(next) => next.remove(node),
                None => panic!("unexpected end of list")
            } 
        }
    }

    fn remove_after(&mut self) {
        self.next = match &mut self.next {
            Some(val) => val.next.take(),
            None => None
        };
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct LinkedList<T: LinkedListValue> {
    pub head: Option<Node<T>>
}

impl<T: LinkedListValue> LinkedList<T> {
    pub fn size(&self) -> usize {
        match &self.head {
            Some(next) => next.size(1),
            None => 0
        }
    }

    pub fn head_mut(&mut self) -> &mut Option<Node<T>> {
        &mut self.head
    }
    
    pub fn head(&self) -> &Option<Node<T>> {
        &self.head
    }

    pub fn is_empty(&self)-> bool{
        self.head.is_none()
    }

    fn insert_head(&mut self, value: T) {
        let next = match &mut self.head {
            None => None,
            _ => Some(Box::new(self.head.take().unwrap()))//Some(Box::new(val)) 
        };
        self.head = Some(Node{ value: value, next: next });
    }

    ///TODO: Should error if empty?
    fn remove_head(&mut self) {
        self.head = match &mut self.head {
            Some(h) => {
                match h.next {
                    Some(_) => Some(*h.next.take().unwrap()),
                    None => None 
                }
            },
            None => None
        }
    }

    fn remove(&mut self, node: *const Node<T>) {
        if self.head.is_some() {
            if let Some(head) = &self.head {
                if head as *const _ == node {
                    self.remove_head();    
                } else {
                    self.head.as_mut().unwrap().remove(node)
                }
            }
        } else {
            panic!("Can not remove from empty list");
        }
    }


    fn new() -> LinkedList<T> {
        LinkedList{head: None}
    }

    fn insert_before(&mut self, node: *const Node<T>, value: T) -> &Node<T> {
        if self.head.is_some() {
            self.head.as_mut().unwrap().insert_before(node, value)
        } else {
            panic!("Can not insert into empty list");
        }
    }

    pub fn concat(list_1: &mut LinkedList<T>, list_2: &mut LinkedList<T>) {
        if let Some(head_1) = &mut list_1.head {
            let mut current = &mut head_1.next; 
            while let Some(c) =  current  {
                current = &mut c.next; 
            }
            match &list_2.head {
                Some(_) => *current = Some(Box::new(list_2.head.take().unwrap())),
                None => {}
            }
        } else {
            *&mut list_1.head = list_2.head.take();
        }
    }

    pub fn node_at_index(&self, index: usize) -> &Node<T> {
        let current = &self.head;
        if index == 0 {
            return match current {
                Some(head) => &head,
                _ => panic!("can not get at index of empty list")
            };
        }
        let mut current = match &self.head {
            Some(c) => &c.next,
            None => panic!("")
        };
        for _ in 1..index {
            current = match current {
                Some(c) => &c.next,
                None => panic!("unexpected end of list")    
            }
        }
        match current {
            Some(c) => c,
            None => panic!("unsecpected end of list")
        }
    }

    pub fn node_at_index_mut(&mut self, index: usize) -> &mut Node<T> {
        let panic_msg = "unexpected end of list";
        //Why cant i just unwrap_or_else after checking head is some?
        //Why must i match over and over and over and over? 
        if index == 0 {
            return match &mut self.head {
                Some(head) => head,
                None => panic!("can not get at index of empty list")
            };
        }
        
        match &mut self.head {
            Some(c) => {
                let mut current = c.next_mut();
                let mut ret: Option<&mut Box<Node<T>>> = None;  
                for i in 1.. {
                    if let Some(c) = current {
                        if i == index {
                            ret = Some(c);
                            break;
                        }
                            current = c.next_mut();
                        } else {
                            panic!(panic_msg)
                        }
                    }
                    ret.unwrap()
                },
            None => panic!(panic_msg)
        }
    }

    pub fn swap(list_1: &mut LinkedList<T>, list_2: &mut LinkedList<T>) {
        std::mem::swap(list_1, list_2)
    }

    pub fn init_list() -> LinkedList<T>{
        LinkedList::new()
    }

    pub fn linked_list_from(from: &Vec<T>) -> LinkedList<T>
        where T: Copy + Debug {
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
}

fn test() {
    {
        let list = vec!(0,0);
        let size = list.len();
        let index = 0;
        let new_elem = 3;
        if list.len() == 0 {
            return
        }
        let mut linked_list = LinkedList::linked_list_from(&list);
        let size = linked_list.size();
        let index_in_range = index % size;
        
        let node = linked_list.node_at_index_mut(index_in_range);
        node.insert_after(new_elem);             
        let node_a = node as *const _;
        let node: &Node<i32>;
        unsafe {
            node = &*node_a;
        }
        linked_list.node_at_index(index_in_range);
        let node = match node.next() {
            Some(c) => c,
            None => panic!("WHAT ARE YOU DOING BITCH") 
        };
        assert!(node.value == new_elem);     //&& check_invariants(&linked_list)

    }
    {
        let mut l1: LinkedList<i32> = LinkedList::new();
        let mut l2: LinkedList<i32> = LinkedList::new();
        l1.insert_head(3);
        l1.insert_head(2);
        l1.insert_head(1);
        l2.insert_head(5);
        l2.insert_head(4);
        LinkedList::concat(&mut l1, &mut l2);
        //print!("\nLIST1: {:?}", l1);
        //print!("\nLIST2: {:?}\n", l2);
        LinkedList::swap(&mut l1, &mut l2);
        //print!("\nLIST1: {:?}", l1);
        //print!("\nLIST2: {:?}\n", l2);
        
        return;
    }
    let mut l1: LinkedList<i32> = LinkedList::new();
    l1.insert_head(1);
    let n1 = l1.head_mut().as_mut().unwrap();
    let n2 = n1.insert_after(23);
    let n2 = n2 as *const _;
    let n4 = l1.insert_before(n2, 90);
    let n4_next = n4.next();
    print!("\n===n4:        {:?}===\n", n4);
    print!("\n===n4_next:   {:?}===\n", n4_next);
    print!("\n\n\n{:?}\n", l1);
    let n3: &Node<i32>;
    unsafe {
        n3 = &*n2;
    }
    print!("\n===n3:    {:?}===\n", n3);
    //return;
    let mut n1 = Node{value: 1, next: Some(Box::new(Node{value: 5, next:None}))};
    n1.insert_after(12232);
    print!("\n{:?}\n", n1);
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
    head.remove_after();
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
use quickcheck::quickcheck;

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

    ///TODO: Every element in list_1, list_2 is present in linked_list_1 as part of property
    fn prop_concat(list_1: Vec<i32>, list_2: Vec<i32>) -> bool {
        let mut linked_list_1: LinkedList<i32> = LinkedList::linked_list_from(&list_1);
        let mut linked_list_2: LinkedList<i32> = LinkedList::linked_list_from(&list_2);
        LinkedList::concat(&mut linked_list_1, &mut linked_list_2);
        linked_list_2.size() == 0 &&
        linked_list_1.size() == list_1.len() + list_2.len()
    }

    ///TODO: Check someting about the content of the lists
    fn prop_swap(list_1: Vec<i32>, list_2: Vec<i32>) -> bool {
        let mut linked_list_1: LinkedList<i32> = LinkedList::linked_list_from(&list_1);
        let mut linked_list_2: LinkedList<i32> = LinkedList::linked_list_from(&list_2);
        LinkedList::swap(&mut linked_list_1, &mut linked_list_2);
        linked_list_2.size() == list_1.len() &&
        linked_list_1.size() == list_2.len()
    }

    fn prop_is_empty(list: Vec<i32>) -> bool {   
        let linked_list: LinkedList<i32> = LinkedList::linked_list_from(&list);
        (list.len() == 0) == linked_list.is_empty() 
    }

    fn prop_remove(list: Vec<i32>, index: usize) -> bool {    
        if list.len() == 0 {
            return true
        }
        let mut linked_list: LinkedList<i32> = LinkedList::linked_list_from(&list);
        let size = list.len();
        let index_in_range = index % size;
        let node = linked_list.node_at_index(index_in_range);
        linked_list.remove(node);             
        linked_list.size() == size - 1
    }

    fn prop_insert_after(list: Vec<i32>, new_elem: i32, index: usize) -> bool {
        if list.len() == 0 {
            return true;
        }
        let mut linked_list = LinkedList::linked_list_from(&list);
        let size = linked_list.size();
        let index_in_range = index % size;
        let node = linked_list.node_at_index_mut(index_in_range);
        node.insert_after(new_elem);             
        let node_a = node as *const _;
        let node: &Node<i32>;
        unsafe {
            node = &*node_a;
        }
        linked_list.node_at_index(index_in_range);
        let node = match node.next() {
            Some(c) => c,
            None => panic!("WHAT ARE YOU DOING BITCH") 
        };
        node.value == new_elem //&& check_invariants(&linked_list)
        }

    #[test]
    fn test_insert_after_prop() {
        quickcheck(prop_insert_after as fn(Vec<i32>, i32, usize) -> bool);
    }

    #[test]
    fn test_insert_head_prop() {
        //quickcheck(prop_insert_head as fn(Vec<i32>, i32) -> bool);
    }

    #[test]
    fn test_is_empty_prop() {
        quickcheck(prop_is_empty as fn(Vec<i32>)-> bool);
    }

    #[test]
    fn test_concat_prop() {
        quickcheck(prop_concat as fn(Vec<i32>, Vec<i32>)-> bool);
    }


    #[test]
    fn test_swap_prop() {
        quickcheck(prop_swap as fn(Vec<i32>, Vec<i32>)-> bool);
    }

    #[test]
    fn test_remove_prop() {
        //println!("prop success: {}", prop_remove(vec!(0,0), 255));
        quickcheck(prop_remove as fn(Vec<i32>, usize) -> bool);
    }
}

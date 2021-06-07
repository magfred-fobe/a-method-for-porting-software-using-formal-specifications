use std::fmt::Debug;
use std::error::Error;
use std::fmt::Display;

#[allow(dead_code)]

impl<T> LinkedListValue for T where T: Debug {}

#[derive(Debug)]
pub struct LinkedListError {
    message: String
}
impl Error for LinkedListError {}

impl LinkedListError {
    fn new<S: Into<String>>(msg: S) -> LinkedListError{
        LinkedListError{message: msg.into()}
    }
}

impl Display for LinkedListError {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "{}", self.message)
    }
}

type LinkedListResult<T> = Result<T, LinkedListError>;


pub trait LinkedListValue: Debug {}

//Box, Rc, or Arc..?
#[derive(Debug, PartialEq)]
pub struct Node<T: LinkedListValue> {
    pub value: T,
    pub next: Option<Box<Node<T>>>
}

#[derive(Debug, PartialEq)]
pub struct LinkedList<T: LinkedListValue> {
    pub head: Option<Node<T>>,
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

    fn insert_before(&mut self, node: *const Self, value: T) -> &Self {
        let next = match &self.next {
            Some(next) => next,
            None => panic!("insertion point not found in list")
        };
        if next.as_ref() as *const _ == node {
            self.insert_after(value)
        } else {
            match &mut self.next {
                Some(next) =>  next.insert_before(node, value),
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

    pub fn remove_after(&mut self) {
        self.next = match &mut self.next {
            Some(val) => val.next.take(),
            None => None
        };
    }
}

impl<T: LinkedListValue> LinkedList<T> {
    pub fn size(&self) -> usize {
        match &self.head {
            Some(next) => next.size(1),
            None => 0
        }
    }

    pub fn borrowcheckertester(&mut self, v: T) -> Box<Node<T>> {
        Box::new(Node{next: None, value: v})
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

    pub fn insert_head(&mut self, value: T) {
        let next = match &mut self.head {
            None => None,
            _ => Some(Box::new(self.head.take().unwrap()))//Some(Box::new(val)) 
        };
        self.head = Some(Node{ value: value, next: next });
    }

    pub fn remove_head(&mut self) {
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

    pub fn remove(&mut self, node: *const Node<T>) {
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

    pub fn new() -> LinkedList<T> {
        LinkedList{head: None}
    }

    pub fn insert_before(&mut self, node: *const Node<T>, value: T) {
        if self.head.is_some() {
            let head = self.head.as_mut().unwrap();
            if node == head as *const _ {
                self.insert_head(value);
            } else
            {
                head.insert_before(node, value);
            } 
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
            list_1.head = list_2.head.take();
        }
    }

    pub fn node_at_index(&self, index: usize) -> LinkedListResult<&Node<T>> {
        let current = &self.head;
        if index == 0 {
            return match current {
                Some(head) => Ok(&head),
                _ => Err(LinkedListError::new("can not get at index of empty list"))
            };
        }
        let mut current = match &self.head {
            Some(c) => &c.next,
            None => return Err(LinkedListError::new("can not get at index of empty list"))
        };
        for _ in 1..index {
            current = match current {
                Some(c) => &c.next,
                None => return Err(LinkedListError::new("unexpected end of list"))    
            }
        }
        match current {
            Some(c) => Ok(c),
            None => Err(LinkedListError::new("unexpected end of list"))
        }
    }

    pub fn node_at_index_mut(&mut self, index: usize) -> LinkedListResult<&mut Node<T>> {
        let panic_msg = "unexpected end of list";
        if index == 0 {
            return match &mut self.head {
                Some(head) => Ok(head),
                None => Err(LinkedListError::new("can not get at index of empty list"))
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
                            return Err(LinkedListError::new(panic_msg));
                        }
                    }
                    Ok(ret.unwrap())
                },
            None => panic!("{}", panic_msg)
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
            for val in from.iter().rev() {
                list.insert_head(*val);
            }
            list
        }
    }
    
    pub fn iter(&self) -> Iter<T> {
        match &self.head {
            Some(node) => {
            Iter { current: Some(node) }
            },
            None => Iter { current: None}
        }
    }
}

pub struct Iter<'a, T: LinkedListValue> {
    current: Option<&'a Node<T>>
}

impl<'a, T: LinkedListValue> Iterator for Iter<'a, T> {
    type Item = &'a T;

    #[inline]
    fn next(&mut self) -> Option<Self::Item> {
        if self.current.is_some() {
            let val = Some(&self.current.unwrap().value);
            let next = match &self.current.unwrap().next {
                Some(node) => {
                    Some(node.as_ref())
                },
                None => None
            };
            self.current = next;
            val
        } 
        else
        {
            None
        }
    }
}


#[cfg(test)]
use quickcheck::quickcheck;

#[allow(dead_code)]
mod tests {
    use super::*;

    fn prop_concat(list_1: Vec<i32>, list_2: Vec<i32>) -> bool {
        let mut linked_list_1 = LinkedList::linked_list_from(&list_1);
        let mut linked_list_2 = LinkedList::linked_list_from(&list_2);
        LinkedList::concat(&mut linked_list_1, &mut linked_list_2);        
        let mut i = 0;
        for x in linked_list_1.iter() {
            if i < list_1.len() {
                if *x != list_1[i] { return false; }
            } else {
                if *x != list_2[i-list_1.len()] { return false; }
            }
            i += 1;
        }
        linked_list_2.size() == 0 &&
        linked_list_1.size() == list_1.len() + list_2.len() 
    }

    
    fn prop_swap(list_1: Vec<i32>, list_2: Vec<i32>) -> bool {
        let mut linked_list_1: LinkedList<i32> = LinkedList::linked_list_from(&list_1);
        let mut linked_list_2: LinkedList<i32> = LinkedList::linked_list_from(&list_2);
        LinkedList::swap(&mut linked_list_1, &mut linked_list_2);
        let mut i = 0;
        for x in linked_list_1.iter() {
            if *x != list_2[i] {
                return false;
            } 
            i += 1;
        }
        let mut i = 0;
        for x in linked_list_2.iter() {
            if *x != list_1[i] {
                return false;
            } 
            i += 1;
        }
        linked_list_2.size() == list_1.len() &&
        linked_list_1.size() == list_2.len()
    }

    fn prop_is_empty(list: Vec<i32>) -> bool {   
        let linked_list: LinkedList<i32> = LinkedList::linked_list_from(&list);
        (list.len() == 0) == linked_list.is_empty() 
    }

    fn prop_insert_head(list: Vec<i32>, new_elem: i32) -> bool {
        let mut linked_list: LinkedList<i32> = LinkedList::linked_list_from(&list);
        linked_list.insert_head(new_elem);
        linked_list.head().as_ref().unwrap().value == new_elem
    }

    fn prop_remove(list: Vec<i32>, index: usize) -> bool {    
        if list.len() == 0 {
            return true
        }
        let mut linked_list: LinkedList<i32> = LinkedList::linked_list_from(&list);
        let size = list.len();
        let index_in_range = index % size;
        let node = match linked_list.node_at_index(index_in_range) {
            Ok(node) => node,
            _ => return false
        };
        linked_list.remove(node);
        linked_list.size() == size - 1
    }

    fn prop_remove_after(list: Vec<i32>, index: usize) -> bool {    
        if list.len() < 2 {
            return true
        }
        let mut succeed = true;
        let mut linked_list: LinkedList<i32> = LinkedList::linked_list_from(&list);
        let size = list.len();
        let index_in_range = index % (size-1);
        let node = match linked_list.node_at_index_mut(index_in_range) {
            Ok(node) => node,
            _ => return false
        };
        node.remove_after();             
        succeed &= linked_list.size() == size - 1;

        if index_in_range < size -2 {
            let next = match linked_list.node_at_index(index_in_range+1) {
                Ok(node) => node,
                _ => return false
            };
            let actual_next = list[index_in_range+2];
            succeed &= next.value == actual_next; 
        }
        succeed
    }

    fn prop_insert_after(list: Vec<i32>, new_elem: i32, index: usize) -> bool {
        if list.len() == 0 {
            return true;
        }
        let mut linked_list = LinkedList::linked_list_from(&list);
        let size = linked_list.size();
        let index_in_range = index % size;
        let node = match linked_list.node_at_index_mut(index_in_range) {
            Ok(node) => node,
            _ => return false
        };
        node.insert_after(new_elem);             
        let node = match node.next() {
            Some(c) => c,
            None => panic!("ERROR") 
        };
        node.value == new_elem
    }

    fn prop_insert_before(list: Vec<i32>, new_elem: i32, index: usize) -> bool {
        if list.len() == 0 {
            return true;
        }
        let mut linked_list = LinkedList::linked_list_from(&list);
        let size = linked_list.size();
        let index_in_range = index % size;
        let node = match linked_list.node_at_index_mut(index_in_range) {
            Ok(node) => node as *const _,
            _ => return false
        };
        linked_list.insert_before(node, new_elem);             

        match linked_list.node_at_index(index_in_range) {
            Ok(actual) => actual.value == new_elem,
            _ => false
        }
        
    }

    fn prop_foreach(list: Vec<i32>) -> bool {
        let mut i = 0;
        let linked_list = LinkedList::linked_list_from(&list);
        for x in linked_list.iter() {
            if list[i] != *x {
                return false;
            }
            i += 1;
        }
        true
    }

    #[test]
    fn test_insert_after_prop() {
        quickcheck(prop_insert_after as fn(Vec<i32>, i32, usize) -> bool);
    }

    #[test]
    fn test_insert_before_prop() {
        quickcheck(prop_insert_before as fn(Vec<i32>, i32, usize) -> bool);
    }

    #[test]
    fn test_insert_head_prop() {
        quickcheck(prop_insert_head as fn(Vec<i32>, i32) -> bool);
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
        quickcheck(prop_remove as fn(Vec<i32>, usize) -> bool);
    }

    #[test]
    fn test_remove_after_prop() {
        quickcheck(prop_remove_after as fn(Vec<i32>, usize) -> bool);
    }
    
    #[test]
    fn test_foreach_prop() {
        quickcheck(prop_foreach as fn(Vec<i32>) -> bool);
    }
}

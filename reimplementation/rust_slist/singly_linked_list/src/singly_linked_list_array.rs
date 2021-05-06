#[allow(dead_code)]
///TODO: Clean up the messy Ok, Err, Some, None branches. There must be a nicer way.
use std::fmt::{Debug, Display};
use std::error::Error;
use std::mem;


#[derive(Debug, Clone)]
pub struct LinkedListError {
    message: String
}
impl Error for LinkedListError {}

type LinkedListResult<T> = Result<T, LinkedListError>;

impl Display for LinkedListError {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "{}", self.message)
    }
}

pub trait LinkedListValue: Debug + Copy + Clone {}
impl<T> LinkedListValue for T where T: Debug + Copy + Clone {}

#[derive(Debug, Copy, Clone, PartialEq)]
pub struct Node<T: LinkedListValue> {
    index: usize, 
    next: Option<usize>,
    pub value: T
}

#[derive(Debug)]
pub struct LinkedList<T: LinkedListValue> {
    nodes: Vec<Node<T>>,
    head: Option<usize>,
    size: usize,
    freeindex: Vec<usize>
}

impl<T: LinkedListValue> Default for LinkedList<T> {
    fn default() -> Self {
        LinkedList {
            nodes: Vec::new(),
            head: None,
            size: 0,
            freeindex: Vec::new()
        }
    }
}

impl<T: LinkedListValue> std::fmt::Display for Node<T> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{:?}", self)
    }
}

impl<T: LinkedListValue> LinkedList<T> {
    pub fn remove_head(&mut self) -> LinkedListResult<()> {
        Ok(())
    }

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
    pub fn node_at_index(&self, index: usize) -> LinkedListResult<Option<Node<T>>> {
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

    pub fn is_empty(&self)-> bool{
        self.size == 0
    }

    pub fn insert_head(&mut self, val: T) { 
        let old_head = self.head;
        let next_index = self.nodes.len();
        self.nodes.push(Node{next: old_head, value: val, index: next_index});
        self.head = Some(next_index);
        self.size = self.size + 1;
    }

    pub fn insert_after(&mut self, node: Node<T>, val: T) -> LinkedListResult<Node<T>> {
        if self.size == 0 {
            return Err(LinkedListError{message: String::from("Cannot insert into empty list.")});
        } else {

            let mut old_node = self.nodes[node.index];
            let old_node_next = node.next;
            
            let next_index = self.nodes.len();
            old_node.next = Some(next_index);
            self.nodes[old_node.index] = old_node;
            let node = Node{next: old_node_next, value: val, index: next_index};
            self.nodes.push(node);
            self.size = self.size + 1;
            Ok(node)
        }
    }

    pub fn remove(&mut self, node: Node<T>) -> LinkedListResult<()> {
        if self.size() == 0 {
            return Err(LinkedListError{message: String::from("Cannot remove element from empty list.")});
        }else if node.index > self.nodes.len() {
            return Err(LinkedListError{message: String::from("Cannot remove element from index out of bounds.")}); 
        }

        let ishead = match self.head(){
                Some(h) => if h.index == node.index {
                                self.head = node.next;  
                                self.nodes[h.index].next = None;
                                true
                            }else{
                                false
                            },
                _ => false
        };
  
        if !ishead {
            let mut newnextindex: Option<usize> = None;
            for elem in &self.nodes {
                if let Some(n) = elem.next{
                    if n == node.index {
                            newnextindex = Some(elem.index);
                            break;
                        }
                }
            }

            match newnextindex {
                 Some(index) => {self.nodes[index].next = node.next;
                                 self.nodes[node.index].next = None;               
                },
                 None => {}
            }
        }
        
        self.freeindex.push(node.index);   
        self.size = self.size - 1;
        Ok(())
    }

    
    pub fn swap(list_1: &mut Self, list_2: &mut Self) {
        mem::swap(list_1, list_2)
    }

    pub fn concat(list_1: &mut Self, list_2: &mut Self) -> LinkedListResult<()>  {    
        let mut list_1_end = match list_1.node_at_index(list_1.size()) {
            Ok(Some(node)) => node,
            Ok(None) => {
                mem::swap(list_1, list_2);
                return Ok(())
            },
            Err(e) => return Err(e) 
        };
        
        while let Some(next) = list_2.head() {
            if let Ok(new_end) = list_1.insert_after(list_1_end, next.value) {
                list_1_end = new_end; 
                match list_2.remove_head() {
                    Ok(_) => {},
                    _ => return Err(LinkedListError{message: String::from("Error concatenating lists")})
                }
            }
        }
        Ok(())
    }

    pub fn new() -> Self {
        LinkedList{ nodes: Vec::new(), head: None, ..Default::default()}
    }
}

pub fn linked_list_from<T: LinkedListValue>(from: &Vec<T>) -> LinkedList<T> {
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
        let mut linked_list = linked_list_from(&list);
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
        let mut linked_list = linked_list_from(&list);
        linked_list.insert_head(new_elem);
        if let Some(head_node) = linked_list.head() {
            head_node.value == new_elem
        } else {
            false
        }
    }

    fn prop_is_empty(list: Vec<i32>) -> bool {
        
        let linked_list = linked_list_from(&list);
                
        if list.len() == 0 {
            linked_list.is_empty()
        }else{
            linked_list.is_empty() == false
        }
    }

    fn prop_remove(list: Vec<i32>, index: usize) -> bool {
        
        if list.len() == 0 {
            return true
        }

        let mut linked_list = linked_list_from(&list);
        let size = linked_list.size();
        let index_in_range = index % size;
       
        if let Ok(Some(node)) = linked_list.node_at_index(index_in_range){
            if let Ok(_) = linked_list.remove(node){                  
                let newsize = linked_list.size();
                for  elem in linked_list.nodes {  
                    if let Some(next) = elem.next {
                        if next == node.index{
                            return false
                        }else if linked_list.freeindex[0] != node.index{
                            return false
                        }
                    }
                }
                return newsize == size - 1
            }
        }
    
        false  
    }

    #[test]
    fn test_insert_after_prop() {
        quickcheck(prop_insert_after as fn(Vec<i32>, i32, usize) -> bool);
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
    fn test_remove_prop() {
        //quickcheck(prop_remove as fn(Vec<i32>, usize) -> bool);
    }
}
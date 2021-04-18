----------------------------- MODULE LinkedList -----------------------------
LOCAL INSTANCE TLC
LOCAL INSTANCE FiniteSets
LOCAL INSTANCE Sequences
LOCAL INSTANCE Integers
          
CONSTANTS NULL, VALUE
                
PointerMaps(domain) == 
    [domain -> [value: {VALUE}, next: domain \union {NULL}]]
    
Range(f) == 
    {f[x]["next"]: x \in DOMAIN f}
    
Ring(LL)  ==  
    (DOMAIN  LL  =  Range(LL))
    
First(LL) ==
    IF Ring(LL)THEN Assert(FALSE, "A Linked List Cannot be a ring")  
    ELSE CHOOSE node \in DOMAIN LL:node \notin Range(LL)
    
Cyclic(LL) == 
    NULL \notin Range(LL)
    
isLinkedList(PointerMap) ==
    LET nodes == DOMAIN PointerMap 
        all_seqs == [1..Cardinality(nodes) -> nodes]
        localRange(f) == {f[x]: x \in DOMAIN f}
    IN \E ordering \in all_seqs: 
        /\ \A i \in 1..Len(ordering) - 1: PointerMap[ordering[i]]["next"] = ordering[i+1]
        /\ nodes \subseteq localRange(ordering)
        /\ Cyclic(PointerMap) = FALSE
        /\ Ring(PointerMap) = FALSE
        
LinkedLists(Nodes) ==   
    IF NULL \in Nodes THEN Assert(FALSE, "Null cannot be in Nodes") 
    ELSE CHOOSE pm \in PointerMaps(Nodes) : isLinkedList(pm)

============================================================================

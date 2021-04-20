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
 
\*  LET head == CHOOSE h \in DOMAIN PointerMap: ~\E el \in DOMAIN PointerMap: PointerMap[el]["next"] = h 
    
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

isll(PointerMap) ==
    IF Cyclic(PointerMap) = FALSE /\ Ring(PointerMap) = FALSE THEN
      \*  LET head == CHOOSE h \in DOMAIN PointerMap: ~\E el \in DOMAIN PointerMap: PointerMap[el]["next"] = h
         \A el \in ((DOMAIN PointerMap \union {NULL}) \ {First(PointerMap)}): \E x \in DOMAIN PointerMap : PointerMap[x]["next"] = el  /\ el /= x
    ELSE
        FALSE
       \* \E el \in DOMAIN PointerMap : PointerMap[el]["next"] = NULL
     
 
LinkedLists(Nodes) ==   
    IF NULL \in Nodes THEN Assert(FALSE, "Null cannot be in Nodes") 
    ELSE CHOOSE pm \in PointerMaps(Nodes) : isLinkedList(pm)
    
ll(Nodes) == 
    IF NULL \in Nodes THEN Assert(FALSE, "Null cannot be in Nodes") 
    ELSE { pm \in PointerMaps(Nodes) : isll(pm)}

============================================================================

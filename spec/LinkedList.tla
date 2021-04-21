----------------------------- MODULE LinkedList -----------------------------
LOCAL INSTANCE TLC
LOCAL INSTANCE FiniteSets
LOCAL INSTANCE Sequences
LOCAL INSTANCE Integers
          
CONSTANTS NULL, VALUE
                
PointerMaps(domain) == 
    [domain -> [value: VALUE, next: domain \union {NULL}]]
    
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

\* A list may not contain cyclic references
isll(PointerMap) ==
    Cyclic(PointerMap) = FALSE 
    /\ Ring(PointerMap) = FALSE
    /\ \A el \in ((DOMAIN PointerMap \union {NULL}) \ {First(PointerMap)}): \E x \in DOMAIN PointerMap : PointerMap[x]["next"] = el  /\ el /= x

Empty(l) == 
    Cardinality(DOMAIN l) = 1 /\ \E el \in DOMAIN l: el = "NULL"

EmptyList == 
    [NULL |-> [next |-> NULL, value |-> NULL]]

LinkedLists(Nodes) ==   
    IF NULL \in Nodes THEN Assert(FALSE, "Null cannot be in Nodes") 
    ELSE 
    CHOOSE pm \in PointerMaps(Nodes) : isLinkedList(pm)
    
\* The empty list is a list with an empty domain
ll(Nodes) == 
    IF NULL \in Nodes 
        THEN Assert(FALSE, "Null cannot be in Nodes") 
    ELSE
        IF Nodes \subseteq {}
            THEN EmptyList
        ELSE
            CHOOSE pm \in PointerMaps(Nodes) : isll(pm)

============================================================================
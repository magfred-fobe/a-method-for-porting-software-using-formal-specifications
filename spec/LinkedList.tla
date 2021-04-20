----------------------------- MODULE LinkedList -----------------------------
LOCAL INSTANCE TLC
LOCAL INSTANCE FiniteSets
LOCAL INSTANCE Sequences
LOCAL INSTANCE Integers

          
CONSTANTS VALUE, NULL
 
               
PointerMaps(domain) == 
    [domain -> [value: {VALUE}, next: domain \union {NULL}]]
    
Range(f) == 
    {f[x]["next"]: x \in DOMAIN f}
    
Ring(LL)  ==  
    (DOMAIN  LL  =  Range(LL))

IsNull(v) == 
    v \in {0, NULL}
    
First(LL) ==
    IF Ring(LL)THEN Assert(FALSE, "A Linked List Cannot be a ring")  
    ELSE CHOOSE node \in DOMAIN LL:node \notin Range(LL)
    
Cyclic(LL) == 
    0 \notin Range(LL)
    
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
    /\ \A el \in ((DOMAIN PointerMap \union {0}) \ {First(PointerMap)}): \E x \in DOMAIN PointerMap : PointerMap[x]["next"] = el  /\ el /= x


LinkedLists(Nodes) ==   
    IF 0 \in Nodes THEN Assert(FALSE, "Null cannot be in Nodes") 
    ELSE 
    CHOOSE pm \in PointerMaps(Nodes) : isLinkedList(pm)
    
\* empty domain gives an empty list
ll(Nodes) == 
    IF 0 \in Nodes 
        THEN Assert(FALSE, "Null cannot be in Nodes") 
     ELSE IF Nodes \subseteq {}
            THEN <<>>
        ELSE
            CHOOSE pm \in PointerMaps(Nodes) : isll(pm)


============================================================================

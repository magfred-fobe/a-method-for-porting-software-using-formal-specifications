----------------------------- MODULE LinkedList -----------------------------
LOCAL INSTANCE TLC
LOCAL INSTANCE FiniteSets
LOCAL INSTANCE Sequences
LOCAL INSTANCE Integers
          
CONSTANTS NULL, VALUE


\* == Operators creating lists and verifying their correctness ==


\* Returns every possible permutation created with the domain argument           
PointerMaps(domain) == 
    [domain -> [value: VALUE, next: domain \union {NULL}]]

\* Returns the range pointed to by the domains of the argument "f" "next" keys   
Range(f) == 
    {f[x]["next"]: x \in DOMAIN f}

\* Checks if the linked list argument has any domain values pointing to them self.   
Ring(LL)  ==  
    (DOMAIN  LL  =  Range(LL))
    
\* Checking if there is a NULL value in the range of the linked list to see if it is cyclic or not. 
Cyclic(LL) == 
    NULL \notin Range(LL)

\* Returns the first element of the list
First(LL) ==
    IF Ring(LL)THEN Assert(FALSE, "A Linked List Cannot be a ring")  
    ELSE CHOOSE node \in DOMAIN LL:node \notin Range(LL)

Last(list) == 
    CHOOSE n \in DOMAIN list: list[n]["next"] = NULL

\* A list may not contain cyclic references
IsLinkedList(PointerMap) ==
    Cyclic(PointerMap) = FALSE 
    /\ Ring(PointerMap) = FALSE
    /\ \A el \in ((DOMAIN PointerMap \union {NULL}) \ {First(PointerMap)}): \E x \in DOMAIN PointerMap : PointerMap[x]["next"] = el  /\ el /= x

\*States if the linked list argument is empty or not.
Empty(l) == 
    Cardinality(DOMAIN l) = 1 /\ \E el \in DOMAIN l: el = "NULL"

\* Returns a function representing an empty list.
EmptyList == 
    [NULL |-> [next |-> NULL, value |-> NULL]]


\* The empty list is a list with an empty domain
LinkedList(Nodes) == 
    IF NULL \in Nodes 
        THEN Assert(FALSE, "Null cannot be in Nodes") 
    ELSE
        IF Nodes \subseteq {}
            THEN EmptyList
        ELSE
            CHOOSE pm \in PointerMaps(Nodes) : IsLinkedList(pm)

\* Returns the highest node value currently in the list
HighestNode(list) ==
    IF Empty(list)
    THEN 0
    ELSE
    CHOOSE n \in 1..100: ("node" \o ToString(n)) \in DOMAIN list /\ ~\E h \in 1..100: "node" \o ToString(h) \in DOMAIN list /\ h > n

\* Creates a new node label based on the lowest current label value plus one in the linked list.
NewLabel(list) ==
    "node" \o ToString(HighestNode(list)+1)

\* Creates a new domain of a lowest and highest values used when creting a linked list    
NewDomain(len, list) ==
    {"node" \o ToString(x): x \in HighestNode(list)+1..HighestNode(list)+len}
 
            
           
\* == Operators based on the functionalities of the linked list the model is based on ==



\* Inserts a new head in the linked list
InsertHead(val, list) ==
   IF Empty(list)
   THEN
    CHOOSE x \in [{NewLabel(list)} -> [next: {NULL}, value: {1}]]: TRUE
   ELSE
    list @@ (CHOOSE x \in [{NewLabel(list)} -> [next: {First(list)}, value: {1}]]:TRUE)


\* Find a function so that each element lab in the domain of the list U an arbitrary new label
\* maps to lext[lab] except, for label which maps to the new label, and new label which maps to next[label] 
InsertAfter_slow_and (label, list) == 
    IF Empty(list) /\ label \notin DOMAIN list THEN
        list \* just for testing
        \* Assert("FALSE", "CANNOT INSERT AFTER ELEMENT NOT IN LIST")
    ELSE
        LET 
        nl == {NewLabel(list)}
        next(lab) == list[lab]["next"]
        IN
        CHOOSE l \in [DOMAIN list \union nl -> [value: VALUE, next: Range(list) \union nl]]:
            \A d \in DOMAIN list \union nl:
                (d = label /\ l[d]["next"] \in nl)
            \/  (d \in nl /\ l[d]["next"] = next(label))
            \/  (d \notin {label} \union nl  /\ l[d]["next"] = next(d))
            
InsertAfter(label, list) ==
    IF Empty(list) /\ label \notin DOMAIN list THEN
        list \* just for testing
        \* Assert("FALSE", "CANNOT INSERT AFTER ELEMENT NOT IN LIST")
    ELSE
        LET 
        nl == {NewLabel(list)}
        newBefore == CHOOSE x \in [{label} -> [value: VALUE, next: nl]]:TRUE
        next(lab) == list[lab]["next"]
        newNode == CHOOSE x \in [nl -> [value: VALUE, next: {next(label)}]]:TRUE
        IN
        (newNode @@ newBefore) @@ list 

\* Find a function from the domain of list excluding the removed element, the new function returns the same value as list,
\* except if the list pointed to the removed elemnt, in which case the fuction returns list[label]["next"]
Remove(label, llist) ==  
    IF Empty(llist) \/ label \notin DOMAIN llist THEN
       Assert("FALSE", "CANNOT REMOVE ELEMENT NOT IN LIST")
    ELSE IF DOMAIN llist = {label} THEN 
       EmptyList
    ELSE
     CHOOSE l \in [(DOMAIN llist) \ {label} -> [value: VALUE, next: Range(llist) \ {label}]]:
        \A d \in ((DOMAIN llist) \ {label}): (l[d]["next"] = llist[d]["next"] \/ (llist[d]["next"] = label /\ l[d]["next"] = llist[llist[d]["next"]]["next"]))

\* Removes the head of the linked list..
RemoveHead(list) ==
    IF Empty(list) THEN
        Assert("FALSE", "NO HEAD IN LIST")
    ELSE
        Remove(First(list), list)
        
\* Removes the node after the node represented by the label argument.
RemoveAfter(label, list) ==
    IF Cardinality(DOMAIN list) < 2 THEN
        Assert("FALSE", "NEXT ELEMENT IS NULL OR THE LIST IS EMPTY")
    ELSE
        Remove(list[label]["next"], list)

\* Removes the node previous to the node represented by the label argument.      
RemovePrev(label, list) ==
    IF Cardinality(DOMAIN list) < 2 THEN
        Assert("FALSE", "THERE IS NO ELEMENT BEFORE THE CHOSEN ELEMENT")
    ELSE
        Remove(CHOOSE l \in DOMAIN list: list[l]["next"] = label, list) 

\* Returns the label of the next value of the label pointed to by the node represented by the "label" argument.
GetNext(label, list) ==
    list[label]["next"]

\* Swaps the head of the two list arguments.    
Swap(list, list2) ==
      <<list2, list>>

\*Concatenates two lists into one. The next value of the last element of "list" needs to point at the first element of "list".
Concat(list, list2) ==
    IF Empty(list) THEN
        <<list2, list>>
    ELSE IF Empty(list2) THEN
        <<list, list2>>
    ELSE
        LET newLast ==
            CHOOSE x \in [{Last(list)} -> [value: VALUE, next: {First(list2)}]]:TRUE
        IN
        <<(newLast @@ list) @@ list2, EmptyList>>
============================================================================











-------------------------------- MODULE main --------------------------------

EXTENDS TLC, FiniteSets, Sequences, Integers
CONSTANTS VALUE, NULL
INSTANCE LinkedList
                              
(* --algorithm List

variables 
list = [NULL |-> [next |-> NULL, value |-> NULL]],
domain = {"a", "b", "c"}

define
\* invariant for all lists
HasLast == 
    \E el \in DOMAIN list: list[el]["next"] = NULL 

\* invariant for all lists
isllinv ==
     Cyclic(list) = FALSE /\ 
     Ring(list) = FALSE /\
     \A el \in ((DOMAIN list \union {NULL}) \ {First(list)}): \E x \in DOMAIN list : list[x]["next"] = el  /\ el /= x

Empty(l) == 
    Cardinality(DOMAIN l) = 1 /\ \E el \in DOMAIN l: el = "NULL"


InsertHead(head) == 
   IF Empty(list) THEN head 
   ELSE head
  

\* head2 == CHOOSE h \in DOMAIN old: ~\E el \in DOMAIN old: old[el] = h  
end define


begin  
  (*  print isll(list);   
    \* Perform with a non empty and empty list
    either 
    list := ll({"a", "b", "c"});
    or
    list := ll({})
    end either;
    print isll(list);
    print list;*)
    print Empty(list);
    list := InsertHead(ll({"a"}));
    print Empty(list);
    print list;
end algorithm;*)
\* BEGIN TRANSLATION (chksum(pcal) = "959e9895" /\ chksum(tla) = "9618d17")
VARIABLES list, domain, pc

(* define statement *)
HasLast ==
    \E el \in DOMAIN list: list[el]["next"] = NULL


isllinv ==
     Cyclic(list) = FALSE /\
     Ring(list) = FALSE /\
     \A el \in ((DOMAIN list \union {NULL}) \ {First(list)}): \E x \in DOMAIN list : list[x]["next"] = el  /\ el /= x

Empty(l) ==
    Cardinality(DOMAIN l) = 1 /\ \E el \in DOMAIN l: el = "NULL"


InsertHead(head) ==
   IF Empty(list) THEN head
   ELSE head


vars == << list, domain, pc >>

Init == (* Global variables *)
        /\ list = [NULL |-> [next |-> NULL, value |-> NULL]]
        /\ domain = {"a", "b", "c"}
        /\ pc = "Lbl_1"

Lbl_1 == /\ pc = "Lbl_1"
         /\ PrintT(Empty(list))
         /\ list' = InsertHead(ll({"a"}))
         /\ PrintT(Empty(list'))
         /\ PrintT(list')
         /\ pc' = "Done"
         /\ UNCHANGED domain

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == Lbl_1
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 




=============================================================================

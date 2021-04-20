-------------------------------- MODULE main --------------------------------

EXTENDS TLC, FiniteSets, Sequences, Integers
CONSTANTS VALUE, NULL
INSTANCE LinkedList
(* --algorithm List
                        
variables 
list = [NULL |-> [next |-> NULL, value |-> NULL]],
domain = 1..4

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
    Cardinality(DOMAIN l) = 0

InsertHead(val) == 
   IF Empty(list)
   THEN \* create a new list with 1 element 
    <<[next |-> NULL, value |-> val ]>>
   ELSE \* link a new element in as head of list
    Append(list, [next |-> First(list), value |-> val])
    
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
    list := ll({});
    print Empty(list);
    list := InsertHead(1);
    print list;
    print InsertHead(2);
    print Append(<<[next |-> NULL, value |-> 1]>>,[next |-> NULL, value |-> 1]);
    print DOMAIN list;
end algorithm;*)
\* BEGIN TRANSLATION (chksum(pcal) = "80d72a87" /\ chksum(tla) = "7550f151")
VARIABLES list, domain, pc

(* define statement *)
HasLast ==
    \E el \in DOMAIN list: list[el]["next"] = NULL


isllinv ==
     Cyclic(list) = FALSE /\
     Ring(list) = FALSE /\
     \A el \in ((DOMAIN list \union {NULL}) \ {First(list)}): \E x \in DOMAIN list : list[x]["next"] = el  /\ el /= x

Empty(l) ==
    Cardinality(DOMAIN l) = 0

InsertHead(val) ==
   IF Empty(list)
   THEN
    <<[next |-> NULL, value |-> val ]>>
   ELSE
    Append(list, [next |-> First(list), value |-> val])


vars == << list, domain, pc >>

Init == (* Global variables *)
        /\ list = [NULL |-> [next |-> NULL, value |-> NULL]]
        /\ domain = 1..4
        /\ pc = "Lbl_1"

Lbl_1 == /\ pc = "Lbl_1"
         /\ list' = ll({})
         /\ PrintT(Empty(list'))
         /\ pc' = "Lbl_2"
         /\ UNCHANGED domain

Lbl_2 == /\ pc = "Lbl_2"
         /\ list' = InsertHead(1)
         /\ PrintT(list')
         /\ PrintT(InsertHead(2))
         /\ PrintT(Append(<<[next |-> NULL, value |-> 1]>>,[next |-> NULL, value |-> 1]))
         /\ PrintT(DOMAIN list')
         /\ pc' = "Done"
         /\ UNCHANGED domain

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == Lbl_1 \/ Lbl_2
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 





=============================================================================

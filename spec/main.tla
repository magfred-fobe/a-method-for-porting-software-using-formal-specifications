-------------------------------- MODULE main --------------------------------
EXTENDS TLC, FiniteSets, Sequences, Integers
CONSTANTS NULL, VALUE
INSTANCE LinkedList
                              
(* --algorithm List

variables 
list = [a |-> [next |-> "a", value |-> NULL]],
domain = 1..3



define
HasLast == 
    \E el \in DOMAIN list: list[el]["next"] = NULL \* invariant for all lists

isllinv ==
     Cyclic(list) = FALSE /\ 
     Ring(list) = FALSE /\
     \A el \in ((DOMAIN list \union {NULL}) \ {First(list)}): \E x \in DOMAIN list : list[x]["next"] = el  /\ el /= x

\* head2 == CHOOSE h \in DOMAIN old: ~\E el \in DOMAIN old: old[el] = h  
end define


begin  
    print isll(list);   
    \* Perform with a non empty and empty list
    either 
    list := ll({"a", "b", "c"});
    or
    list := ll({})
    end either;
    print isll(list);
    print list;
end algorithm;*)
\* BEGIN TRANSLATION (chksum(pcal) = "56161191" /\ chksum(tla) = "37771161")
VARIABLES list, domain, pc

(* define statement *)
HasLast ==
    \E el \in DOMAIN list: list[el]["next"] = NULL

isllinv ==
     Cyclic(list) = FALSE /\
     Ring(list) = FALSE /\
     \A el \in ((DOMAIN list \union {NULL}) \ {First(list)}): \E x \in DOMAIN list : list[x]["next"] = el  /\ el /= x


vars == << list, domain, pc >>

Init == (* Global variables *)
        /\ list = [a |-> [next |-> "a", value |-> NULL]]
        /\ domain = 1..3
        /\ pc = "Lbl_1"

Lbl_1 == /\ pc = "Lbl_1"
         /\ PrintT(isll(list))
         /\ \/ /\ list' = ll({"a", "b", "c"})
            \/ /\ list' = ll({})
         /\ PrintT(isll(list'))
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

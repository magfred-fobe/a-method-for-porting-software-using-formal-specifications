-------------------------------- MODULE main --------------------------------
EXTENDS TLC, FiniteSets, Sequences, Integers
CONSTANTS NULL, VALUE
INSTANCE LinkedList
                              
(* --algorithm List

variables 
list = [a |-> [next |-> "b", value |-> NULL]],
domain = {"a","b","c","d","e","f"},
old = [a |-> NULL, b |-> "c", c |-> "a"]

define
head == CHOOSE h \in DOMAIN old: ~\E el \in DOMAIN old: old[el] = h

HasLast == \E el \in DOMAIN list: list[el]["next"] = NULL \* invariant for all lists

isll(PointerMap) ==
    \A el \in ((DOMAIN PointerMap \union {NULL}) \ {head}): \E x \in DOMAIN PointerMap : PointerMap[x] = el  /\ el /= x
end define

begin
 print isll(old);
end algorithm;*)
\* BEGIN TRANSLATION (chksum(pcal) = "972e59bf" /\ chksum(tla) = "c03245d8")
VARIABLES list, domain, old, pc

(* define statement *)
head == CHOOSE h \in DOMAIN old: ~\E el \in DOMAIN old: old[el] = h

HasLast == \E el \in DOMAIN list: list[el]["next"] = NULL

isll(PointerMap) ==
    \A el \in ((DOMAIN PointerMap \union {NULL}) \ {head}): \E x \in DOMAIN PointerMap : PointerMap[x] = el  /\ el /= x


vars == << list, domain, old, pc >>

Init == (* Global variables *)
        /\ list = [a |-> [next |-> "b", value |-> NULL]]
        /\ domain = {"a","b","c","d","e","f"}
        /\ old = [a |-> NULL, b |-> "c", c |-> "a"]
        /\ pc = "Lbl_1"

Lbl_1 == /\ pc = "Lbl_1"
         /\ PrintT(isll(old))
         /\ pc' = "Done"
         /\ UNCHANGED << list, domain, old >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == Lbl_1
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 






=============================================================================

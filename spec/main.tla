-------------------------------- MODULE main --------------------------------
EXTENDS TLC, FiniteSets, Sequences, Integers
CONSTANTS NULL, VALUE
INSTANCE LinkedList
                              
(* --algorithm List

variables 
list = [a |-> [next |-> "b", value |-> NULL]],
domain = {"a", "b"},
old = [a |-> NULL, b |-> "c", c |-> "a"]

define
head2 == CHOOSE h \in DOMAIN old: ~\E el \in DOMAIN old: old[el] = h

HasLast == \E el \in DOMAIN list: list[el]["next"] = NULL \* invariant for all lists
end define

begin
\*  print PointerMaps(domain);   
  print ll(domain);
end algorithm;*)
\* BEGIN TRANSLATION (chksum(pcal) = "bf086545" /\ chksum(tla) = "fb327ade")
VARIABLES list, domain, old, pc

(* define statement *)
head2 == CHOOSE h \in DOMAIN old: ~\E el \in DOMAIN old: old[el] = h

HasLast == \E el \in DOMAIN list: list[el]["next"] = NULL


vars == << list, domain, old, pc >>

Init == (* Global variables *)
        /\ list = [a |-> [next |-> "b", value |-> NULL]]
        /\ domain = {"a", "b"}
        /\ old = [a |-> NULL, b |-> "c", c |-> "a"]
        /\ pc = "Lbl_1"

Lbl_1 == /\ pc = "Lbl_1"
         /\ PrintT(ll(domain))
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

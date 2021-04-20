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
\* BEGIN TRANSLATION (chksum(pcal) = "67f41eb9" /\ chksum(tla) = "73dd3056")
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
         /\ PrintT(isll(list))
         /\ \/ /\ list' = ll({"a", "b", "c"})
            \/ /\ list' = ll({})
         /\ PrintT(isll(list'))
         /\ PrintT(list')
         /\ pc' = "Done"
         /\ UNCHANGED << domain, old >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == Lbl_1
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 






=============================================================================

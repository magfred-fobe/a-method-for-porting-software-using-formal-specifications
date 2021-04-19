-------------------------------- MODULE main --------------------------------
EXTENDS TLC, FiniteSets, Sequences, Integers
CONSTANTS NULL, VALUE
INSTANCE LinkedList
                              
(* --algorithm List
variables domain = {"a", "b", "c"}, 
list = LinkedLists(domain),
old = [a |-> "c", b |-> "a", c |-> NULL]
define
    HasLast == \E el \in DOMAIN list: list[el]["next"] = NULL \* invariant for all lists
end define;
begin
    print "TRUE";
    \*print isLinkedList(list);
    \*print LinkedLists(domain);

end algorithm;*)
\* BEGIN TRANSLATION (chksum(pcal) = "684c6f38" /\ chksum(tla) = "129a249b")
VARIABLES domain, list, old, pc

(* define statement *)
HasLast == \E el \in DOMAIN list: list[el]["next"] = NULL


vars == << domain, list, old, pc >>

Init == (* Global variables *)
        /\ domain = {"a", "b", "c"}
        /\ list = LinkedLists(domain)
        /\ old = [a |-> "c", b |-> "a", c |-> NULL]
        /\ pc = "Lbl_1"

Lbl_1 == /\ pc = "Lbl_1"
         /\ PrintT("TRUE")
         /\ pc' = "Done"
         /\ UNCHANGED << domain, list, old >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == Lbl_1
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 





=============================================================================

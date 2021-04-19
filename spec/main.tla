-------------------------------- MODULE main --------------------------------
EXTENDS TLC, FiniteSets, Sequences, Integers
CONSTANTS NULL, VALUE
INSTANCE LinkedList
                              
(* --algorithm List
variables domain = {"a", "b", "c"}, 
list = [domain -> [value : {1}, next: domain \union {NULL}]],
pointermap = [a |-> [value |-> 1, next |-> "b"], b |-> [value |-> 1, next |-> NULL]],
old = [a |-> "c", b |-> "a", c |-> NULL]
define
    HasLast == \E l \in list: \E x \in DOMAIN l: l[x]["next"]= NULL \* invariant for all lists
end define;
begin
    print isLinkedList(pointermap);
    print LinkedLists(domain);

end algorithm;*)
\* BEGIN TRANSLATION (chksum(pcal) = "8117d045" /\ chksum(tla) = "322ef1f2")
VARIABLES domain, list, pointermap, old, pc

(* define statement *)
HasLast == \E l \in list: \E x \in DOMAIN l: l[x]["next"]= NULL
Fail == \A l \in list: \A x \in DOMAIN l: l[x]["next"]= NULL


vars == << domain, list, pointermap, old, pc >>

Init == (* Global variables *)
        /\ domain = {"a", "b", "c"}
        /\ list = [domain -> [value : {1}, next: domain \union {NULL}]]
        /\ pointermap = [a |-> [value |-> 1, next |-> "b"], b |-> [value |-> 1, next |-> NULL]]
        /\ old = [a |-> "c", b |-> "a", c |-> NULL]
        /\ pc = "Lbl_1"

Lbl_1 == /\ pc = "Lbl_1"
         /\ PrintT(isLinkedList(pointermap))
         /\ PrintT(LinkedLists(domain))
         /\ pc' = "Done"
         /\ UNCHANGED << domain, list, pointermap, old >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == Lbl_1
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 




=============================================================================

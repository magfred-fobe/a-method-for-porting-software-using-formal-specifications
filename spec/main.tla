-------------------------------- MODULE main --------------------------------
EXTENDS TLC, FiniteSets, Sequences, Integers
CONSTANTS NULL, VALUE
INSTANCE LinkedList
                              
(* --algorithm List
variables 
list = [a |-> [next |-> "b", value |-> NULL]],
characters = {"x", "y", "z"},
domain = {"a", "b"},
old = [a |-> NULL, b |-> "c", c |-> "a"]
define
head2 == CHOOSE h \in DOMAIN old: ~\E el \in DOMAIN old: old[el] = h

HasLast == \E el \in DOMAIN list: list[el]["next"] = NULL \* invariant for all lists

NewLabel ==
    CHOOSE label \in {x \o z: x \in DOMAIN list, z \in characters}: label \notin DOMAIN list

InsertHead(val) ==
   IF Empty(list)
   THEN
    CHOOSE x \in [{"a"} -> [next: {NULL}, value: {1}]]: TRUE
   ELSE
    list @@ (CHOOSE x \in [{NewLabel} -> [next: {First(list)}, value: {1}]]:TRUE)
    


end define
begin
    \* Perform with a non empty and empty list
    either 
    list := ll({"a", "b", "c"});
    or
    list := ll({})
    end either;
    print list;
    list := InsertHead(2);
    print list;
    print isll(list);   
    
end algorithm;*)
\* BEGIN TRANSLATION (chksum(pcal) = "c2319279" /\ chksum(tla) = "b77112dd")
VARIABLES list, characters, domain, old, pc

(* define statement *)
head2 == CHOOSE h \in DOMAIN old: ~\E el \in DOMAIN old: old[el] = h

HasLast == \E el \in DOMAIN list: list[el]["next"] = NULL

NewLabel ==
    CHOOSE label \in {x \o z: x \in DOMAIN list, z \in characters}: label \notin DOMAIN list

InsertHead(val) ==
   IF Empty(list)
   THEN
    CHOOSE x \in [{"a"} -> [next: {NULL}, value: {1}]]: TRUE
   ELSE
    list @@ (CHOOSE x \in [{NewLabel} -> [next: {First(list)}, value: {1}]]:TRUE)


vars == << list, characters, domain, old, pc >>

Init == (* Global variables *)
        /\ list = [a |-> [next |-> "b", value |-> NULL]]
        /\ characters = {"x", "y", "z"}
        /\ domain = {"a", "b"}
        /\ old = [a |-> NULL, b |-> "c", c |-> "a"]
        /\ pc = "Lbl_1"

Lbl_1 == /\ pc = "Lbl_1"
         /\ \/ /\ list' = ll({"a", "b", "c"})
            \/ /\ list' = ll({})
         /\ PrintT(list')
         /\ pc' = "Lbl_2"
         /\ UNCHANGED << characters, domain, old >>

Lbl_2 == /\ pc = "Lbl_2"
         /\ list' = InsertHead(2)
         /\ PrintT(list')
         /\ PrintT(isll(list'))
         /\ pc' = "Done"
         /\ UNCHANGED << characters, domain, old >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == Lbl_1 \/ Lbl_2
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 






=============================================================================

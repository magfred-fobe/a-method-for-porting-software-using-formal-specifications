-------------------------------- MODULE main --------------------------------
EXTENDS TLC, FiniteSets, Sequences, Integers
CONSTANTS NULL, VALUE
INSTANCE LinkedList
                              
(* --algorithm List
variables 
i = 0,
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
    START:
    either
    list := ll({"a", "b", "c"});
    or
    list := ll({})
    end either;
LOOP:
 while i < 2 do
    either 
       \*Concat:
       skip;
    or
       \*InsertAfter:
       skip;
    or
       list := InsertHead(2)
    or
        \*Next2:
        skip;
    or
        \*Remove:
        skip;
    or
        \*RemoveAfter:
        skip;
    or
        \*RemoveHead:
        skip;
    or
        \*RemovePrev:
        skip;
    or
        \*Swap:
        skip; 
    or
        \*End:
        skip;
    or
        \*First2:
        skip;
    end either;
INCREMENT:
   i := i+1;
print list;
end while;
    
end algorithm;*)
\* BEGIN TRANSLATION (chksum(pcal) = "e5178769" /\ chksum(tla) = "2e2ef562")
VARIABLES i, list, characters, domain, old, pc

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


vars == << i, list, characters, domain, old, pc >>

Init == (* Global variables *)
        /\ i = 0
        /\ list = [a |-> [next |-> "b", value |-> NULL]]
        /\ characters = {"x", "y", "z"}
        /\ domain = {"a", "b"}
        /\ old = [a |-> NULL, b |-> "c", c |-> "a"]
        /\ pc = "START"

START == /\ pc = "START"
         /\ \/ /\ list' = ll({"a", "b", "c"})
            \/ /\ list' = ll({})
         /\ pc' = "LOOP"
         /\ UNCHANGED << i, characters, domain, old >>

LOOP == /\ pc = "LOOP"
        /\ IF i < 2
              THEN /\ \/ /\ TRUE
                         /\ list' = list
                      \/ /\ TRUE
                         /\ list' = list
                      \/ /\ list' = InsertHead(2)
                      \/ /\ TRUE
                         /\ list' = list
                      \/ /\ TRUE
                         /\ list' = list
                      \/ /\ TRUE
                         /\ list' = list
                      \/ /\ TRUE
                         /\ list' = list
                      \/ /\ TRUE
                         /\ list' = list
                      \/ /\ TRUE
                         /\ list' = list
                      \/ /\ TRUE
                         /\ list' = list
                      \/ /\ TRUE
                         /\ list' = list
                   /\ pc' = "INCREMENT"
              ELSE /\ pc' = "Done"
                   /\ list' = list
        /\ UNCHANGED << i, characters, domain, old >>

INCREMENT == /\ pc = "INCREMENT"
             /\ i' = i+1
             /\ PrintT(list)
             /\ pc' = "LOOP"
             /\ UNCHANGED << list, characters, domain, old >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == START \/ LOOP \/ INCREMENT
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 






=============================================================================

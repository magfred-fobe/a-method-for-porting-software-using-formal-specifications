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
old = [a |-> NULL, b |-> "c", c |-> "a"],
temp = NULL
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

Remove(label) ==  
    \*CHOOSE l \in [DOMAIN list \ {label} -> [value: VALUE, next: Range(list) \ {label}]]: \A d \in DOMAIN list \ label: l[d]["next"]: 
       CHOOSE l \in [(DOMAIN list) \ {label} -> [value: VALUE, next: Range(list) \ {label}]]:
        \A d \in ((DOMAIN list) \ {label}): (l[d]["next"] = list[d]["next"] \/ (list[d]["next"] = label /\ l[d]["next"] = list[list[d]["next"]]["next"]))


end define
begin
    PRESTART:
    list := ll({"f", "g", "h"});
    print "BEFORE";
    print list;
    print "REMOVED";
    REMOVE:
    list := Remove("h");
    print list;
    
    print "===";
    \* Perform with a non empty and empty list 
    START:
    either
    list := ll({"f", "g", "h"});
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
\* BEGIN TRANSLATION (chksum(pcal) = "ff3b7a44" /\ chksum(tla) = "33bacec")
VARIABLES i, list, characters, domain, old, temp, pc

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

Remove(label) ==

       CHOOSE l \in [(DOMAIN list) \ {label} -> [value: VALUE, next: Range(list) \ {label}]]:
        \A d \in ((DOMAIN list) \ {label}): (l[d]["next"] = list[d]["next"] \/ (list[d]["next"] = label /\ l[d]["next"] = list[list[d]["next"]]["next"]))


vars == << i, list, characters, domain, old, temp, pc >>

Init == (* Global variables *)
        /\ i = 0
        /\ list = [a |-> [next |-> "b", value |-> NULL]]
        /\ characters = {"x", "y", "z"}
        /\ domain = {"a", "b"}
        /\ old = [a |-> NULL, b |-> "c", c |-> "a"]
        /\ temp = NULL
        /\ pc = "PRESTART"

PRESTART == /\ pc = "PRESTART"
            /\ list' = ll({"f", "g", "h"})
            /\ PrintT("BEFORE")
            /\ PrintT(list')
            /\ PrintT("REMOVED")
            /\ pc' = "REMOVE"
            /\ UNCHANGED << i, characters, domain, old, temp >>

REMOVE == /\ pc = "REMOVE"
          /\ list' = Remove("h")
          /\ PrintT(list')
          /\ PrintT("===")
          /\ pc' = "START"
          /\ UNCHANGED << i, characters, domain, old, temp >>

START == /\ pc = "START"
         /\ \/ /\ list' = ll({"f", "g", "h"})
            \/ /\ list' = ll({})
         /\ pc' = "LOOP"
         /\ UNCHANGED << i, characters, domain, old, temp >>

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
        /\ UNCHANGED << i, characters, domain, old, temp >>

INCREMENT == /\ pc = "INCREMENT"
             /\ i' = i+1
             /\ PrintT(list)
             /\ pc' = "LOOP"
             /\ UNCHANGED << list, characters, domain, old, temp >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == PRESTART \/ REMOVE \/ START \/ LOOP \/ INCREMENT
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 






=============================================================================

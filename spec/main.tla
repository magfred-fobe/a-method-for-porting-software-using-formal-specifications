-------------------------------- MODULE main --------------------------------
EXTENDS FiniteSets, Sequences, Integers
LOCAL INSTANCE TLC
CONSTANTS NULL, VALUE
INSTANCE LinkedList
                              
(* --algorithm List
variables 
i = 0,
list = ll({}),
characters = {"x", "y", "z"},
domain = {"a", "b"},
old = [a |-> NULL, b |-> "c", c |-> "a"],
temp = NULL
define
head2 == CHOOSE h \in DOMAIN old: ~\E el \in DOMAIN old: old[el] = h

HasLast == Empty(list) \/ \E el \in DOMAIN list: list[el]["next"] = NULL \* invariant for all lists

NewLabel ==
    CHOOSE label \in {x \o z: x \in DOMAIN list, z \in characters}: label \notin DOMAIN list

InsertHead(val) ==
   IF Empty(list)
   THEN
    CHOOSE x \in [{"a"} -> [next: {NULL}, value: {1}]]: TRUE
   ELSE
    list @@ (CHOOSE x \in [{NewLabel} -> [next: {First(list)}, value: {1}]]:TRUE)

\* Find a function from the domain of list excluding the removed element, the new function returns the same value as list,
\* except if the list pointed to the removed elemnt, in which case the fuction returns list[label]["next"]
Remove ==  
    IF Empty(list) THEN
        list
    ELSE IF DOMAIN list = {First(list)}
     THEN 
     EmptyList
     ELSE
    \*CHOOSE l \in [DOMAIN list \ {label} -> [value: VALUE, next: Range(list) \ {label}]]: \A d \in DOMAIN list \ label: l[d]["next"]: 
       LET label == CHOOSE x \in DOMAIN list: TRUE
       IN CHOOSE l \in [(DOMAIN list) \ {label} -> [value: VALUE, next: Range(list) \ {label}]]:
        \A d \in ((DOMAIN list) \ {label}): (l[d]["next"] = list[d]["next"] \/ (list[d]["next"] = label /\ l[d]["next"] = list[list[d]["next"]]["next"]))


end define
begin
    \* Perform with a non empty and empty list 
    START:
    either
    list := ll({"f", "g", "h"});
    or
    skip;\*list := ll({})
    end either;
LOOP:
 while i < 5 do
    either 
       list := InsertHead(2)
    or
       list := Remove;
    end either;
INCREMENT:
   i := i+1;
print "=== LIST IS ===";
print list;
\* This should also be an invariant
assert HasLast;
end while;
    
end algorithm;*)
\* BEGIN TRANSLATION (chksum(pcal) = "92497c27" /\ chksum(tla) = "8e8b0ed3")
VARIABLES i, list, characters, domain, old, temp, pc

(* define statement *)
head2 == CHOOSE h \in DOMAIN old: ~\E el \in DOMAIN old: old[el] = h

HasLast == Empty(list) \/ \E el \in DOMAIN list: list[el]["next"] = NULL

NewLabel ==
    CHOOSE label \in {x \o z: x \in DOMAIN list, z \in characters}: label \notin DOMAIN list

InsertHead(val) ==
   IF Empty(list)
   THEN
    CHOOSE x \in [{"a"} -> [next: {NULL}, value: {1}]]: TRUE
   ELSE
    list @@ (CHOOSE x \in [{NewLabel} -> [next: {First(list)}, value: {1}]]:TRUE)



Remove ==
    IF Empty(list) THEN
        list
    ELSE IF DOMAIN list = {First(list)}
     THEN
     EmptyList
     ELSE

       LET label == CHOOSE x \in DOMAIN list: TRUE
       IN CHOOSE l \in [(DOMAIN list) \ {label} -> [value: VALUE, next: Range(list) \ {label}]]:
        \A d \in ((DOMAIN list) \ {label}): (l[d]["next"] = list[d]["next"] \/ (list[d]["next"] = label /\ l[d]["next"] = list[list[d]["next"]]["next"]))


vars == << i, list, characters, domain, old, temp, pc >>

Init == (* Global variables *)
        /\ i = 0
        /\ list = ll({})
        /\ characters = {"x", "y", "z"}
        /\ domain = {"a", "b"}
        /\ old = [a |-> NULL, b |-> "c", c |-> "a"]
        /\ temp = NULL
        /\ pc = "START"

START == /\ pc = "START"
         /\ \/ /\ list' = ll({"f", "g", "h"})
            \/ /\ TRUE
               /\ list' = list
         /\ pc' = "LOOP"
         /\ UNCHANGED << i, characters, domain, old, temp >>

LOOP == /\ pc = "LOOP"
        /\ IF i < 5
              THEN /\ \/ /\ list' = InsertHead(2)
                      \/ /\ list' = Remove
                   /\ pc' = "INCREMENT"
              ELSE /\ pc' = "Done"
                   /\ list' = list
        /\ UNCHANGED << i, characters, domain, old, temp >>

INCREMENT == /\ pc = "INCREMENT"
             /\ i' = i+1
             /\ PrintT("=== LIST IS ===")
             /\ PrintT(list)
             /\ Assert(HasLast, "Failure of assertion at line 66, column 1.")
             /\ pc' = "LOOP"
             /\ UNCHANGED << list, characters, domain, old, temp >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == START \/ LOOP \/ INCREMENT
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 






=============================================================================

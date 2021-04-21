-------------------------------- MODULE main --------------------------------

EXTENDS TLC, FiniteSets, Sequences, Integers
CONSTANTS VALUE, NULL
INSTANCE LinkedList
(* --algorithm List
                        
variables 
list = [NULL |-> [value |-> NULL, next |-> NULL]],
domain = 1..4,
values \in 1..10,
i = 0,
characters = {"a", "b", "c", "d"},
char

define
\* invariant for all lists
HasLast == 
    \E el \in DOMAIN list: list[el]["next"] = NULL 

\* invariant for all lists
isllinv ==
     Cyclic(list) = FALSE /\
     Ring(list) = FALSE /\
     \A el \in ((DOMAIN list \union {NULL}) \ {First(list)}): \E x \in DOMAIN list : list[x]["next"] = el  /\ el /= x

Empty(l) == 
    Cardinality(DOMAIN l) = 1 /\ \E el \in DOMAIN l: el = "NULL"

NewLabel ==
    CHOOSE label \in {x \o z: x \in DOMAIN list, z \in characters}: label \notin DOMAIN list

InsertHead2(val) == 
   IF Empty(list)
   THEN \* create a new list with 1 element 
    <<[next |-> NULL, value |-> val ]>>
   ELSE \* link a new element in as head of list
    Append(list, [next |-> First(list), value |-> val])
    
end define


begin  
LOOP:
 while i < 2 do
    either 
       Concat:
       skip;
    or
       InsertAfter:
       skip;
    or
       InsertHead:
       if Empty(list) then goto B else goto C end if;
         B:
          list := CHOOSE x \in [{NewLabel} -> [next: {NULL}, value: {1}]]: TRUE;
         C:
          list :=  list @@ (CHOOSE x \in [{NewLabel} -> [next: {First(list)}, value: {1}]]:TRUE);   
    or
        Next2:
        skip;
    or
        Remove:
        skip;
    or
        RemoveAfter:
        skip;
    or
        RemoveHead:
        skip;
    or
        RemovePrev:
        skip;
    or
        Swap:
        skip; 
    or
        End:
        skip;
    or
        First2:
        skip;       
    end either;
    
INCREMENT:
   i := i+1;
        
PRINT: 
   print list;
   
end while  
end algorithm;*)
\* BEGIN TRANSLATION (chksum(pcal) = "307ff922" /\ chksum(tla) = "c8803241")
CONSTANT defaultInitValue
VARIABLES list, domain, values, i, characters, char, pc

(* define statement *)
HasLast ==
    \E el \in DOMAIN list: list[el]["next"] = NULL


isllinv ==
     Cyclic(list) = FALSE /\
     Ring(list) = FALSE /\
     \A el \in ((DOMAIN list \union {NULL}) \ {First(list)}): \E x \in DOMAIN list : list[x]["next"] = el  /\ el /= x

Empty(l) ==
    Cardinality(DOMAIN l) = 1 /\ \E el \in DOMAIN l: el = "NULL"

NewLabel ==
    CHOOSE label \in {x \o z: x \in DOMAIN list, z \in characters}: label \notin DOMAIN list

InsertHead2(val) ==
   IF Empty(list)
   THEN
    <<[next |-> NULL, value |-> val ]>>
   ELSE
    Append(list, [next |-> First(list), value |-> val])


vars == << list, domain, values, i, characters, char, pc >>

Init == (* Global variables *)
        /\ list = [NULL |-> [value |-> NULL, next |-> NULL]]
        /\ domain = 1..4
        /\ values \in 1..10
        /\ i = 0
        /\ characters = {"a", "b", "c", "d"}
        /\ char = defaultInitValue
        /\ pc = "LOOP"

LOOP == /\ pc = "LOOP"
        /\ IF i < 2
              THEN /\ \/ /\ pc' = "Concat"
                      \/ /\ pc' = "InsertAfter"
                      \/ /\ pc' = "InsertHead"
                      \/ /\ pc' = "Next2"
                      \/ /\ pc' = "Remove"
                      \/ /\ pc' = "RemoveAfter"
                      \/ /\ pc' = "RemoveHead"
                      \/ /\ pc' = "RemovePrev"
                      \/ /\ pc' = "Swap"
                      \/ /\ pc' = "End"
                      \/ /\ pc' = "First2"
              ELSE /\ pc' = "Done"
        /\ UNCHANGED << list, domain, values, i, characters, char >>

INCREMENT == /\ pc = "INCREMENT"
             /\ i' = i+1
             /\ pc' = "PRINT"
             /\ UNCHANGED << list, domain, values, characters, char >>

PRINT == /\ pc = "PRINT"
         /\ PrintT(list)
         /\ pc' = "LOOP"
         /\ UNCHANGED << list, domain, values, i, characters, char >>

Concat == /\ pc = "Concat"
          /\ TRUE
          /\ pc' = "INCREMENT"
          /\ UNCHANGED << list, domain, values, i, characters, char >>

InsertAfter == /\ pc = "InsertAfter"
               /\ TRUE
               /\ pc' = "INCREMENT"
               /\ UNCHANGED << list, domain, values, i, characters, char >>

InsertHead == /\ pc = "InsertHead"
              /\ IF Empty(list)
                    THEN /\ pc' = "B"
                    ELSE /\ pc' = "C"
              /\ UNCHANGED << list, domain, values, i, characters, char >>

B == /\ pc = "B"
     /\ list' = (CHOOSE x \in [{NewLabel} -> [next: {NULL}, value: {1}]]: TRUE)
     /\ pc' = "C"
     /\ UNCHANGED << domain, values, i, characters, char >>

C == /\ pc = "C"
     /\ list' = list @@ (CHOOSE x \in [{NewLabel} -> [next: {First(list)}, value: {1}]]:TRUE)
     /\ pc' = "INCREMENT"
     /\ UNCHANGED << domain, values, i, characters, char >>

Next2 == /\ pc = "Next2"
         /\ TRUE
         /\ pc' = "INCREMENT"
         /\ UNCHANGED << list, domain, values, i, characters, char >>

Remove == /\ pc = "Remove"
          /\ TRUE
          /\ pc' = "INCREMENT"
          /\ UNCHANGED << list, domain, values, i, characters, char >>

RemoveAfter == /\ pc = "RemoveAfter"
               /\ TRUE
               /\ pc' = "INCREMENT"
               /\ UNCHANGED << list, domain, values, i, characters, char >>

RemoveHead == /\ pc = "RemoveHead"
              /\ TRUE
              /\ pc' = "INCREMENT"
              /\ UNCHANGED << list, domain, values, i, characters, char >>

RemovePrev == /\ pc = "RemovePrev"
              /\ TRUE
              /\ pc' = "INCREMENT"
              /\ UNCHANGED << list, domain, values, i, characters, char >>

Swap == /\ pc = "Swap"
        /\ TRUE
        /\ pc' = "INCREMENT"
        /\ UNCHANGED << list, domain, values, i, characters, char >>

End == /\ pc = "End"
       /\ TRUE
       /\ pc' = "INCREMENT"
       /\ UNCHANGED << list, domain, values, i, characters, char >>

First2 == /\ pc = "First2"
          /\ TRUE
          /\ pc' = "INCREMENT"
          /\ UNCHANGED << list, domain, values, i, characters, char >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == LOOP \/ INCREMENT \/ PRINT \/ Concat \/ InsertAfter \/ InsertHead
           \/ B \/ C \/ Next2 \/ Remove \/ RemoveAfter \/ RemoveHead
           \/ RemovePrev \/ Swap \/ End \/ First2
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 

\* END TRANSLATION 




=============================================================================

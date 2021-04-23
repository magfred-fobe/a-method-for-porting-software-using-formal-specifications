-------------------------------- MODULE main --------------------------------
EXTENDS FiniteSets, Sequences, Integers
LOCAL INSTANCE TLC
CONSTANTS NULL, VALUE
INSTANCE LinkedList
                              
(* --algorithm List

\* Global variables
variables 
i = 0,
list = LinkedList({}),
list2 = LinkedList({}),
characters = {"x", "y", "z"},
domain = {"a", "b"},
old = [a |-> NULL, b |-> "c", c |-> "a"]

\* Global and local invariants the model is based on 
define

HasLast == Empty(list) \/ \E el \in DOMAIN list: list[el]["next"] = NULL \* invariant for all lists

validList == IsLinkedList(list)
    
end define

\* The model checking alogithm
begin
    START:
    list := LinkedList(NewDomain(3, list));
    print list;
    START2:
    list2 := LinkedList(NewDomain(2, list));
    print list2;
    NeXT:
    either
    A:
    list := Concat(list, list2);
    or
    list := InsertHead(NewLabel(list), list);
    end either;
    PRINT:
    print list;
    after:
    list := InsertAfter(CHOOSE x \in DOMAIN list: TRUE, list);
    print "==AFTER==";
    print list;
    print "DONE";
 
 (*       
LOOP:
 while i < 3 do
    either 
       list := InsertHead(CHOOSE value \in 1..1: TRUE);
    or
       list := Remove;
    or
       list := InsertAfter(CHOOSE value \in DOMAIN list: TRUE);
    or
       list := RemoveAfter(CHOOSE l \in DOMAIN list: list[l]["next"] \in DOMAIN list);
    or
       list := RemoveHead;
    or
       list := RemovePrev(CHOOSE l \in DOMAIN list: list[l]["next"] \in Range(list));
    or
       GetNext(CHOOSE l \in DOMAIN list: TRUE)
    or
       Swap(list, LinkedList(NewDomain(2, list)));
    or
       UpdatingLast:
        list[Last(list)]["next"] := First(list2);
       Concatenating:
        list := Concat(list, list2)
    end either;
INCREMENT:
   i := i+1;
print "=== LIST IS ===";
print list;
\* This should also be an invariant
assert HasLast;
end while;
 *)   
end algorithm;*)
\* BEGIN TRANSLATION (chksum(pcal) = "321823aa" /\ chksum(tla) = "6a6fb99f")
VARIABLES i, list, list2, characters, domain, old, pc

(* define statement *)
HasLast == Empty(list) \/ \E el \in DOMAIN list: list[el]["next"] = NULL

validList == IsLinkedList(list)


vars == << i, list, list2, characters, domain, old, pc >>

Init == (* Global variables *)
        /\ i = 0
        /\ list = LinkedList({})
        /\ list2 = LinkedList({})
        /\ characters = {"x", "y", "z"}
        /\ domain = {"a", "b"}
        /\ old = [a |-> NULL, b |-> "c", c |-> "a"]
        /\ pc = "START"

START == /\ pc = "START"
         /\ list' = LinkedList(NewDomain(3, list))
         /\ PrintT(list')
         /\ pc' = "START2"
         /\ UNCHANGED << i, list2, characters, domain, old >>

START2 == /\ pc = "START2"
          /\ list2' = LinkedList(NewDomain(2, list))
          /\ PrintT(list2')
          /\ pc' = "NeXT"
          /\ UNCHANGED << i, list, characters, domain, old >>

NeXT == /\ pc = "NeXT"
        /\ \/ /\ pc' = "A"
              /\ list' = list
           \/ /\ list' = InsertHead(NewLabel(list), list)
              /\ pc' = "PRINT"
        /\ UNCHANGED << i, list2, characters, domain, old >>

A == /\ pc = "A"
     /\ list' = Concat(list, list2)
     /\ pc' = "PRINT"
     /\ UNCHANGED << i, list2, characters, domain, old >>

PRINT == /\ pc = "PRINT"
         /\ PrintT(list)
         /\ pc' = "after"
         /\ UNCHANGED << i, list, list2, characters, domain, old >>

after == /\ pc = "after"
         /\ list' = InsertAfter(CHOOSE x \in DOMAIN list: TRUE, list)
         /\ PrintT("==AFTER==")
         /\ PrintT(list')
         /\ PrintT("DONE")
         /\ pc' = "Done"
         /\ UNCHANGED << i, list2, characters, domain, old >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == START \/ START2 \/ NeXT \/ A \/ PRINT \/ after
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 


=============================================================================

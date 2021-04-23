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
    NEXT:
    list := Remove("node3", list);
    print list;
    NeXt:
    list := Swap(list, LinkedList(NewDomain(2, list)));
    print list;
    NExt:
    list := InsertAfter("node4", list);
    print list;
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
\* BEGIN TRANSLATION (chksum(pcal) = "651d7c54" /\ chksum(tla) = "54a2916c")
VARIABLES i, list, characters, domain, old, pc

(* define statement *)
HasLast == Empty(list) \/ \E el \in DOMAIN list: list[el]["next"] = NULL

validList == IsLinkedList(list)


vars == << i, list, characters, domain, old, pc >>

Init == (* Global variables *)
        /\ i = 0
        /\ list = LinkedList({})
        /\ characters = {"x", "y", "z"}
        /\ domain = {"a", "b"}
        /\ old = [a |-> NULL, b |-> "c", c |-> "a"]
        /\ pc = "START"

START == /\ pc = "START"
         /\ list' = LinkedList(NewDomain(3, list))
         /\ PrintT(list')
         /\ pc' = "NEXT"
         /\ UNCHANGED << i, characters, domain, old >>

NEXT == /\ pc = "NEXT"
        /\ list' = Remove("node3", list)
        /\ PrintT(list')
        /\ pc' = "NeXt"
        /\ UNCHANGED << i, characters, domain, old >>

NeXt == /\ pc = "NeXt"
        /\ list' = Swap(list, LinkedList(NewDomain(2, list)))
        /\ PrintT(list')
        /\ pc' = "NExt"
        /\ UNCHANGED << i, characters, domain, old >>

NExt == /\ pc = "NExt"
        /\ list' = InsertAfter("node4", list)
        /\ PrintT(list')
        /\ pc' = "Done"
        /\ UNCHANGED << i, characters, domain, old >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == START \/ NEXT \/ NeXt \/ NExt
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 


=============================================================================

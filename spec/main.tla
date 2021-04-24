-------------------------------- MODULE main --------------------------------
EXTENDS FiniteSets, Sequences, Integers
LOCAL INSTANCE TLC
CONSTANTS NULL, VALUE
INSTANCE LinkedList
                              
(* --algorithm List

\* Global variables
variables 
i = 0,
from = 1,
list = LinkedList({}),
list2 = LinkedList({}),
characters = {"x", "y", "z"},
domain = {"a", "b"},
old = [a |-> NULL, b |-> "c", c |-> "a"],
temp = NULL,
arg = {},
lab = NULL,
index = NULL

\* Global and local invariants the model is based on 
define

HasLast == Empty(list) \/ \E el \in DOMAIN list: list[el]["next"] = NULL \* invariant for all lists

ValidList == IsLinkedList(list) /\ IsLinkedList(list2)

ForEachOperator(x) == x*2

end define

\* The model checking alogrithm
begin
    \* with either list1 empty or a list of size 1 to 3
    PRECONDITIONS:
    with size1 \in 0..3 do
        with size2 \in 0..3 do
        list := LinkedList(NewDomain(size2, list))
        end with;
        list2 := LinkedList(NewDomain(size1, list))
    end with;
        
        \* Do the following from each starting state
        \* Also do it in a loop
        either
            INSERTHEAD:
            list := InsertHead(NewLabel(list), list);
        or 
            CONCAT:
            temp := Concat(list, list2);
            list := temp[1];
            list2:= temp[2];
        or 
            SWAP:
            temp := Swap(list, list2);
            list := temp[1];
            list2 := temp[2];
        or
            REMOVE:
            \* just to make it work with empty lists as well
            if Empty(list) = FALSE then
                REMOVENOTEMPTY:
                list := Remove(CHOOSE x \in DOMAIN list:TRUE, list);
            else 
                REMOVEEMPTY:
                skip;
            end if;
        or 
            FOREACHFROM:
            \* just to make it work with empty lists as well
            if Empty(list) = FALSE then
                FOREACHNOTEMPTY:
                  lab := First(list);
                  arg := {lab};
                FOREACHFROMLOOP:
                  while from < 1 do
                    lab := list[lab]["next"];
                    arg := arg \union {lab};
                    from := from + 1;
                  end while; 
                FOREACHFROMRUN:
                  list := ForEachFrom(list, {el \in DOMAIN list: el \notin arg}, ForEachOperator);
                  from := 1;
            else 
                skip;
            end if;
    end either;
    
    END:
    print "===LIST IS===";
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
\* BEGIN TRANSLATION (chksum(pcal) = "1e266b9f" /\ chksum(tla) = "fb0e229f")
VARIABLES i, from, list, list2, characters, domain, old, temp, arg, lab, 
          index, pc

(* define statement *)
HasLast == Empty(list) \/ \E el \in DOMAIN list: list[el]["next"] = NULL

ValidList == IsLinkedList(list) /\ IsLinkedList(list2)

ForEachOperator(x) == x*2


vars == << i, from, list, list2, characters, domain, old, temp, arg, lab, 
           index, pc >>

Init == (* Global variables *)
        /\ i = 0
        /\ from = 1
        /\ list = LinkedList({})
        /\ list2 = LinkedList({})
        /\ characters = {"x", "y", "z"}
        /\ domain = {"a", "b"}
        /\ old = [a |-> NULL, b |-> "c", c |-> "a"]
        /\ temp = NULL
        /\ arg = {}
        /\ lab = NULL
        /\ index = NULL
        /\ pc = "PRECONDITIONS"

PRECONDITIONS == /\ pc = "PRECONDITIONS"
                 /\ \E size1 \in 0..3:
                      /\ \E size2 \in 0..3:
                           list' = LinkedList(NewDomain(size2, list))
                      /\ list2' = LinkedList(NewDomain(size1, list'))
                 /\ \/ /\ pc' = "INSERTHEAD"
                    \/ /\ pc' = "CONCAT"
                    \/ /\ pc' = "SWAP"
                    \/ /\ pc' = "REMOVE"
                    \/ /\ pc' = "FOREACHFROM"
                 /\ UNCHANGED << i, from, characters, domain, old, temp, arg, 
                                 lab, index >>

INSERTHEAD == /\ pc = "INSERTHEAD"
              /\ list' = InsertHead(NewLabel(list), list)
              /\ pc' = "END"
              /\ UNCHANGED << i, from, list2, characters, domain, old, temp, 
                              arg, lab, index >>

CONCAT == /\ pc = "CONCAT"
          /\ temp' = Concat(list, list2)
          /\ list' = temp'[1]
          /\ list2' = temp'[2]
          /\ pc' = "END"
          /\ UNCHANGED << i, from, characters, domain, old, arg, lab, index >>

SWAP == /\ pc = "SWAP"
        /\ temp' = Swap(list, list2)
        /\ list' = temp'[1]
        /\ list2' = temp'[2]
        /\ pc' = "END"
        /\ UNCHANGED << i, from, characters, domain, old, arg, lab, index >>

REMOVE == /\ pc = "REMOVE"
          /\ IF Empty(list) = FALSE
                THEN /\ pc' = "REMOVENOTEMPTY"
                ELSE /\ pc' = "REMOVEEMPTY"
          /\ UNCHANGED << i, from, list, list2, characters, domain, old, temp, 
                          arg, lab, index >>

REMOVENOTEMPTY == /\ pc = "REMOVENOTEMPTY"
                  /\ list' = Remove(CHOOSE x \in DOMAIN list:TRUE, list)
                  /\ pc' = "END"
                  /\ UNCHANGED << i, from, list2, characters, domain, old, 
                                  temp, arg, lab, index >>

REMOVEEMPTY == /\ pc = "REMOVEEMPTY"
               /\ TRUE
               /\ pc' = "END"
               /\ UNCHANGED << i, from, list, list2, characters, domain, old, 
                               temp, arg, lab, index >>

FOREACHFROM == /\ pc = "FOREACHFROM"
               /\ IF Empty(list) = FALSE
                     THEN /\ pc' = "FOREACHNOTEMPTY"
                     ELSE /\ TRUE
                          /\ pc' = "END"
               /\ UNCHANGED << i, from, list, list2, characters, domain, old, 
                               temp, arg, lab, index >>

FOREACHNOTEMPTY == /\ pc = "FOREACHNOTEMPTY"
                   /\ lab' = First(list)
                   /\ arg' = {lab'}
                   /\ pc' = "FOREACHFROMLOOP"
                   /\ UNCHANGED << i, from, list, list2, characters, domain, 
                                   old, temp, index >>

FOREACHFROMLOOP == /\ pc = "FOREACHFROMLOOP"
                   /\ IF from < 1
                         THEN /\ lab' = list[lab]["next"]
                              /\ arg' = (arg \union {lab'})
                              /\ from' = from + 1
                              /\ pc' = "FOREACHFROMLOOP"
                         ELSE /\ pc' = "FOREACHFROMRUN"
                              /\ UNCHANGED << from, arg, lab >>
                   /\ UNCHANGED << i, list, list2, characters, domain, old, 
                                   temp, index >>

FOREACHFROMRUN == /\ pc = "FOREACHFROMRUN"
                  /\ list' = ForEachFrom(list, {el \in DOMAIN list: el \notin arg}, ForEachOperator)
                  /\ from' = 1
                  /\ pc' = "END"
                  /\ UNCHANGED << i, list2, characters, domain, old, temp, arg, 
                                  lab, index >>

END == /\ pc = "END"
       /\ PrintT("===LIST IS===")
       /\ PrintT(list)
       /\ pc' = "Done"
       /\ UNCHANGED << i, from, list, list2, characters, domain, old, temp, 
                       arg, lab, index >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == PRECONDITIONS \/ INSERTHEAD \/ CONCAT \/ SWAP \/ REMOVE
           \/ REMOVENOTEMPTY \/ REMOVEEMPTY \/ FOREACHFROM \/ FOREACHNOTEMPTY
           \/ FOREACHFROMLOOP \/ FOREACHFROMRUN \/ END
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 



=============================================================================

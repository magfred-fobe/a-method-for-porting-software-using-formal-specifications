-------------------------------- MODULE main --------------------------------
EXTENDS FiniteSets, Sequences, Integers
LOCAL INSTANCE TLC
CONSTANTS NULL, VALUE
INSTANCE LinkedList
                              
(* --algorithm List

\* Global variables
variables 
depth = 3,
index = 0,
i = 0,
from = 1,
list = LinkedList({}),
list2 = LinkedList({}),
temp = NULL,
arg = {},
lab = NULL

define

\* Invariants
HasFirst == Empty(list) \/ \E el \in DOMAIN list: First(list) = el /\ First(list) \notin Range(list)

HasLast == Empty(list) \/ \E el \in DOMAIN list: list[el]["next"] = NULL 

NullNotInDomain == Empty(list) \/ NULL \notin DOMAIN list

ValidList == IsLinkedList(list) /\ IsLinkedList(list2)

RemoveInvariant == IF Empty(list) THEN TRUE
                   ELSE IF Cardinality(DOMAIN list) = 1 THEN EmptyList = RemoveHead(list)
                   ELSE 
                     /\ Cardinality(DOMAIN list) = (Cardinality(DOMAIN Remove(CHOOSE el \in DOMAIN list: TRUE, list)) + 1)
                     /\ \E el \in DOMAIN list: el \notin DOMAIN Remove(CHOOSE e \in DOMAIN list: TRUE, list)

RemovePrevInvariant == IF Cardinality(DOMAIN list) < 2 THEN TRUE
                       ELSE 
                         /\ Cardinality(DOMAIN list) - 1 = Cardinality(DOMAIN RemovePrev(CHOOSE l \in DOMAIN list: l \in Range(list), list))
                         /\ \E el \in DOMAIN list: el \notin DOMAIN RemovePrev(CHOOSE l \in DOMAIN list: l \in Range(list), list)

InsertInvariant == IF Empty(list) THEN First(InsertHead(NewLabel(list), list)) = NewLabel(list)
                   ELSE 
                     /\ Cardinality(DOMAIN InsertAfter(CHOOSE el \in DOMAIN list: TRUE, list)) = (Cardinality(DOMAIN list) + 1)
                     /\ \E el \in DOMAIN InsertAfter(CHOOSE el \in DOMAIN list: TRUE, list): el \notin DOMAIN list

ConcatInvariant == IF Empty(list) THEN Concat(list, list2)[1] = list2 /\ Empty(Concat(list, list2)[2]) 
                   ELSE IF Empty(list2) THEN Concat(list2, list)[1] = list /\ Empty(Concat(list2, list)[2])
                   ELSE /\ DOMAIN list \subseteq DOMAIN Concat(list, list2)[1] 
                        /\ Empty(Concat(list, list2)[2])
                        /\ DOMAIN list \subseteq DOMAIN Concat(list2, list)[1] 
                        /\ Empty(Concat(list2, list)[2])
                        /\ DOMAIN list2 \subseteq DOMAIN Concat(list, list2)[1] 
                        /\ DOMAIN list2 \subseteq DOMAIN Concat(list2, list)[1]
                        
SwapInvariant == IF Empty(list) THEN Swap(list, list2)[1] = list2 /\ Empty(Swap(list, list2)[2])
                 ELSE IF Empty(list2) THEN Empty(Swap(list, list2)[1]) /\ Swap(list, list2)[2] = list
                 ELSE /\ Swap(list, list2)[1] = list2 
                      /\ Swap(list, list2)[2] = list
                      /\ Swap(list2, list)[1] = list
                      /\ Swap(list2, list)[2] = list2

NextInvariant == \A el \in Range(list): \E e \in DOMAIN list: GetNext(e, list) = el
                      
\* Assertion operators for the for each functions since they are special cases of functionality.

ForEachedList == \A el \in DOMAIN list: list[el]["value"] /= temp[el]["value"]

ForEachedFromList == \A el \in DOMAIN list \ arg: list[el]["value"] /= temp[el]["value"]

(* A helper operator for providing proof of concept of what the ForEach functionality could do. The return 
   value x*2 could be replaced by anything the implementor wants but for example x² would break the ForEach 
   assertions but is an equally valid implementation *) 
ForEachOperator(x) == x*2

end define


\* The model checking alogrithm
begin
    \* with either list1 empty or a list of size 1 to 3
    PRECONDITIONS:
    with size \in 0..2 do
        list := LinkedList(NewDomain(size, list));
    end with;
        
    \* Do the following from each starting state
    LOOP:
    while index < depth do
        either
            INSERTHEAD:
            list := InsertHead(NewLabel(list), list);
        or  
            INSERTAFTER:
            if Empty(list) then
            skip;
            else
            list := InsertAfter(CHOOSE value \in DOMAIN list: TRUE, list);
            end if;
        or 
            PRECONCAT: 
            with size \in 0..1 do
            list2 := LinkedList(NewDomain(size, list));
            end with;            
            
            CONCAT:  
            temp := Concat(list, list2);
            list := temp[1];
            list2:= temp[2];
        or 
            PRESWAP:
            with size \in 0..1 do
            list2 := LinkedList(NewDomain(size, list));
            end with;
            
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
                skip;
            end if;
        or  
            REMOVEAFTER:
            if Cardinality(DOMAIN list) < 2 then
            skip;
            else   
            list := RemoveAfter(CHOOSE l \in DOMAIN list: list[l]["next"] \in DOMAIN list, list);
            end if;
        or  
            REMOVEHEAD:           
            if Empty(list) then
            skip;
            else
            list := RemoveHead(list);
            end if;
        or  
            REMOVEPREV:
            if Cardinality(DOMAIN list) < 2 then
            skip;
            else
            list := RemovePrev(CHOOSE l \in DOMAIN list: l \in Range(list), list);    
            end if;
        or
            FOREACH:
            if Empty(list) then
            skip;
            else
            temp := list;
            list := ForEach(list, ForEachOperator);
            
            ASSERTFOREACH:
            assert ForEachedList;
            end if;
        or 
            FOREACHFROM:
            \* just to make it work with empty lists as well
            if Empty(list) then
            skip;
            else
            temp := list;
            lab := First(list);
            arg := {lab};
            i := 1;
            with length \in 1..Cardinality(DOMAIN list)do
            from := length;
            end with;
                  
            FOREACHFROMRUN:
            while i < from do
                lab := list[lab]["next"];
                arg := arg \union {lab};
                i := i + 1;
            end while; 
            list := ForEachFrom(list, {el \in DOMAIN list: el \notin arg}, ForEachOperator);
                
            ASSERTFOREACHFROM:
            assert ForEachedFromList;  
            end if;
        end either;
 
    INCREMENT:
    index := index + 1;
    end while;
 
end algorithm;*)
\* BEGIN TRANSLATION (chksum(pcal) = "d3777105" /\ chksum(tla) = "f1040f35")
VARIABLES depth, index, i, from, list, list2, temp, arg, lab, pc

(* define statement *)
HasFirst == Empty(list) \/ \E el \in DOMAIN list: First(list) = el /\ First(list) \notin Range(list)

HasLast == Empty(list) \/ \E el \in DOMAIN list: list[el]["next"] = NULL

NullNotInDomain == Empty(list) \/ NULL \notin DOMAIN list

ValidList == IsLinkedList(list) /\ IsLinkedList(list2)

RemoveInvariant == IF Empty(list) THEN TRUE
                   ELSE IF Cardinality(DOMAIN list) = 1 THEN EmptyList = RemoveHead(list)
                   ELSE
                     /\ Cardinality(DOMAIN list) = (Cardinality(DOMAIN Remove(CHOOSE el \in DOMAIN list: TRUE, list)) + 1)
                     /\ \E el \in DOMAIN list: el \notin DOMAIN Remove(CHOOSE e \in DOMAIN list: TRUE, list)

RemovePrevInvariant == IF Cardinality(DOMAIN list) < 2 THEN TRUE
                       ELSE
                         /\ Cardinality(DOMAIN list) - 1 = Cardinality(DOMAIN RemovePrev(CHOOSE l \in DOMAIN list: l \in Range(list), list))
                         /\ \E el \in DOMAIN list: el \notin DOMAIN RemovePrev(CHOOSE l \in DOMAIN list: l \in Range(list), list)

InsertInvariant == IF Empty(list) THEN First(InsertHead(NewLabel(list), list)) = NewLabel(list)
                   ELSE
                     /\ Cardinality(DOMAIN InsertAfter(CHOOSE el \in DOMAIN list: TRUE, list)) = (Cardinality(DOMAIN list) + 1)
                     /\ \E el \in DOMAIN InsertAfter(CHOOSE el \in DOMAIN list: TRUE, list): el \notin DOMAIN list

ConcatInvariant == IF Empty(list) THEN Concat(list, list2)[1] = list2 /\ Empty(Concat(list, list2)[2])
                   ELSE IF Empty(list2) THEN Concat(list2, list)[1] = list /\ Empty(Concat(list2, list)[2])
                   ELSE /\ DOMAIN list \subseteq DOMAIN Concat(list, list2)[1]
                        /\ Empty(Concat(list, list2)[2])
                        /\ DOMAIN list \subseteq DOMAIN Concat(list2, list)[1]
                        /\ Empty(Concat(list2, list)[2])
                        /\ DOMAIN list2 \subseteq DOMAIN Concat(list, list2)[1]
                        /\ DOMAIN list2 \subseteq DOMAIN Concat(list2, list)[1]

SwapInvariant == IF Empty(list) THEN Swap(list, list2)[1] = list2 /\ Empty(Swap(list, list2)[2])
                 ELSE IF Empty(list2) THEN Empty(Swap(list, list2)[1]) /\ Swap(list, list2)[2] = list
                 ELSE /\ Swap(list, list2)[1] = list2
                      /\ Swap(list, list2)[2] = list
                      /\ Swap(list2, list)[1] = list
                      /\ Swap(list2, list)[2] = list2

NextInvariant == \A el \in Range(list): \E e \in DOMAIN list: GetNext(e, list) = el



ForEachedList == \A el \in DOMAIN list: list[el]["value"] /= temp[el]["value"]

ForEachedFromList == \A el \in DOMAIN list \ arg: list[el]["value"] /= temp[el]["value"]




ForEachOperator(x) == x*2


vars == << depth, index, i, from, list, list2, temp, arg, lab, pc >>

Init == (* Global variables *)
        /\ depth = 3
        /\ index = 0
        /\ i = 0
        /\ from = 1
        /\ list = LinkedList({})
        /\ list2 = LinkedList({})
        /\ temp = NULL
        /\ arg = {}
        /\ lab = NULL
        /\ pc = "PRECONDITIONS"

PRECONDITIONS == /\ pc = "PRECONDITIONS"
                 /\ \E size \in 0..2:
                      list' = LinkedList(NewDomain(size, list))
                 /\ pc' = "LOOP"
                 /\ UNCHANGED << depth, index, i, from, list2, temp, arg, lab >>

LOOP == /\ pc = "LOOP"
        /\ IF index < depth
              THEN /\ \/ /\ pc' = "INSERTHEAD"
                      \/ /\ pc' = "INSERTAFTER"
                      \/ /\ pc' = "PRECONCAT"
                      \/ /\ pc' = "PRESWAP"
                      \/ /\ pc' = "REMOVE"
                      \/ /\ pc' = "REMOVEAFTER"
                      \/ /\ pc' = "REMOVEHEAD"
                      \/ /\ pc' = "REMOVEPREV"
                      \/ /\ pc' = "FOREACH"
                      \/ /\ pc' = "FOREACHFROM"
              ELSE /\ pc' = "Done"
        /\ UNCHANGED << depth, index, i, from, list, list2, temp, arg, lab >>

INCREMENT == /\ pc = "INCREMENT"
             /\ index' = index + 1
             /\ pc' = "LOOP"
             /\ UNCHANGED << depth, i, from, list, list2, temp, arg, lab >>

INSERTHEAD == /\ pc = "INSERTHEAD"
              /\ list' = InsertHead(NewLabel(list), list)
              /\ pc' = "INCREMENT"
              /\ UNCHANGED << depth, index, i, from, list2, temp, arg, lab >>

INSERTAFTER == /\ pc = "INSERTAFTER"
               /\ IF Empty(list)
                     THEN /\ TRUE
                          /\ list' = list
                     ELSE /\ list' = InsertAfter(CHOOSE value \in DOMAIN list: TRUE, list)
               /\ pc' = "INCREMENT"
               /\ UNCHANGED << depth, index, i, from, list2, temp, arg, lab >>

PRECONCAT == /\ pc = "PRECONCAT"
             /\ \E size \in 0..1:
                  list2' = LinkedList(NewDomain(size, list))
             /\ pc' = "CONCAT"
             /\ UNCHANGED << depth, index, i, from, list, temp, arg, lab >>

CONCAT == /\ pc = "CONCAT"
          /\ temp' = Concat(list, list2)
          /\ list' = temp'[1]
          /\ list2' = temp'[2]
          /\ pc' = "INCREMENT"
          /\ UNCHANGED << depth, index, i, from, arg, lab >>

PRESWAP == /\ pc = "PRESWAP"
           /\ \E size \in 0..1:
                list2' = LinkedList(NewDomain(size, list))
           /\ pc' = "SWAP"
           /\ UNCHANGED << depth, index, i, from, list, temp, arg, lab >>

SWAP == /\ pc = "SWAP"
        /\ temp' = Swap(list, list2)
        /\ list' = temp'[1]
        /\ list2' = temp'[2]
        /\ pc' = "INCREMENT"
        /\ UNCHANGED << depth, index, i, from, arg, lab >>

REMOVE == /\ pc = "REMOVE"
          /\ IF Empty(list) = FALSE
                THEN /\ pc' = "REMOVENOTEMPTY"
                ELSE /\ TRUE
                     /\ pc' = "INCREMENT"
          /\ UNCHANGED << depth, index, i, from, list, list2, temp, arg, lab >>

REMOVENOTEMPTY == /\ pc = "REMOVENOTEMPTY"
                  /\ list' = Remove(CHOOSE x \in DOMAIN list:TRUE, list)
                  /\ pc' = "INCREMENT"
                  /\ UNCHANGED << depth, index, i, from, list2, temp, arg, lab >>

REMOVEAFTER == /\ pc = "REMOVEAFTER"
               /\ IF Cardinality(DOMAIN list) < 2
                     THEN /\ TRUE
                          /\ list' = list
                     ELSE /\ list' = RemoveAfter(CHOOSE l \in DOMAIN list: list[l]["next"] \in DOMAIN list, list)
               /\ pc' = "INCREMENT"
               /\ UNCHANGED << depth, index, i, from, list2, temp, arg, lab >>

REMOVEHEAD == /\ pc = "REMOVEHEAD"
              /\ IF Empty(list)
                    THEN /\ TRUE
                         /\ list' = list
                    ELSE /\ list' = RemoveHead(list)
              /\ pc' = "INCREMENT"
              /\ UNCHANGED << depth, index, i, from, list2, temp, arg, lab >>

REMOVEPREV == /\ pc = "REMOVEPREV"
              /\ IF Cardinality(DOMAIN list) < 2
                    THEN /\ TRUE
                         /\ list' = list
                    ELSE /\ list' = RemovePrev(CHOOSE l \in DOMAIN list: l \in Range(list), list)
              /\ pc' = "INCREMENT"
              /\ UNCHANGED << depth, index, i, from, list2, temp, arg, lab >>

FOREACH == /\ pc = "FOREACH"
           /\ IF Empty(list)
                 THEN /\ TRUE
                      /\ pc' = "INCREMENT"
                      /\ UNCHANGED << list, temp >>
                 ELSE /\ temp' = list
                      /\ list' = ForEach(list, ForEachOperator)
                      /\ pc' = "ASSERTFOREACH"
           /\ UNCHANGED << depth, index, i, from, list2, arg, lab >>

ASSERTFOREACH == /\ pc = "ASSERTFOREACH"
                 /\ Assert(ForEachedList, 
                           "Failure of assertion at line 160, column 13.")
                 /\ pc' = "INCREMENT"
                 /\ UNCHANGED << depth, index, i, from, list, list2, temp, arg, 
                                 lab >>

FOREACHFROM == /\ pc = "FOREACHFROM"
               /\ IF Empty(list)
                     THEN /\ TRUE
                          /\ pc' = "INCREMENT"
                          /\ UNCHANGED << i, from, temp, arg, lab >>
                     ELSE /\ temp' = list
                          /\ lab' = First(list)
                          /\ arg' = {lab'}
                          /\ i' = 1
                          /\ \E length \in 1..Cardinality(DOMAIN list):
                               from' = length
                          /\ pc' = "FOREACHFROMRUN"
               /\ UNCHANGED << depth, index, list, list2 >>

FOREACHFROMRUN == /\ pc = "FOREACHFROMRUN"
                  /\ IF i < from
                        THEN /\ lab' = list[lab]["next"]
                             /\ arg' = (arg \union {lab'})
                             /\ i' = i + 1
                             /\ pc' = "FOREACHFROMRUN"
                             /\ list' = list
                        ELSE /\ list' = ForEachFrom(list, {el \in DOMAIN list: el \notin arg}, ForEachOperator)
                             /\ pc' = "ASSERTFOREACHFROM"
                             /\ UNCHANGED << i, arg, lab >>
                  /\ UNCHANGED << depth, index, from, list2, temp >>

ASSERTFOREACHFROM == /\ pc = "ASSERTFOREACHFROM"
                     /\ Assert(ForEachedFromList, 
                               "Failure of assertion at line 185, column 13.")
                     /\ pc' = "INCREMENT"
                     /\ UNCHANGED << depth, index, i, from, list, list2, temp, 
                                     arg, lab >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == PRECONDITIONS \/ LOOP \/ INCREMENT \/ INSERTHEAD \/ INSERTAFTER
           \/ PRECONCAT \/ CONCAT \/ PRESWAP \/ SWAP \/ REMOVE \/ REMOVENOTEMPTY
           \/ REMOVEAFTER \/ REMOVEHEAD \/ REMOVEPREV \/ FOREACH \/ ASSERTFOREACH
           \/ FOREACHFROM \/ FOREACHFROMRUN \/ ASSERTFOREACHFROM
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 


=============================================================================

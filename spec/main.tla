-------------------------------- MODULE main --------------------------------
EXTENDS FiniteSets, Sequences, Integers
LOCAL INSTANCE TLC
CONSTANTS NULL, VALUE
INSTANCE LinkedList
                              
(* --algorithm List

\* Global variables
variables 
depth = 5,
index = 0,
i = 0,
from = 1,
list = LinkedList({}),
list2 = LinkedList({}),
temp = NULL,
arg = {},
lab = NULL,
lab2 = NULL,
preInsertSize = NULL,
preRemoveSize = NULL,
nl = NULL,
l1 = NULL,
l2 = NULL

\* Global and local invariants the model is based on 
define

\* Invariants
HasFirst == Empty(list) \/ \E el \in DOMAIN list: First(list) = el /\ First(list) \notin Range(list)

HasLast == Empty(list) \/ \E el \in DOMAIN list: list[el]["next"] = NULL \* invariant for all lists

ValidList == IsLinkedList(list) /\ IsLinkedList(list2)



\* Assertion operators called when respective functionality has been applied on the list.
HeadElementInserted == Cardinality(DOMAIN list) = (preInsertSize + 1) /\ nl \in DOMAIN list /\ nl = First(list)

ElementInsertedAfter == preInsertSize + 1 = Cardinality(DOMAIN list) /\ list[lab]["next"] /= lab2 /\ list[lab]["next"] \notin DOMAIN temp 

ListsConcatenated == IF Empty(l1) /\ Empty(l2) THEN Empty(list) /\ Empty(list2) 
                     ELSE IF Empty(l1) THEN Empty(list2) /\ \A el \in DOMAIN l2: l2[el] = list[el]
                     ELSE IF Empty(l2) THEN Empty(list2) /\ \A el \in DOMAIN l1: l1[el] = list[el]
                     ELSE Empty(list2) /\ \A e \in DOMAIN l1: e \in DOMAIN list /\ \A el \in DOMAIN l2: el \in DOMAIN list

ListsSwapped == \A e \in DOMAIN l1: e \in DOMAIN list2 /\ \A el \in DOMAIN l2: el \in DOMAIN list

ElementRemoved == lab \notin DOMAIN list

ElementAfterRemoved == preRemoveSize - 1 = Cardinality(DOMAIN list) /\ lab2 \notin DOMAIN list /\ lab2 /= list[lab]["next"]

RemovedHead == IF Empty(list) THEN preRemoveSize - 1 = 0 /\ lab \notin DOMAIN list 
               ELSE preRemoveSize - 1 = Cardinality(DOMAIN list) /\ lab \notin DOMAIN list /\ lab /= First(list)

RemovedPrev == lab2 \notin DOMAIN list /\ preRemoveSize - 1 = Cardinality(DOMAIN list)

NextGotten == list[lab]["next"] = lab2 /\ lab2 \in Range(list)

ForEachedList == \A el \in DOMAIN list: list[el]["value"] /= temp[el]["value"]

ForEachedFromList == \A el \in DOMAIN list \ arg: list[el]["value"] /= temp[el]["value"]

(*A helper operator for providing proof of concept of what the ForEach functionality could do. The return 
  value x*2 could be replaced by anything the implementor wants but for example x² would break the ForEach 
  assertions but is an equally valid implementation*) 
ForEachOperator(x) == x*2

end define

\* Sets the pre insertsize and used to avoid duplicate code.
macro set_preInsertSize() begin
  if Empty(list) then
     preInsertSize := 0;
  else 
     preInsertSize := Cardinality(DOMAIN list);
  end if;
end macro;

\* The model checking alogrithm
begin
    \* with either list1 empty or a list of size 1 to 3
    PRECONDITIONS:
    with size \in 0..3 do
        list := LinkedList(NewDomain(size, list));
    end with;
        
    \* Do the following from each starting state
    LOOP:
    while index < depth do
        either
            INSERTHEAD:
            set_preInsertSize();
            nl := NewLabel(list);
            list := InsertHead(nl, list);
          
            ASSERTINSERTHEAD:
            assert HeadElementInserted;
        or  
            INSERTAFTER:
            if Empty(list) then
            skip;
            else
            set_preInsertSize();
            lab := CHOOSE value \in DOMAIN list: TRUE;
            lab2 := list[lab]["next"];
            temp := list;
            list := InsertAfter(lab, list);
            
            ASSERTINSERTAFTER:
            assert ElementInsertedAfter;
            end if;
        or 
            PRECONCAT: 
            with size \in 0..1 do
            list2 := LinkedList(NewDomain(size, list));
            end with;            
            l1 := list;
            l2 := list2; 
            
            CONCAT:  
            temp := Concat(list, list2);
            list := temp[1];
            list2:= temp[2];
            
            ASSERTCONCAT:
            assert ListsConcatenated;
        or 
            PRESWAP:
            with size \in 0..1 do
            list2 := LinkedList(NewDomain(size, list));
            end with;
            l1 := list;
            l2 := list2;
            
            SWAP:
            temp := Swap(list, list2);
            list := temp[1];
            list2 := temp[2];
            
            ASSERTSWAP:
            assert ListsSwapped;
        or
            REMOVE:
            \* just to make it work with empty lists as well
            if Empty(list) = FALSE then
                REMOVENOTEMPTY:
                lab := CHOOSE x \in DOMAIN list:TRUE;
                list := Remove(lab, list);
                
                ASSERTREMOVE:
                assert ElementRemoved;
            else 
                REMOVEEMPTY:
                skip;
            end if;
        or  
            REMOVEAFTER:
            if Cardinality(DOMAIN list) < 2 then
            skip;
            else 
            preRemoveSize := Cardinality(DOMAIN list);
            lab := CHOOSE l \in DOMAIN list: list[l]["next"] \in DOMAIN list;
            lab2 := list[lab]["next"];
            list := RemoveAfter(lab, list);
            
            ASSERTREMOVEAFTER:
            assert ElementAfterRemoved;
            end if;
        or  
            REMOVEHEAD:           
            if Empty(list) then
            skip;
            else
            lab := First(list);
            preRemoveSize := Cardinality(DOMAIN list);
            list := RemoveHead(list);
            
            ASSERTREMOVEHEAD:
            assert RemovedHead;
            end if;
        or  
            REMOVEPREV:
            if Cardinality(DOMAIN list) < 2 then
            skip;
            else
            preRemoveSize := Cardinality(DOMAIN list);
            lab := CHOOSE l \in DOMAIN list: l \in Range(list);
            lab2 := CHOOSE l \in DOMAIN list: list[l]["next"] = lab;
            list := RemovePrev(lab, list);
            
            ASSERTREMOVEPREV:
            assert RemovedPrev;
            end if;
        or
            GETNEXT:
            lab := CHOOSE l \in DOMAIN list: TRUE;
            lab2 := GetNext(lab, list);
            
            GOTNEXT:
            assert NextGotten;
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
\* BEGIN TRANSLATION (chksum(pcal) = "43b717f1" /\ chksum(tla) = "45778705")
VARIABLES depth, index, i, from, list, list2, temp, arg, lab, lab2, 
          preInsertSize, preRemoveSize, nl, l1, l2, pc

(* define statement *)
HasFirst == Empty(list) \/ \E el \in DOMAIN list: First(list) = el /\ First(list) \notin Range(list)

HasLast == Empty(list) \/ \E el \in DOMAIN list: list[el]["next"] = NULL

ValidList == IsLinkedList(list) /\ IsLinkedList(list2)




HeadElementInserted == Cardinality(DOMAIN list) = (preInsertSize + 1) /\ nl \in DOMAIN list /\ nl = First(list)

ElementInsertedAfter == preInsertSize + 1 = Cardinality(DOMAIN list) /\ list[lab]["next"] /= lab2 /\ list[lab]["next"] \notin DOMAIN temp

ListsConcatenated == IF Empty(l1) /\ Empty(l2) THEN Empty(list) /\ Empty(list2)
                     ELSE IF Empty(l1) THEN Empty(list2) /\ \A el \in DOMAIN l2: l2[el] = list[el]
                     ELSE IF Empty(l2) THEN Empty(list2) /\ \A el \in DOMAIN l1: l1[el] = list[el]
                     ELSE Empty(list2) /\ \A e \in DOMAIN l1: e \in DOMAIN list /\ \A el \in DOMAIN l2: el \in DOMAIN list

ListsSwapped == \A e \in DOMAIN l1: e \in DOMAIN list2 /\ \A el \in DOMAIN l2: el \in DOMAIN list

ElementRemoved == lab \notin DOMAIN list

ElementAfterRemoved == preRemoveSize - 1 = Cardinality(DOMAIN list) /\ lab2 \notin DOMAIN list /\ lab2 /= list[lab]["next"]

RemovedHead == IF Empty(list) THEN preRemoveSize - 1 = 0 /\ lab \notin DOMAIN list
               ELSE preRemoveSize - 1 = Cardinality(DOMAIN list) /\ lab \notin DOMAIN list /\ lab /= First(list)

RemovedPrev == lab2 \notin DOMAIN list /\ preRemoveSize - 1 = Cardinality(DOMAIN list)

NextGotten == list[lab]["next"] = lab2 /\ lab2 \in Range(list)

ForEachedList == \A el \in DOMAIN list: list[el]["value"] /= temp[el]["value"]

ForEachedFromList == \A el \in DOMAIN list \ arg: list[el]["value"] /= temp[el]["value"]




ForEachOperator(x) == x*2


vars == << depth, index, i, from, list, list2, temp, arg, lab, lab2, 
           preInsertSize, preRemoveSize, nl, l1, l2, pc >>

Init == (* Global variables *)
        /\ depth = 5
        /\ index = 0
        /\ i = 0
        /\ from = 1
        /\ list = LinkedList({})
        /\ list2 = LinkedList({})
        /\ temp = NULL
        /\ arg = {}
        /\ lab = NULL
        /\ lab2 = NULL
        /\ preInsertSize = NULL
        /\ preRemoveSize = NULL
        /\ nl = NULL
        /\ l1 = NULL
        /\ l2 = NULL
        /\ pc = "PRECONDITIONS"

PRECONDITIONS == /\ pc = "PRECONDITIONS"
                 /\ \E size \in 0..3:
                      list' = LinkedList(NewDomain(size, list))
                 /\ pc' = "LOOP"
                 /\ UNCHANGED << depth, index, i, from, list2, temp, arg, lab, 
                                 lab2, preInsertSize, preRemoveSize, nl, l1, 
                                 l2 >>

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
                      \/ /\ pc' = "GETNEXT"
                      \/ /\ pc' = "FOREACH"
                      \/ /\ pc' = "FOREACHFROM"
              ELSE /\ pc' = "Done"
        /\ UNCHANGED << depth, index, i, from, list, list2, temp, arg, lab, 
                        lab2, preInsertSize, preRemoveSize, nl, l1, l2 >>

INCREMENT == /\ pc = "INCREMENT"
             /\ index' = index + 1
             /\ pc' = "LOOP"
             /\ UNCHANGED << depth, i, from, list, list2, temp, arg, lab, lab2, 
                             preInsertSize, preRemoveSize, nl, l1, l2 >>

INSERTHEAD == /\ pc = "INSERTHEAD"
              /\ IF Empty(list)
                    THEN /\ preInsertSize' = 0
                    ELSE /\ preInsertSize' = Cardinality(DOMAIN list)
              /\ nl' = NewLabel(list)
              /\ list' = InsertHead(nl', list)
              /\ pc' = "ASSERTINSERTHEAD"
              /\ UNCHANGED << depth, index, i, from, list2, temp, arg, lab, 
                              lab2, preRemoveSize, l1, l2 >>

ASSERTINSERTHEAD == /\ pc = "ASSERTINSERTHEAD"
                    /\ Assert(HeadElementInserted, 
                              "Failure of assertion at line 100, column 13.")
                    /\ pc' = "INCREMENT"
                    /\ UNCHANGED << depth, index, i, from, list, list2, temp, 
                                    arg, lab, lab2, preInsertSize, 
                                    preRemoveSize, nl, l1, l2 >>

INSERTAFTER == /\ pc = "INSERTAFTER"
               /\ IF Empty(list)
                     THEN /\ TRUE
                          /\ pc' = "INCREMENT"
                          /\ UNCHANGED << list, temp, lab, lab2, preInsertSize >>
                     ELSE /\ IF Empty(list)
                                THEN /\ preInsertSize' = 0
                                ELSE /\ preInsertSize' = Cardinality(DOMAIN list)
                          /\ lab' = (CHOOSE value \in DOMAIN list: TRUE)
                          /\ lab2' = list[lab']["next"]
                          /\ temp' = list
                          /\ list' = InsertAfter(lab', list)
                          /\ pc' = "ASSERTINSERTAFTER"
               /\ UNCHANGED << depth, index, i, from, list2, arg, 
                               preRemoveSize, nl, l1, l2 >>

ASSERTINSERTAFTER == /\ pc = "ASSERTINSERTAFTER"
                     /\ Assert(ElementInsertedAfter, 
                               "Failure of assertion at line 113, column 13.")
                     /\ pc' = "INCREMENT"
                     /\ UNCHANGED << depth, index, i, from, list, list2, temp, 
                                     arg, lab, lab2, preInsertSize, 
                                     preRemoveSize, nl, l1, l2 >>

PRECONCAT == /\ pc = "PRECONCAT"
             /\ \E size \in 0..1:
                  list2' = LinkedList(NewDomain(size, list))
             /\ l1' = list
             /\ l2' = list2'
             /\ pc' = "CONCAT"
             /\ UNCHANGED << depth, index, i, from, list, temp, arg, lab, lab2, 
                             preInsertSize, preRemoveSize, nl >>

CONCAT == /\ pc = "CONCAT"
          /\ temp' = Concat(list, list2)
          /\ list' = temp'[1]
          /\ list2' = temp'[2]
          /\ pc' = "ASSERTCONCAT"
          /\ UNCHANGED << depth, index, i, from, arg, lab, lab2, preInsertSize, 
                          preRemoveSize, nl, l1, l2 >>

ASSERTCONCAT == /\ pc = "ASSERTCONCAT"
                /\ Assert(ListsConcatenated, 
                          "Failure of assertion at line 129, column 13.")
                /\ pc' = "INCREMENT"
                /\ UNCHANGED << depth, index, i, from, list, list2, temp, arg, 
                                lab, lab2, preInsertSize, preRemoveSize, nl, 
                                l1, l2 >>

PRESWAP == /\ pc = "PRESWAP"
           /\ \E size \in 0..1:
                list2' = LinkedList(NewDomain(size, list))
           /\ l1' = list
           /\ l2' = list2'
           /\ pc' = "SWAP"
           /\ UNCHANGED << depth, index, i, from, list, temp, arg, lab, lab2, 
                           preInsertSize, preRemoveSize, nl >>

SWAP == /\ pc = "SWAP"
        /\ temp' = Swap(list, list2)
        /\ list' = temp'[1]
        /\ list2' = temp'[2]
        /\ pc' = "ASSERTSWAP"
        /\ UNCHANGED << depth, index, i, from, arg, lab, lab2, preInsertSize, 
                        preRemoveSize, nl, l1, l2 >>

ASSERTSWAP == /\ pc = "ASSERTSWAP"
              /\ Assert(ListsSwapped, 
                        "Failure of assertion at line 144, column 13.")
              /\ pc' = "INCREMENT"
              /\ UNCHANGED << depth, index, i, from, list, list2, temp, arg, 
                              lab, lab2, preInsertSize, preRemoveSize, nl, l1, 
                              l2 >>

REMOVE == /\ pc = "REMOVE"
          /\ IF Empty(list) = FALSE
                THEN /\ pc' = "REMOVENOTEMPTY"
                ELSE /\ pc' = "REMOVEEMPTY"
          /\ UNCHANGED << depth, index, i, from, list, list2, temp, arg, lab, 
                          lab2, preInsertSize, preRemoveSize, nl, l1, l2 >>

REMOVENOTEMPTY == /\ pc = "REMOVENOTEMPTY"
                  /\ lab' = (CHOOSE x \in DOMAIN list:TRUE)
                  /\ list' = Remove(lab', list)
                  /\ pc' = "ASSERTREMOVE"
                  /\ UNCHANGED << depth, index, i, from, list2, temp, arg, 
                                  lab2, preInsertSize, preRemoveSize, nl, l1, 
                                  l2 >>

ASSERTREMOVE == /\ pc = "ASSERTREMOVE"
                /\ Assert(ElementRemoved, 
                          "Failure of assertion at line 154, column 17.")
                /\ pc' = "INCREMENT"
                /\ UNCHANGED << depth, index, i, from, list, list2, temp, arg, 
                                lab, lab2, preInsertSize, preRemoveSize, nl, 
                                l1, l2 >>

REMOVEEMPTY == /\ pc = "REMOVEEMPTY"
               /\ TRUE
               /\ pc' = "INCREMENT"
               /\ UNCHANGED << depth, index, i, from, list, list2, temp, arg, 
                               lab, lab2, preInsertSize, preRemoveSize, nl, l1, 
                               l2 >>

REMOVEAFTER == /\ pc = "REMOVEAFTER"
               /\ IF Cardinality(DOMAIN list) < 2
                     THEN /\ TRUE
                          /\ pc' = "INCREMENT"
                          /\ UNCHANGED << list, lab, lab2, preRemoveSize >>
                     ELSE /\ preRemoveSize' = Cardinality(DOMAIN list)
                          /\ lab' = (CHOOSE l \in DOMAIN list: list[l]["next"] \in DOMAIN list)
                          /\ lab2' = list[lab']["next"]
                          /\ list' = RemoveAfter(lab', list)
                          /\ pc' = "ASSERTREMOVEAFTER"
               /\ UNCHANGED << depth, index, i, from, list2, temp, arg, 
                               preInsertSize, nl, l1, l2 >>

ASSERTREMOVEAFTER == /\ pc = "ASSERTREMOVEAFTER"
                     /\ Assert(ElementAfterRemoved, 
                               "Failure of assertion at line 170, column 13.")
                     /\ pc' = "INCREMENT"
                     /\ UNCHANGED << depth, index, i, from, list, list2, temp, 
                                     arg, lab, lab2, preInsertSize, 
                                     preRemoveSize, nl, l1, l2 >>

REMOVEHEAD == /\ pc = "REMOVEHEAD"
              /\ IF Empty(list)
                    THEN /\ TRUE
                         /\ pc' = "INCREMENT"
                         /\ UNCHANGED << list, lab, preRemoveSize >>
                    ELSE /\ lab' = First(list)
                         /\ preRemoveSize' = Cardinality(DOMAIN list)
                         /\ list' = RemoveHead(list)
                         /\ pc' = "ASSERTREMOVEHEAD"
              /\ UNCHANGED << depth, index, i, from, list2, temp, arg, lab2, 
                              preInsertSize, nl, l1, l2 >>

ASSERTREMOVEHEAD == /\ pc = "ASSERTREMOVEHEAD"
                    /\ Assert(RemovedHead, 
                              "Failure of assertion at line 182, column 13.")
                    /\ pc' = "INCREMENT"
                    /\ UNCHANGED << depth, index, i, from, list, list2, temp, 
                                    arg, lab, lab2, preInsertSize, 
                                    preRemoveSize, nl, l1, l2 >>

REMOVEPREV == /\ pc = "REMOVEPREV"
              /\ IF Cardinality(DOMAIN list) < 2
                    THEN /\ TRUE
                         /\ pc' = "INCREMENT"
                         /\ UNCHANGED << list, lab, lab2, preRemoveSize >>
                    ELSE /\ preRemoveSize' = Cardinality(DOMAIN list)
                         /\ lab' = (CHOOSE l \in DOMAIN list: l \in Range(list))
                         /\ lab2' = (CHOOSE l \in DOMAIN list: list[l]["next"] = lab')
                         /\ list' = RemovePrev(lab', list)
                         /\ pc' = "ASSERTREMOVEPREV"
              /\ UNCHANGED << depth, index, i, from, list2, temp, arg, 
                              preInsertSize, nl, l1, l2 >>

ASSERTREMOVEPREV == /\ pc = "ASSERTREMOVEPREV"
                    /\ Assert(RemovedPrev, 
                              "Failure of assertion at line 195, column 13.")
                    /\ pc' = "INCREMENT"
                    /\ UNCHANGED << depth, index, i, from, list, list2, temp, 
                                    arg, lab, lab2, preInsertSize, 
                                    preRemoveSize, nl, l1, l2 >>

GETNEXT == /\ pc = "GETNEXT"
           /\ lab' = (CHOOSE l \in DOMAIN list: TRUE)
           /\ lab2' = GetNext(lab', list)
           /\ pc' = "GOTNEXT"
           /\ UNCHANGED << depth, index, i, from, list, list2, temp, arg, 
                           preInsertSize, preRemoveSize, nl, l1, l2 >>

GOTNEXT == /\ pc = "GOTNEXT"
           /\ Assert(NextGotten, 
                     "Failure of assertion at line 203, column 13.")
           /\ pc' = "INCREMENT"
           /\ UNCHANGED << depth, index, i, from, list, list2, temp, arg, lab, 
                           lab2, preInsertSize, preRemoveSize, nl, l1, l2 >>

FOREACH == /\ pc = "FOREACH"
           /\ IF Empty(list)
                 THEN /\ TRUE
                      /\ pc' = "INCREMENT"
                      /\ UNCHANGED << list, temp >>
                 ELSE /\ temp' = list
                      /\ list' = ForEach(list, ForEachOperator)
                      /\ pc' = "ASSERTFOREACH"
           /\ UNCHANGED << depth, index, i, from, list2, arg, lab, lab2, 
                           preInsertSize, preRemoveSize, nl, l1, l2 >>

ASSERTFOREACH == /\ pc = "ASSERTFOREACH"
                 /\ Assert(ForEachedList, 
                           "Failure of assertion at line 213, column 13.")
                 /\ pc' = "INCREMENT"
                 /\ UNCHANGED << depth, index, i, from, list, list2, temp, arg, 
                                 lab, lab2, preInsertSize, preRemoveSize, nl, 
                                 l1, l2 >>

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
               /\ UNCHANGED << depth, index, list, list2, lab2, preInsertSize, 
                               preRemoveSize, nl, l1, l2 >>

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
                  /\ UNCHANGED << depth, index, from, list2, temp, lab2, 
                                  preInsertSize, preRemoveSize, nl, l1, l2 >>

ASSERTFOREACHFROM == /\ pc = "ASSERTFOREACHFROM"
                     /\ Assert(ForEachedFromList, 
                               "Failure of assertion at line 238, column 13.")
                     /\ pc' = "INCREMENT"
                     /\ UNCHANGED << depth, index, i, from, list, list2, temp, 
                                     arg, lab, lab2, preInsertSize, 
                                     preRemoveSize, nl, l1, l2 >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == PRECONDITIONS \/ LOOP \/ INCREMENT \/ INSERTHEAD
           \/ ASSERTINSERTHEAD \/ INSERTAFTER \/ ASSERTINSERTAFTER \/ PRECONCAT
           \/ CONCAT \/ ASSERTCONCAT \/ PRESWAP \/ SWAP \/ ASSERTSWAP \/ REMOVE
           \/ REMOVENOTEMPTY \/ ASSERTREMOVE \/ REMOVEEMPTY \/ REMOVEAFTER
           \/ ASSERTREMOVEAFTER \/ REMOVEHEAD \/ ASSERTREMOVEHEAD \/ REMOVEPREV
           \/ ASSERTREMOVEPREV \/ GETNEXT \/ GOTNEXT \/ FOREACH \/ ASSERTFOREACH
           \/ FOREACHFROM \/ FOREACHFROMRUN \/ ASSERTFOREACHFROM
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 


=============================================================================

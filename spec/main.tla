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
temp = NULL,
arg = {},
lab = NULL,
lab2 = NULL,
index = NULL,
preInsertSize = NULL,
preRemoveSize = NULL,
nl = NULL,
l1 = NULL,
l2 = NULL

\* Global and local invariants the model is based on 
define

\* Global invariants
HasLast == Empty(list) \/ \E el \in DOMAIN list: list[el]["next"] = NULL \* invariant for all lists

ValidList == IsLinkedList(list) /\ IsLinkedList(list2)

\* Local invariants called when respective functionality has been applied on the list.
HeadElementInserted == Cardinality(DOMAIN list) = (preInsertSize + 1) /\ nl \in DOMAIN list /\ nl = First(list)

ElementInsertedAfter == preInsertSize + 1 = Cardinality(DOMAIN list) /\ list[lab]["next"] /= lab2 /\ list[lab]["next"] \notin DOMAIN temp 

ListsConcatenated == IF Empty(l1) /\ Empty(l2) THEN Empty(list) /\ Empty(list2) 
                     ELSE IF Empty(l1) THEN Empty(list2) /\ \A el \in DOMAIN l2: l2[el] = list[el]
                     ELSE IF Empty(l2) THEN Empty(list2) /\ \A el \in DOMAIN l1: l1[el] = list[el]
                     ELSE Empty(list2) /\ \A e \in DOMAIN l1: e \in DOMAIN list /\ \A el \in DOMAIN l2: el \in DOMAIN list

ListsSwapped == \A e \in DOMAIN l1: e \in DOMAIN list2 /\ \A el \in DOMAIN l2: el \in DOMAIN list

ElementRemoved == lab \notin DOMAIN list

ElementAfterRemoved == preRemoveSize - 1 = Cardinality(DOMAIN list) /\ lab2 \notin DOMAIN list /\ lab2 /= list[lab]["next"]


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
            CONCAT:   
            l1 := list;
            l2 := list2;   
            temp := Concat(list, list2);
            list := temp[1];
            list2:= temp[2];
            
            ASSERTCONCAT:
            assert ListsConcatenated;
        or 
            SWAP:
            l1 := list;
            l2 := list2;
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
    
   \* END:
   \* print "===LIST IS===";
  \*  print list;
    
 
 (*       
LOOP:
 while i < 3 do
    either 
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
\* BEGIN TRANSLATION (chksum(pcal) = "42a90341" /\ chksum(tla) = "adbbf156")
VARIABLES i, from, list, list2, temp, arg, lab, lab2, index, preInsertSize, 
          preRemoveSize, nl, l1, l2, pc

(* define statement *)
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





ForEachOperator(x) == x*2


vars == << i, from, list, list2, temp, arg, lab, lab2, index, preInsertSize, 
           preRemoveSize, nl, l1, l2, pc >>

Init == (* Global variables *)
        /\ i = 0
        /\ from = 1
        /\ list = LinkedList({})
        /\ list2 = LinkedList({})
        /\ temp = NULL
        /\ arg = {}
        /\ lab = NULL
        /\ lab2 = NULL
        /\ index = NULL
        /\ preInsertSize = NULL
        /\ preRemoveSize = NULL
        /\ nl = NULL
        /\ l1 = NULL
        /\ l2 = NULL
        /\ pc = "PRECONDITIONS"

PRECONDITIONS == /\ pc = "PRECONDITIONS"
                 /\ \E size1 \in 0..3:
                      /\ \E size2 \in 0..3:
                           list' = LinkedList(NewDomain(size2, list))
                      /\ list2' = LinkedList(NewDomain(size1, list'))
                 /\ \/ /\ pc' = "INSERTHEAD"
                    \/ /\ pc' = "INSERTAFTER"
                    \/ /\ pc' = "CONCAT"
                    \/ /\ pc' = "SWAP"
                    \/ /\ pc' = "REMOVE"
                    \/ /\ pc' = "REMOVEAFTER"
                    \/ /\ pc' = "FOREACHFROM"
                 /\ UNCHANGED << i, from, temp, arg, lab, lab2, index, 
                                 preInsertSize, preRemoveSize, nl, l1, l2 >>

INSERTHEAD == /\ pc = "INSERTHEAD"
              /\ IF Empty(list)
                    THEN /\ preInsertSize' = 0
                    ELSE /\ preInsertSize' = Cardinality(DOMAIN list)
              /\ nl' = NewLabel(list)
              /\ list' = InsertHead(nl', list)
              /\ pc' = "ASSERTINSERTHEAD"
              /\ UNCHANGED << i, from, list2, temp, arg, lab, lab2, index, 
                              preRemoveSize, l1, l2 >>

ASSERTINSERTHEAD == /\ pc = "ASSERTINSERTHEAD"
                    /\ Assert(HeadElementInserted, 
                              "Failure of assertion at line 87, column 13.")
                    /\ pc' = "Done"
                    /\ UNCHANGED << i, from, list, list2, temp, arg, lab, lab2, 
                                    index, preInsertSize, preRemoveSize, nl, 
                                    l1, l2 >>

INSERTAFTER == /\ pc = "INSERTAFTER"
               /\ IF Empty(list)
                     THEN /\ TRUE
                          /\ pc' = "Done"
                          /\ UNCHANGED << list, temp, lab, lab2, preInsertSize >>
                     ELSE /\ IF Empty(list)
                                THEN /\ preInsertSize' = 0
                                ELSE /\ preInsertSize' = Cardinality(DOMAIN list)
                          /\ lab' = (CHOOSE value \in DOMAIN list: TRUE)
                          /\ lab2' = list[lab']["next"]
                          /\ temp' = list
                          /\ list' = InsertAfter(lab', list)
                          /\ pc' = "ASSERTINSERTAFTER"
               /\ UNCHANGED << i, from, list2, arg, index, preRemoveSize, nl, 
                               l1, l2 >>

ASSERTINSERTAFTER == /\ pc = "ASSERTINSERTAFTER"
                     /\ Assert(ElementInsertedAfter, 
                               "Failure of assertion at line 100, column 13.")
                     /\ pc' = "Done"
                     /\ UNCHANGED << i, from, list, list2, temp, arg, lab, 
                                     lab2, index, preInsertSize, preRemoveSize, 
                                     nl, l1, l2 >>

CONCAT == /\ pc = "CONCAT"
          /\ l1' = list
          /\ l2' = list2
          /\ temp' = Concat(list, list2)
          /\ list' = temp'[1]
          /\ list2' = temp'[2]
          /\ pc' = "ASSERTCONCAT"
          /\ UNCHANGED << i, from, arg, lab, lab2, index, preInsertSize, 
                          preRemoveSize, nl >>

ASSERTCONCAT == /\ pc = "ASSERTCONCAT"
                /\ Assert(ListsConcatenated, 
                          "Failure of assertion at line 111, column 13.")
                /\ pc' = "Done"
                /\ UNCHANGED << i, from, list, list2, temp, arg, lab, lab2, 
                                index, preInsertSize, preRemoveSize, nl, l1, 
                                l2 >>

SWAP == /\ pc = "SWAP"
        /\ l1' = list
        /\ l2' = list2
        /\ temp' = Swap(list, list2)
        /\ list' = temp'[1]
        /\ list2' = temp'[2]
        /\ pc' = "ASSERTSWAP"
        /\ UNCHANGED << i, from, arg, lab, lab2, index, preInsertSize, 
                        preRemoveSize, nl >>

ASSERTSWAP == /\ pc = "ASSERTSWAP"
              /\ Assert(ListsSwapped, 
                        "Failure of assertion at line 121, column 13.")
              /\ pc' = "Done"
              /\ UNCHANGED << i, from, list, list2, temp, arg, lab, lab2, 
                              index, preInsertSize, preRemoveSize, nl, l1, l2 >>

REMOVE == /\ pc = "REMOVE"
          /\ IF Empty(list) = FALSE
                THEN /\ pc' = "REMOVENOTEMPTY"
                ELSE /\ pc' = "REMOVEEMPTY"
          /\ UNCHANGED << i, from, list, list2, temp, arg, lab, lab2, index, 
                          preInsertSize, preRemoveSize, nl, l1, l2 >>

REMOVENOTEMPTY == /\ pc = "REMOVENOTEMPTY"
                  /\ lab' = (CHOOSE x \in DOMAIN list:TRUE)
                  /\ list' = Remove(lab', list)
                  /\ pc' = "ASSERTREMOVE"
                  /\ UNCHANGED << i, from, list2, temp, arg, lab2, index, 
                                  preInsertSize, preRemoveSize, nl, l1, l2 >>

ASSERTREMOVE == /\ pc = "ASSERTREMOVE"
                /\ Assert(ElementRemoved, 
                          "Failure of assertion at line 131, column 17.")
                /\ pc' = "Done"
                /\ UNCHANGED << i, from, list, list2, temp, arg, lab, lab2, 
                                index, preInsertSize, preRemoveSize, nl, l1, 
                                l2 >>

REMOVEEMPTY == /\ pc = "REMOVEEMPTY"
               /\ TRUE
               /\ pc' = "Done"
               /\ UNCHANGED << i, from, list, list2, temp, arg, lab, lab2, 
                               index, preInsertSize, preRemoveSize, nl, l1, l2 >>

REMOVEAFTER == /\ pc = "REMOVEAFTER"
               /\ IF Cardinality(DOMAIN list) < 2
                     THEN /\ TRUE
                          /\ pc' = "Done"
                          /\ UNCHANGED << list, lab, lab2, preRemoveSize >>
                     ELSE /\ preRemoveSize' = Cardinality(DOMAIN list)
                          /\ lab' = (CHOOSE l \in DOMAIN list: list[l]["next"] \in DOMAIN list)
                          /\ lab2' = list[lab']["next"]
                          /\ list' = RemoveAfter(lab', list)
                          /\ pc' = "ASSERTREMOVEAFTER"
               /\ UNCHANGED << i, from, list2, temp, arg, index, preInsertSize, 
                               nl, l1, l2 >>

ASSERTREMOVEAFTER == /\ pc = "ASSERTREMOVEAFTER"
                     /\ Assert(ElementAfterRemoved, 
                               "Failure of assertion at line 147, column 13.")
                     /\ pc' = "Done"
                     /\ UNCHANGED << i, from, list, list2, temp, arg, lab, 
                                     lab2, index, preInsertSize, preRemoveSize, 
                                     nl, l1, l2 >>

FOREACHFROM == /\ pc = "FOREACHFROM"
               /\ IF Empty(list) = FALSE
                     THEN /\ pc' = "FOREACHNOTEMPTY"
                     ELSE /\ TRUE
                          /\ pc' = "Done"
               /\ UNCHANGED << i, from, list, list2, temp, arg, lab, lab2, 
                               index, preInsertSize, preRemoveSize, nl, l1, l2 >>

FOREACHNOTEMPTY == /\ pc = "FOREACHNOTEMPTY"
                   /\ lab' = First(list)
                   /\ arg' = {lab'}
                   /\ pc' = "FOREACHFROMLOOP"
                   /\ UNCHANGED << i, from, list, list2, temp, lab2, index, 
                                   preInsertSize, preRemoveSize, nl, l1, l2 >>

FOREACHFROMLOOP == /\ pc = "FOREACHFROMLOOP"
                   /\ IF from < 1
                         THEN /\ lab' = list[lab]["next"]
                              /\ arg' = (arg \union {lab'})
                              /\ from' = from + 1
                              /\ pc' = "FOREACHFROMLOOP"
                         ELSE /\ pc' = "FOREACHFROMRUN"
                              /\ UNCHANGED << from, arg, lab >>
                   /\ UNCHANGED << i, list, list2, temp, lab2, index, 
                                   preInsertSize, preRemoveSize, nl, l1, l2 >>

FOREACHFROMRUN == /\ pc = "FOREACHFROMRUN"
                  /\ list' = ForEachFrom(list, {el \in DOMAIN list: el \notin arg}, ForEachOperator)
                  /\ from' = 1
                  /\ pc' = "Done"
                  /\ UNCHANGED << i, list2, temp, arg, lab, lab2, index, 
                                  preInsertSize, preRemoveSize, nl, l1, l2 >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == PRECONDITIONS \/ INSERTHEAD \/ ASSERTINSERTHEAD \/ INSERTAFTER
           \/ ASSERTINSERTAFTER \/ CONCAT \/ ASSERTCONCAT \/ SWAP \/ ASSERTSWAP
           \/ REMOVE \/ REMOVENOTEMPTY \/ ASSERTREMOVE \/ REMOVEEMPTY
           \/ REMOVEAFTER \/ ASSERTREMOVEAFTER \/ FOREACHFROM \/ FOREACHNOTEMPTY
           \/ FOREACHFROMLOOP \/ FOREACHFROMRUN
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 


=============================================================================

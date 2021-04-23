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
old = [a |-> NULL, b |-> "c", c |-> "a"],
temp = NULL

\* Global and local invariants the model is based on 
define

HasLast == Empty(list) \/ \E el \in DOMAIN list: list[el]["next"] = NULL \* invariant for all lists

validList == IsLinkedList(list)

end define

\* The model checking alogithm
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
    end either;
    
    END:
    print "===LIST IS===";
    print list;
    
    
    (*    
    list := LinkedList(NewDomain(3, list));
    print list;
    START2:
    \* ForEach usage    
    \*print ForEach(list, LAMBDA x: x*2);
    list2 := LinkedList(NewDomain(2, list));
    print list2;
    NEXT:
    either
    A:
    temp := Concat(list, list2);
    list := temp[1];
    list2:= temp[2];
    or
    B:
    list := InsertHead(NewLabel(list), list);
    or
    C:
    temp := Swap(list, list2);
    list := temp[1];
    list2:= temp[2];
    end either;
    PRINT:
    print list;
    *)
 
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
\* BEGIN TRANSLATION (chksum(pcal) = "8da779f4" /\ chksum(tla) = "6b0aeb71")
VARIABLES i, list, list2, characters, domain, old, temp, pc

(* define statement *)
HasLast == Empty(list) \/ \E el \in DOMAIN list: list[el]["next"] = NULL

validList == IsLinkedList(list)


vars == << i, list, list2, characters, domain, old, temp, pc >>

Init == (* Global variables *)
        /\ i = 0
        /\ list = LinkedList({})
        /\ list2 = LinkedList({})
        /\ characters = {"x", "y", "z"}
        /\ domain = {"a", "b"}
        /\ old = [a |-> NULL, b |-> "c", c |-> "a"]
        /\ temp = NULL
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
                 /\ UNCHANGED << i, characters, domain, old, temp >>

INSERTHEAD == /\ pc = "INSERTHEAD"
              /\ list' = InsertHead(NewLabel(list), list)
              /\ pc' = "END"
              /\ UNCHANGED << i, list2, characters, domain, old, temp >>

CONCAT == /\ pc = "CONCAT"
          /\ temp' = Concat(list, list2)
          /\ list' = temp'[1]
          /\ list2' = temp'[2]
          /\ pc' = "END"
          /\ UNCHANGED << i, characters, domain, old >>

SWAP == /\ pc = "SWAP"
        /\ temp' = Swap(list, list2)
        /\ list' = temp'[1]
        /\ list2' = temp'[2]
        /\ pc' = "END"
        /\ UNCHANGED << i, characters, domain, old >>

REMOVE == /\ pc = "REMOVE"
          /\ IF Empty(list) = FALSE
                THEN /\ pc' = "REMOVENOTEMPTY"
                ELSE /\ pc' = "REMOVEEMPTY"
          /\ UNCHANGED << i, list, list2, characters, domain, old, temp >>

REMOVENOTEMPTY == /\ pc = "REMOVENOTEMPTY"
                  /\ list' = Remove(CHOOSE x \in DOMAIN list:TRUE, list)
                  /\ pc' = "END"
                  /\ UNCHANGED << i, list2, characters, domain, old, temp >>

REMOVEEMPTY == /\ pc = "REMOVEEMPTY"
               /\ TRUE
               /\ pc' = "END"
               /\ UNCHANGED << i, list, list2, characters, domain, old, temp >>

END == /\ pc = "END"
       /\ PrintT("===LIST IS===")
       /\ PrintT(list)
       /\ pc' = "Done"
       /\ UNCHANGED << i, list, list2, characters, domain, old, temp >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == PRECONDITIONS \/ INSERTHEAD \/ CONCAT \/ SWAP \/ REMOVE
           \/ REMOVENOTEMPTY \/ REMOVEEMPTY \/ END
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 


=============================================================================

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
old = [a |-> NULL, b |-> "c", c |-> "a"]
define

HasLast == Empty(list) \/ \E el \in DOMAIN list: list[el]["next"] = NULL \* invariant for all lists

validList == isll(list)
    
HighestNode ==
    IF Empty(list)
    THEN 0
    ELSE
    CHOOSE n \in 1..100: ("node" \o ToString(n)) \in DOMAIN list /\ ~\E h \in 1..100: "node" \o ToString(h) \in DOMAIN list /\ h > n


NewLabel ==
    "node" \o ToString(HighestNode+1)
    
NewDomain(len) ==
    {"node" \o ToString(x): x \in HighestNode+1..HighestNode+len}

InsertHead(val) ==
   IF Empty(list)
   THEN
    CHOOSE x \in [{NewLabel} -> [next: {NULL}, value: {1}]]: TRUE
   ELSE
    list @@ (CHOOSE x \in [{NewLabel} -> [next: {First(list)}, value: {1}]]:TRUE)

\* with next[label] == list[label]["next"]
\* Find a function so that each element lab in the domain of the list U an arbitrary new label
\* maps to lext[lab] except, for label which maps to the new label, and new label which maps to next[label] 
InsertAfter(label) == 
    IF Empty(list) /\ label \notin DOMAIN list THEN
        list \* just for testing
        \* Assert("FALSE", "CANNOT INSERT AFTER ELEMENT NOT IN LIST")
    ELSE
        LET 
        nl == {NewLabel}
        next(lab) == list[lab]["next"]
        IN
        CHOOSE l \in [DOMAIN list \union nl -> [value: VALUE, next: Range(list) \union nl]]:
            \A d \in DOMAIN list \union nl:
                (d = label /\ l[d]["next"] \in nl)
            \/  (d \in nl /\ l[d]["next"] = next(label))
            \/  (d \notin {label} \union nl  /\ l[d]["next"] = next(d))


\* Find a function from the domain of list excluding the removed element, the new function returns the same value as list,
\* except if the list pointed to the removed elemnt, in which case the fuction returns list[label]["next"]
Remove(label, llist) ==  
    IF Empty(llist) \/ label \notin DOMAIN llist THEN
       Assert("FALSE", "CANNOT REMOVE ELEMENT NOT IN LIST")
    ELSE IF DOMAIN llist = {label} THEN 
       EmptyList
    ELSE
     CHOOSE l \in [(DOMAIN llist) \ {label} -> [value: VALUE, next: Range(llist) \ {label}]]:
        \A d \in ((DOMAIN llist) \ {label}): (l[d]["next"] = llist[d]["next"] \/ (llist[d]["next"] = label /\ l[d]["next"] = llist[llist[d]["next"]]["next"]))
(*
RemoveHead ==
    IF Empty(list) THEN
        Assert("FALSE", "NO HEAD IN LIST")
    ELSE
        Remove(First(list))

RemoveAfter(label) ==
    IF Cardinality(DOMAIN list) < 2 THEN
        Assert("FALSE", "NEXT ELEMENT IS NULL OR THE LIST IS EMPTY")
    ELSE
        Remove(list[label]["next"])
        
RemovePrev(label) ==
    IF Cardinality(DOMAIN list) < 2 THEN
        Assert("FALSE", "THERE IS NO ELEMENT BEFORE THE CHOSEN ELEMENT")
    ELSE
        Remove(CHOOSE l \in DOMAIN list: list[l]["next"] = label) 
*)
GetNext(label) ==
    list[label]["next"]
    
Swap(list2) ==
    LET
      head2 == First(list2)
      temp == Remove(First(list), list)
    IN
     temp @@ CHOOSE l \in [{head2} -> {[next |-> First(temp), value |-> list2[head2]["value"]]}]: TRUE  

end define
begin
    START:
    list := ll(NewDomain(3));
    print list;
    NEXT:
    print Swap(ll(NewDomain(2)));
  
 (*    NEXT3:
    list := Remove("node1");
    print list;
   either
    or
    list := ll({});
    end either;
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
\* BEGIN TRANSLATION (chksum(pcal) = "efbcb0ac" /\ chksum(tla) = "291050ed")
VARIABLES i, list, characters, domain, old, pc

(* define statement *)
HasLast == Empty(list) \/ \E el \in DOMAIN list: list[el]["next"] = NULL

validList == isll(list)

HighestNode ==
    IF Empty(list)
    THEN 0
    ELSE
    CHOOSE n \in 1..100: ("node" \o ToString(n)) \in DOMAIN list /\ ~\E h \in 1..100: "node" \o ToString(h) \in DOMAIN list /\ h > n


NewLabel ==
    "node" \o ToString(HighestNode+1)

NewDomain(len) ==
    {"node" \o ToString(x): x \in HighestNode+1..HighestNode+len}

InsertHead(val) ==
   IF Empty(list)
   THEN
    CHOOSE x \in [{NewLabel} -> [next: {NULL}, value: {1}]]: TRUE
   ELSE
    list @@ (CHOOSE x \in [{NewLabel} -> [next: {First(list)}, value: {1}]]:TRUE)




InsertAfter(label) ==
    IF Empty(list) /\ label \notin DOMAIN list THEN
        list

    ELSE
        LET
        nl == {NewLabel}
        next(lab) == list[lab]["next"]
        IN
        CHOOSE l \in [DOMAIN list \union nl -> [value: VALUE, next: Range(list) \union nl]]:
            \A d \in DOMAIN list \union nl:
                (d = label /\ l[d]["next"] \in nl)
            \/  (d \in nl /\ l[d]["next"] = next(label))
            \/  (d \notin {label} \union nl  /\ l[d]["next"] = next(d))




Remove(label, llist) ==
    IF Empty(llist) \/ label \notin DOMAIN llist THEN
       Assert("FALSE", "CANNOT REMOVE ELEMENT NOT IN LIST")
    ELSE IF DOMAIN llist = {label} THEN
       EmptyList
    ELSE
     CHOOSE l \in [(DOMAIN llist) \ {label} -> [value: VALUE, next: Range(llist) \ {label}]]:
        \A d \in ((DOMAIN llist) \ {label}): (l[d]["next"] = llist[d]["next"] \/ (llist[d]["next"] = label /\ l[d]["next"] = llist[llist[d]["next"]]["next"]))



















GetNext(label) ==
    list[label]["next"]

Swap(list2) ==
    LET
      head2 == First(list2)
      temp == Remove(First(list), list)
    IN
     temp @@ CHOOSE l \in [{head2} -> {[next |-> First(temp), value |-> list2[head2]["value"]]}]: TRUE


vars == << i, list, characters, domain, old, pc >>

Init == (* Global variables *)
        /\ i = 0
        /\ list = ll({})
        /\ characters = {"x", "y", "z"}
        /\ domain = {"a", "b"}
        /\ old = [a |-> NULL, b |-> "c", c |-> "a"]
        /\ pc = "START"

START == /\ pc = "START"
         /\ list' = ll(NewDomain(3))
         /\ PrintT(list')
         /\ pc' = "NEXT"
         /\ UNCHANGED << i, characters, domain, old >>

NEXT == /\ pc = "NEXT"
        /\ PrintT(Swap(ll(NewDomain(2))))
        /\ pc' = "Done"
        /\ UNCHANGED << i, list, characters, domain, old >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == START \/ NEXT
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 



=============================================================================

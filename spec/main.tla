-------------------------------- MODULE main --------------------------------
EXTENDS TLC, FiniteSets, Sequences, Integers
CONSTANTS NULL, VALUE
INSTANCE LinkedList
                              
(* --algorithm List

variables 
list = [NULL |-> [next |-> NULL, value |-> NULL]],
domain = 1..3,
a =1;



define
HasLast == 
    \E el \in DOMAIN list: list[el]["next"] = NULL \* invariant for all lists

isllinv ==
     Cyclic(list) = FALSE /\ 
     Ring(list) = FALSE /\
     \A el \in ((DOMAIN list \union {NULL}) \ {First(list)}): \E x \in DOMAIN list : list[x]["next"] = el  /\ el /= x
    
end define


procedure Empty(l) begin 
   Cardinality(DOMAIN l);
   return;
end procedure;



begin
  print list;
 \* InsertHead([a |-> "a"]);
  Empty(list);
  print a;
end algorithm;*)
\* BEGIN TRANSLATION (chksum(pcal) = "486f16e" /\ chksum(tla) = "43524abe")
VARIABLES list, domain, a, pc

(* define statement *)
HasLast ==
    \E el \in DOMAIN list: list[el]["next"] = NULL

isllinv ==
     Cyclic(list) = FALSE /\
     Ring(list) = FALSE /\
     \A el \in ((DOMAIN list \union {NULL}) \ {First(list)}): \E x \in DOMAIN list : list[x]["next"] = el  /\ el /= x


vars == << list, domain, a, pc >>

Init == (* Global variables *)
        /\ list = [NULL |-> [next |-> NULL, value |-> NULL]]
        /\ domain = 1..3
        /\ a = 1
        /\ pc = "Lbl_1"

Lbl_1 == /\ pc = "Lbl_1"
         /\ PrintT(list)
         /\ Assert(Cardinality(DOMAIN list) = 1, 
                   "Failure of assertion at line 28, column 4 of macro called at line 38, column 3.")
         /\ PrintT(Empty(list))
         /\ PrintT(a)
         /\ pc' = "Done"
         /\ UNCHANGED << list, domain, a >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == Lbl_1
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 






=============================================================================

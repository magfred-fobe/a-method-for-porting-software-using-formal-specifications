-------------------------------- MODULE main --------------------------------
EXTENDS TLC, FiniteSets, Sequences, Integers
CONSTANTS NULL
INSTANCE LinkedList
                              
(* --algorithm List
variables domain = {"a", "b", "c"}, seq =[a |-> "c", b |-> "a", c |-> "b"], nod = DOMAIN seq, all = [1..Cardinality(nod) -> nod]

begin
   \* print isLinkedList(seq);
   
   print LinkedLists(domain);
  \* print First(seq);
  \* print Cyclic(seq);
end algorithm;*)
\* BEGIN TRANSLATION (chksum(pcal) = "e99507a8" /\ chksum(tla) = "603d3d3f")
VARIABLES domain, seq, nod, all, pc

vars == << domain, seq, nod, all, pc >>

Init == (* Global variables *)
        /\ domain = {"a", "b", "c"}
        /\ seq = [a |-> "c", b |-> "a", c |-> "b"]
        /\ nod = DOMAIN seq
        /\ all = [1..Cardinality(nod) -> nod]
        /\ pc = "Lbl_1"

Lbl_1 == /\ pc = "Lbl_1"
         /\ PrintT(LinkedLists(domain))
         /\ pc' = "Done"
         /\ UNCHANGED << domain, seq, nod, all >>

(* Allow infinite stuttering to prevent deadlock on termination. *)
Terminating == pc = "Done" /\ UNCHANGED vars

Next == Lbl_1
           \/ Terminating

Spec == Init /\ [][Next]_vars

Termination == <>(pc = "Done")

\* END TRANSLATION 
=============================================================================

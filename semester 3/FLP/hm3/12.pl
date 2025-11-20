%Adds an element to the end of the list
%(L,E,R)
%L-list
%R-result
%(i,i,o)
addend([],E,[E]).
addend([H|T],E,[H|R]):-
    addend(T,E,R).

%reverse a list
%(L,R)
%L-list
%R-resulted list
%(i,o)
reverselist([],[]).
reverselist([H|T], R) :-
    reverselist(T, RT),
    addend(RT,H,R).


%returns every element from the list of candidates L
%(L,E)
%L-list
%E-excluding this elem
%C-candidate element
%(i,i,o)
candidate([F|_],E,F):-
    F=\=E.
candidate([_|T],E,C):-
    candidate(T,E,C).

% final verifies if in the current solution we reached has the requested
% number of elements and it starts with 1 or -1
%(L,N)
%L-list
%N-number of elements it should have
%(i,i)
firstisone([H|_]):-
    (H=1;H=(-1)).
final(L,N):-firstisone(L),nelements(L,N).
nelements([],0).
nelements([_|T],N):-
    N>0,
    N1 is N-1,
    nelements(T,N1).

%generates the results
%(L,N,R)
%L-list of elements from where we cunstruct the solutions
%N-number of elements wanted in the solution
%R-solution
%(i,i,o)
generate(L,N,R):-
    candidate(L,-2,C),
    %candidatii de aici 0,-1,1
    generateaux(L,N,R,[C],C).

%(L,N,R,X,Prev)
%L,N,R as above
%X-current solution we are working on
%Prev-we memeorize the last element at any point in the construction of
%the solution
%(i,i,o,i,i)
generateaux(_,N,R,X,_):-%X are N elemente si incepe cu 1 sau -1 ca sa se poata termina in 0
    final(X,N),
    reverselist([0|X],R).
generateaux(L,N,R,X,Prev):-
    not(nelements(X,N)),
    candidate(L,Prev,C),
    generateaux(L,N,R,[C|X],C).

wrapper(N):-
    N1 is N+N,
    generate([0,1,-1],N1,R),
    writeln(R),
    fail.
wrapper(_).



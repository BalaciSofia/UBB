% list composed of numbers and non emty linear numerical lists
% invert the sublists fo which the lowest common multiple is greater
% than the square of  the first elem of the sublist
%
% cmmdc cel mai mic multiplu comun
% reverse

% cmmdc(a,b)=cmmdc(a-b),a>b
%            cmmdc(b-a),b>a
%            a,a=b

cmmdc(A,B,A):-
    A=:=B,!.
cmmdc(A,B,R):-
    A > B,!,
    A1 is A-B,
    cmmdc(A1,B,R).
cmmdc(A,B,R):-
    B1 is B-A,
    cmmdc(A,B1,R).

cmmmc(A,B,R):-
    cmmdc(A,B,R1),
    R is (A*B)//R1.

%cmmdclist_wrapper(l)=cmmdclist(l2...ln,l1)
% cmmdclist(l,n)= cmmdclist(l2...ln,cmmdc(l1,n))

cmmmclist([],N,N).
cmmmclist([H|T],N,R):-
    cmmmc(H,N,N1),
    cmmmclist(T,N1,R).

cmmmclist_wrapper([H|T],R):-
    cmmmclist(T,H,R).

addback([],E,[E]).
addback([H|T],E,[H|R]):-
    addback(T,E,R).

%invert(l)=invert(l2...ln)U l1
%          [],n=0

invert([],[]).
invert([H|T],R):-
    invert(T,R1),
    addback(R1,H,R).

getfirstsquared([H|_],R):-
    R is H*H.

main([],[]).
main([H|T],[H1|R]):-
    is_list(H),
    getfirstsquared(H,S),
    cmmmclist_wrapper(H,C),
    C>S,!,
    invert(H,H1),
    main(T,R).
main([H|T],[H|R]):-
    main(T,R).


%------------------------------------------------
%generate the list of subsets with at least N elements
%such that sum of all elements of the subset is divisible by 3

checkdivizibility([],S):-
    0 is (S mod 3),!.
checkdivizibility([H|T],S):-
    S1 is S+H,
    checkdivizibility(T,S1).


candidate([H|T], H, T).
candidate([_|T], E, Rest):-
    candidate(T, E, Rest).

morethanN([],N):-
    N =< 0,!.
morethanN([_|T],N):-
    N1 is N-1,
    morethanN(T,N1).

% perm(L,N,R) generates one subset R of L s.t. len>=N and sum divisible by 3
perm(L,N,R):-
    permutations_aux(L,N,[],R).

% Option 1: stop here and return X if it satisfies conditions (X must be non-empty)
permutations_aux(_,N,X,R):-
    X \= [],
    morethanN(X,N),
    checkdivizibility(X,0),
    invert(X,R).

% Option 2: extend subset by picking a new element, but ONLY from the remaining tail
permutations_aux(L,N,X,R):-
    candidate(L,New,Rest),
    permutations_aux(Rest,N,[New|X],R).

% If you want the full list of all solutions:
solve(L,N,All):-
    findall(R, perm(L,N,R), All).


%I
%2
%f([],0)
%f(H|T],S):-
%    F(T,S1),
%    faux(H,S1,S).

%faux(H,S1,S):-
%    H < S1,!,
%    S is S1+H.
%faux(H,S1,S):-
% S is S1+2.
%
%4
%(1,1,1)
%
%list of int numb
%generate the list of all subsets
%with at least n elements
%their sum must be div by 3

validatesum([],S):-
    0 is S mod 3.
validatesum([H|T],S):-
    S1 is S+H,
    validatesum(T,S1).
validatelen([],N,L):-
    L >= N.
validatelen([_|T],N,L):-
    L1 is L+1,
    validatelen(T,N,L1).
%(i,o,o)
candidate([H|T],H,T).
generate(L,N,R):-
    generateaux(L,N,R,[]).
generateaux([],N,X,X):-
    validatesum(X,0),
    validatelen(X,N,0).
generateaux(L,N,R,X):-
    candidate(L,C,T),
    addback(X,C,X1),
    generateaux(T,N,R,X1).
generateaux(L,N,R,X):-
    candidate(L,_,T),
    generateaux(T,N,R,X).
solve(L,N,Rez):-
    findall(R,generate(L,N,R),Rez).
addback([],E,[E]).
addback([H|T],E,[H|R]):-
    addback(T,E,R).

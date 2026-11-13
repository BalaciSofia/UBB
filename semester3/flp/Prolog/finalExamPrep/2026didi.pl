%I
%2
%f([],0)
%f([H|T],S):-
%  f(T,S1),
%  faux(H,S1,S)
%
%faux(H,S1,R):-
%  S1<H,!,
%  R is H.
%faux(H,S1,R):
%  R is S1.
%
%4
%(1 2 3)
%(1 3)

%permutations of a list
%property : absolute diff between 2 consecutive values from each permm
%is <=3

islengthN([],[]).
islengthN([_|T],[_|T1]):-
    islengthN(T,T1).
property([],_).
property([H|T],P):-
    R is abs(P-H),
    R =<3,
    property(T,H).
candidate([H|T],H,T).
candidate([H|T],C,[H|R]):-
     candidate(T,C,R).
generate(L,R):-
    generateaux(L,L,[],R).
generateaux(_,L1,X,X):-
    first(X,F),
    islengthN(X,L1),
    property(X,F).
generateaux(L,L1,X,R):-
    candidate(L,C,T),
    addback(X,C,X1),
    generateaux(T,L1,X1,R).
solve(L,Rez):-
    findall(R,generate(L,R),Rez).
first([H|_],H).
addback([],E,[E]).
addback([H|T],E,[H|R]):-
    addback(T,E,R).






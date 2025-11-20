%
%maxim(L,Acc,R)
%L-the list
%Acc-initialized with first element from list
%R-the result
%maxim(i,i,o)
maxim([H|T],Acc,R):-
    H > Acc,
    Acc1 is H,
    maxim(T,Acc1,R).
maxim([H|T],Acc,R):-
    H =< Acc,
    maxim(T,Acc,R).
maxim([],Acc,Acc).

%maxim(i,o)
%L-the list
%R-maximum element
maxim(L,R):-
    L=[H|_],
    maxim(L,H,R).

%replace(L,M,E,R)
%L-the list
%M-the element we are replaceing
%E-the element we are replacing M with
%R-the resulted list
%replace(i,i,i,o)
replace([H|T],M,E,[H|R]):-
    H=\=M,
    replace(T,M,E,R).
replace([H|T],M,E,[E|R]):-
    H==M,
    replace(T,M,E,R).
replace([],_,_,[]).

%replace(L,E,R)
%L-the list
%E-the element we are replaceing the maximum with
%R-the resulted list
%replace(i,i,o)
replace(L,E,R):-
    maxim(L,M),
    replace(L,M,E,R).


